/**
 * Copyright (c) 2016-2022 Deephaven Data Labs and Patent Pending
 */
package io.deephaven.time;

import io.deephaven.base.clock.Clock;
import io.deephaven.base.clock.TimeConstants;
import io.deephaven.base.clock.TimeZones;
import io.deephaven.hash.KeyedObjectHashMap;
import io.deephaven.hash.KeyedObjectKey;
import io.deephaven.configuration.Configuration;
import io.deephaven.function.Numeric;
import io.deephaven.util.QueryConstants;
import io.deephaven.util.annotations.ScriptApi;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;
import org.joda.time.DateMidnight;
import org.joda.time.DurationFieldType;

import java.time.*;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.time.temporal.ChronoField;
import java.util.HashMap;
import java.util.Objects;
import java.util.concurrent.TimeUnit;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import static io.deephaven.util.QueryConstants.NULL_LONG;

/**
 * Utilities for Deephaven date/time storage and manipulation.
 */
@SuppressWarnings("unused")
public class DateTimeUtils {
    //TODO: reorganize functions into better groupings

    //TODO: no equivalent.  Document and move out?
    public static final DateTime[] ZERO_LENGTH_DATETIME_ARRAY = new DateTime[0];

    // The following 3 patterns support LocalDate literals. Note all LocalDate patterns must not have characters after
    // the date, to avoid confusion with DateTime literals.

    /** Matches yyyy-MM-dd. */
    private static final Pattern STD_DATE_PATTERN =
            Pattern.compile("^(?<year>[0-9][0-9][0-9][0-9])-(?<month>[0-9][0-9])-(?<day>[0-9][0-9])$");
    /** Matches yyyyMMdd (consistent with ISO dates). */
    private static final Pattern STD_DATE_PATTERN2 =
            Pattern.compile("^(?<year>[0-9][0-9][0-9][0-9])(?<month>[0-9][0-9])(?<day>[0-9][0-9])$");
    /**
     * Matches variations of month/day/year or day/month/year or year/month/day - how this is interpreted depends on the
     * DateTimeUtils.dateStyle system property.
     */
    private static final Pattern SLASH_DATE_PATTERN =
            Pattern.compile(
                    "^(?<part1>[0-9]?[0-9](?<part1sub2>[0-9][0-9])?)\\/(?<part2>[0-9]?[0-9])\\/(?<part3>[0-9]?[0-9](?<part3sub2>[0-9][0-9])?)$");

    /** for use when interpreting two digit years (we use Java's rules). */
    private static final DateTimeFormatter TWO_DIGIT_YR_FORMAT = DateTimeFormatter.ofPattern("yy");

    /**
     * for LocalTime literals. Note these must begin with "L" to avoid ambiguity with the older
     * TIME_AND_DURATION_PATTERN
     */
    private static final Pattern LOCAL_TIME_PATTERN =
            Pattern.compile("^L([0-9][0-9]):?([0-9][0-9])?:?([0-9][0-9])?(\\.([0-9]{1,9}))?");

    // DateTime literals
    private static final Pattern DATETIME_PATTERN = Pattern.compile(
            "[0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9](T[0-9][0-9]?:[0-9][0-9](:[0-9][0-9])?(\\.[0-9][0-9]?[0-9]?[0-9]?[0-9]?[0-9]?[0-9]?[0-9]?[0-9]?)?)? [a-zA-Z]+");
    private static final Pattern TIME_AND_DURATION_PATTERN = Pattern.compile(
            "\\-?([0-9]+T)?([0-9]+):([0-9]+)(:[0-9]+)?(\\.[0-9][0-9]?[0-9]?[0-9]?[0-9]?[0-9]?[0-9]?[0-9]?[0-9]?)?");
    private static final Pattern PERIOD_PATTERN = Pattern.compile(
            "\\-?([0-9]+[Yy])?([0-9]+[Mm])?([0-9]+[Ww])?([0-9]+[Dd])?(T([0-9]+[Hh])?([0-9]+[Mm])?([0-9]+[Ss])?)?");
    private static final String DATE_COLUMN_PARTITION_FORMAT_STRING = "yyyy-MM-dd";

    /**
     * Date formatting styles for use in conversion functions such as {@link #convertDateQuiet(String, DateStyle)}.
     */
    public enum DateStyle {
        MDY, DMY, YMD
    }

    private static final DateStyle DATE_STYLE = DateStyle
            .valueOf(Configuration.getInstance().getStringWithDefault("DateTimeUtils.dateStyle", DateStyle.MDY.name()));

    // region Constants

    /**
     * Constant value of one second in nanoseconds.
     */
    public static final long SECOND = 1_000_000_000;

    /**
     * Constant value of one minute in nanoseconds.
     */
    public static final long MINUTE = 60 * SECOND;

    /**
     * Constant value of one hour in nanoseconds.
     */
    public static final long HOUR = 60 * MINUTE;

    /**
     * Constant value of one day in nanoseconds.
     */
    public static final long DAY = 24 * HOUR;

    /**
     * Constant value of one week in nanoseconds.
     */
    public static final long WEEK = 7 * DAY;

    /**
     * Constant value of one year (365 days) in nanoseconds.
     */
    public static final long YEAR = 365 * DAY;

    // endregion

    private static final Pattern CAPTURING_DATETIME_PATTERN = Pattern.compile(
            "(([0-9][0-9][0-9][0-9])-([0-9][0-9])-([0-9][0-9])T?)?(([0-9][0-9]?)(?::([0-9][0-9])(?::([0-9][0-9]))?(?:\\.([0-9][0-9]?[0-9]?[0-9]?[0-9]?[0-9]?[0-9]?[0-9]?[0-9]?))?)?)?( [a-zA-Z]+)?");

    private enum DateGroupId {
        // Date(1),
        Year(2, ChronoField.YEAR), Month(3, ChronoField.MONTH_OF_YEAR), Day(4, ChronoField.DAY_OF_MONTH),
        // Tod(5),
        Hours(6, ChronoField.HOUR_OF_DAY), Minutes(7, ChronoField.MINUTE_OF_HOUR), Seconds(8,
                ChronoField.SECOND_OF_MINUTE), Fraction(9, ChronoField.MILLI_OF_SECOND);

        public final int id;
        public final ChronoField field;

        DateGroupId(int id, ChronoField field) {
            this.id = id;
            this.field = field;
        }
    }

    /**
     * Maximum time in microseconds that can be converted to a {@link DateTime} without overflow.
     */
    private static final long MAX_CONVERTIBLE_MICROS = Long.MAX_VALUE / 1_000L;

    /**
     * Maximum time in milliseconds that can be converted to a {@link DateTime} without overflow.
     */
    private static final long MAX_CONVERTIBLE_MILLIS = Long.MAX_VALUE / 1_000_000L;

    /**
     * Maximum time in seconds that can be converted to a {@link DateTime} without overflow.
     */
    private static final long MAX_CONVERTIBLE_SECONDS = Long.MAX_VALUE / 1_000_000_000L;

    private static final double YEARS_PER_NANO = 1. / (double) YEAR;

    //TODO: document
    // TODO(deephaven-core#3044): Improve scaffolding around full system replay
    /**
     * Allows setting a custom clock instead of actual current time. This is mainly used when setting up for a replay
     * simulation.
     */
    public static Clock clock;

    /**
     * Returns milliseconds since Epoch for a {@link DateTime} value.
     *
     * @param dateTime The {@link DateTime} for which the milliseconds offset should be returned.
     * @return A long value of milliseconds since Epoch, or a {@link QueryConstants#NULL_LONG} value if the
     *         {@link DateTime} is null.
     */
    public static long millis(DateTime dateTime) {
        if (dateTime == null) {
            return NULL_LONG;
        }

        return dateTime.getMillis();
    }

    /**
     * Returns nanoseconds since Epoch for a {@link DateTime} value.
     *
     * @param dateTime The {@link DateTime} for which the nanoseconds offset should be returned.
     * @return A long value of nanoseconds since Epoch, or a NULL_LONG value if the {@link DateTime} is null.
     */
    public static long nanos(DateTime dateTime) {
        if (dateTime == null) {
            return NULL_LONG;
        }

        return dateTime.getNanos();
    }

    //TODO: no equivalent
    /**
     * Returns nanoseconds since Epoch for an {@link Instant} value.
     *
     * @param instant The {@link Instant} for which the nanoseconds offset should be returned.
     * @return A long value of nanoseconds since Epoch, or a NULL_LONG value if the {@link Instant} is null.
     */
    public static long nanos(Instant instant) {
        if (instant == null) {
            return NULL_LONG;
        }
        return Math.addExact(TimeUnit.SECONDS.toNanos(instant.getEpochSecond()), instant.getNano());
    }

    // region Comparisons

    /**
     * Evaluates whether one {@link DateTime} value is earlier than a second {@link DateTime} value.
     *
     * @param d1 The first {@link DateTime} value to compare.
     * @param d2 The second {@link DateTime} value to compare.
     * @return Boolean true if d1 is earlier than d2, false if either value is null, or if d2 is equal to or earlier
     *         than d1.
     */
    public static boolean isBefore(DateTime d1, DateTime d2) {
        if (d1 == null || d2 == null) {
            return false;
        }

        return d1.getNanos() < d2.getNanos();
    }

    /**
     * Evaluates whether one {@link DateTime} value is later than a second {@link DateTime} value.
     *
     * @param d1 The first {@link DateTime} value to compare.
     * @param d2 The second {@link DateTime} value to compare.
     * @return Boolean true if d1 is later than d2, false if either value is null, or if d2 is equal to or later than
     *         d1.
     */
    public static boolean isAfter(DateTime d1, DateTime d2) {
        if (d1 == null || d2 == null) {
            return false;
        }

        return d1.getNanos() > d2.getNanos();
    }

    /**
     * Adds one time from another.
     *
     * @param dateTime The starting {@link DateTime} value.
     * @param nanos The long number of nanoseconds to add to dateTime.
     * @return a null {@link DateTime} if either input is null; the starting {@link DateTime} plus the specified number
     *         of nanoseconds, if the result is not too large for a {@link DateTime}; or throws a
     *         {@link DateTimeOverflowException DateTimeOverflowException} if the resultant value is more than max long
     *         nanoseconds from Epoch.
     */
    public static DateTime plus(DateTime dateTime, long nanos) {
        if (dateTime == null || nanos == NULL_LONG) {
            return null;
        }

        return new DateTime(checkOverflowPlus(dateTime.getNanos(), nanos, false));
    }

    /**
     * Subtracts one time from another.
     *
     * @param dateTime The starting {@link DateTime} value.
     * @param nanos The long number of nanoseconds to subtract from dateTime.
     * @return a null {@link DateTime} if either input is null; the starting {@link DateTime} minus the specified number
     *         of nanoseconds, if the result is not too negative for a {@link DateTime}; or throws a
     *         {@link DateTimeOverflowException DateTimeOverflowException} if the resultant value is more than min long
     *         nanoseconds from Epoch.
     */
    public static DateTime minus(DateTime dateTime, long nanos) {
        if (dateTime == null || -nanos == NULL_LONG) {
            return null;
        }

        return new DateTime(checkUnderflowMinus(dateTime.getNanos(), nanos, true));
    }

    /**
     * Adds one time from another.
     *
     * @param dateTime The starting {@link DateTime} value.
     * @param period The {@link Period} to add to dateTime.
     * @return a null {@link DateTime} if either input is null; the starting {@link DateTime} plus the specified period,
     *         if the result is not too large for a DateTime; or throws a {@link DateTimeOverflowException
     *         DateTimeOverflowException} if the resultant value is more than max long nanoseconds from Epoch.
     */
    public static DateTime plus(DateTime dateTime, Period period) {
        if (dateTime == null || period == null) {
            return null;
        }

        if (period.isPositive()) {
            return new DateTime(millisToNanos(dateTime.getJodaDateTime().plus(period.getJodaPeriod()).getMillis())
                    + dateTime.getNanosPartial());
        } else {
            return new DateTime(millisToNanos(dateTime.getJodaDateTime().minus(period.getJodaPeriod()).getMillis())
                    + dateTime.getNanosPartial());
        }
    }

    /**
     * Subtracts one time from another.
     *
     * @param dateTime The starting {@link DateTime} value.
     * @param period The {@link Period} to subtract from dateTime.
     * @return a null {@link DateTime} if either input is null; the starting {@link DateTime} minus the specified
     *         period, if the result is not too negative for a {@link DateTime}; or throws a
     *         {@link DateTimeOverflowException DateTimeOverflowException} if the resultant value is more than min long
     *         nanoseconds from Epoch.
     */
    public static DateTime minus(DateTime dateTime, Period period) {
        if (dateTime == null || period == null) {
            return null;
        }

        if (period.isPositive()) {
            return new DateTime(millisToNanos(dateTime.getJodaDateTime().minus(period.getJodaPeriod()).getMillis())
                    + dateTime.getNanosPartial());
        } else {
            return new DateTime(millisToNanos(dateTime.getJodaDateTime().plus(period.getJodaPeriod()).getMillis())
                    + dateTime.getNanosPartial());
        }
    }

    /**
     * Subtracts one time from another.
     *
     * @param d1 The first {@link DateTime}.
     * @param d2 The {@link DateTime} to subtract from d1.
     * @return {@link QueryConstants#NULL_LONG} if either input is null; the long nanoseconds from Epoch value of the
     *         first {@link DateTime} minus d2, if the result is not out of range for a long value; or throws a
     *         {@link DateTimeOverflowException DateTimeOverflowException} if the resultant value would be more than min
     *         long or max long nanoseconds from Epoch.
     *         <P>
     *         Note that the subtraction is done based the nanosecond offsets of the two dates from Epoch, so, if either
     *         date is before Epoch (negative offset), the result may be unexpected.
     *         </P>
     */
    public static long minus(DateTime d1, DateTime d2) {
        if (d1 == null || d2 == null) {
            return NULL_LONG;
        }

        return checkUnderflowMinus(d1.getNanos(), d2.getNanos(), true);
    }

    //TODO: remove deprecated -- ALL OF THEM
    @Deprecated
    public static long diff(DateTime d1, DateTime d2) {
        return diffNanos(d1, d2);
    }

    @Deprecated
    public static double yearDiff(DateTime start, DateTime end) {
        return diffYears(start, end);
    }

    @Deprecated
    public static double dayDiff(DateTime start, DateTime end) {
        return diffDays(start, end);
    }

    /**
     * Returns the difference in nanoseconds between two {@link DateTime} values.
     *
     * @param d1 The first {@link DateTime}.
     * @param d2 The second {@link DateTime}.
     * @return {@link QueryConstants#NULL_LONG} if either input is null; the long nanoseconds from Epoch value of the
     *         first {@link DateTime} minus d2, if the result is not out of range for a long value; or throws a
     *         {@link DateTimeOverflowException DateTimeOverflowException} if the resultant value would be more than min
     *         long or max long nanoseconds from Epoch.
     *         <P>
     *         Note that the subtraction is done based the nanosecond offsets of the two dates from Epoch, so, if either
     *         date is before Epoch (negative offset), the result may be unexpected.
     *         </P>
     *         If the first value is greater than the second value, the result will be negative.
     */
    //TODO: review note in docs
    @SuppressWarnings("WeakerAccess")
    public static long diffNanos(DateTime d1, DateTime d2) {
        return minus(d2, d1);
    }

    /**
     * Returns a double value of the number of 365 day units difference between two {@link DateTime} values.
     *
     * @param start The first {@link DateTime}.
     * @param end The second {@link DateTime}.
     * @return {@link QueryConstants#NULL_LONG} if either input is null; a double value of the number of 365 day periods
     *         obtained from the first {@link DateTime} value minus d2, if the intermediate value of nanoseconds
     *         difference between the two dates is not out of range for a long value; or throws a
     *         {@link DateTimeOverflowException} if the intermediate value would be more than min long or max long
     *         nanoseconds from Epoch.
     *         <P>
     *         Note that the subtraction is done based the nanosecond offsets of the two dates from Epoch, so, if either
     *         date is before Epoch (negative offset), the result may be unexpected.
     *         </P>
     *         If the first value is greater than the second value, the result will be negative.
     */
    //TODO: review note in docs
    public static double diffYears(DateTime start, DateTime end) {
        if (start == null || end == null) {
            return io.deephaven.util.QueryConstants.NULL_DOUBLE;
        }

        return (double) diffNanos(start, end) * YEARS_PER_NANO;
    }

    /**
     * Returns a double value of the number of days difference between two {@link DateTime} values.
     *
     * @param start The first {@link DateTime}.
     * @param end The second {@link DateTime}.
     * @return {@link QueryConstants#NULL_LONG} if either input is null; a double value of the number of days obtained
     *         from the first {@link DateTime} value minus d2, if the intermediate value of nanoseconds difference
     *         between the two dates is not out of range for a long value; or throws a {@link DateTimeOverflowException
     *         DateTimeOverflowException} if the intermediate value would be more than min long or max long nanoseconds
     *         from Epoch.
     *         <P>
     *         Note that the subtraction is done based the nanosecond offsets of the two dates from Epoch, so, if either
     *         date is before Epoch (negative offset), the result may be unexpected.
     *         </P>
     *         If the first value is greater than the second value, the result will be negative.
     */
    @SuppressWarnings("WeakerAccess")
    public static double diffDays(DateTime start, DateTime end) {
        if (start == null || end == null) {
            return io.deephaven.util.QueryConstants.NULL_DOUBLE;
        }

        return (double) diffNanos(start, end) / DAY;
    }
    // endregion

    /**
     * Returns a {@link DateTime} for the requested {@link DateTime} at midnight in the specified time zone.
     *
     * @param dateTime {@link DateTime} for which the new value at midnight should be calculated.
     * @param timeZone {@link TimeZone} for which the new value at midnight should be calculated.
     * @return A null {@link DateTime} if either input is null, otherwise a {@link DateTime} representing midnight for
     *         the date and time zone of the inputs.
     */
    public static DateTime dateTimeAtMidnight(DateTime dateTime, TimeZone timeZone) {
        if (dateTime == null || timeZone == null) {
            return null;
        }

        return new DateTime(millisToNanos(new DateMidnight(dateTime.getMillis(), timeZone.getTimeZone()).getMillis())
                + dateTime.getNanosPartial());
    }

    //TODO: no equivalent
    //TODO: remove or support
    /**
     * Returns a {@link DateTime} representing midnight in a selected time zone on the date specified by a number of
     * milliseconds from Epoch.
     *
     * @param millis A long value of the number of milliseconds from Epoch for which the {@link DateTime} is to be
     *        calculated.
     * @param timeZone {@link TimeZone} for which the new value at midnight should be calculated.
     * @return A {@link DateTime} rounded down to midnight in the selected time zone for the specified number of
     *         milliseconds from Epoch.
     */
    @SuppressWarnings("WeakerAccess")
    public static DateTime millisToDateAtMidnight(final long millis, final TimeZone timeZone) {
        if (millis == NULL_LONG) {
            return null;
        }

        return new DateTime(millisToNanos(new DateMidnight(millis, timeZone.getTimeZone()).getMillis()));
    }

    // region Formatting

    //TODO: rename formatting commands?
    /**
     * Returns a string DateTime representation formatted as "yyyy-MM-ddThh:mm:ss.SSSSSSSSS TZ".
     *
     * @param dateTime The {@link DateTime} to format as a String.
     * @param timeZone The {@link TimeZone} to use when formatting the String.
     * @return A null String if either input is null, otherwise a String formatted as "yyyy-MM-ddThh:mm:ss.nnnnnnnnn TZ".
     */
    public static String formatDateTime(DateTime dateTime, TimeZone timeZone) {
        if (dateTime == null || timeZone == null) {
            return null;
        }

        return dateTime.toString(timeZone);
    }

    /**
     * Returns a string date representation for a specified {@link DateTime} and time zone formatted as
     * "yyy-MM-dd".
     *
     * @param dateTime The {@link DateTime} to format as a String.
     * @param timeZone The {@link TimeZone} to use when formatting the String.
     * @return A null String if either input is null, otherwise a String formatted as "yyyy-MM-dd".
     */
    @SuppressWarnings("WeakerAccess")
    public static String formatDate(DateTime dateTime, TimeZone timeZone) {
        if (dateTime == null || timeZone == null) {
            return null;
        }

        return dateTime.toDateString(timeZone);
    }

    /**
     * Returns a string representation of a number of nanoseconds formatted as "dddThh:mm:ss.nnnnnnnnn".
     * For periods less than one day, "dddT" is not included.
     *
     * @param nanos The long number of nanoseconds offset from Epoch.
     * @return A String formatted as "dddThh:mm:ss.nnnnnnnnn" for periods of more and one day and "hh:mm:ss.nnnnnnnnn" otherwise.
     */
    public static String formatNanos(long nanos) {
        StringBuilder buf = new StringBuilder(25);

        if (nanos < 0) {
            buf.append('-');
            nanos = -nanos;
        }

        int days = (int) (nanos / 86400000000000L);

        nanos %= 86400000000000L;

        int hours = (int) (nanos / 3600000000000L);

        nanos %= 3600000000000L;

        int minutes = (int) (nanos / 60000000000L);

        nanos %= 60000000000L;

        int seconds = (int) (nanos / 1000000000L);

        nanos %= 1000000000L;

        if (days != 0) {
            buf.append(days).append('T');
        }

        buf.append(hours).append(':').append(pad(String.valueOf(minutes), 2)).append(':')
                .append(pad(String.valueOf(seconds), 2));

        if (nanos != 0) {
            buf.append('.').append(pad(String.valueOf(nanos), 9));
        }

        return buf.toString();
    }

    // endregion

    static String pad(@NotNull final String str, final int length) {
        if (length <= str.length()) {
            return str;
        }
        return "0".repeat(length - str.length()) + str;
    }

    // region Chronology Getters

    /**
     * Returns a 1-based int value of the day of the month for a {@link DateTime} and specified time zone.
     *
     * @param dateTime The {@link DateTime} for which to find the day of the month.
     * @param timeZone The {@link TimeZone} to use when interpreting the date/time.
     * @return A {@link QueryConstants#NULL_INT} if either input is null, otherwise, an int value of the day of the
     *         month represented by the {@link DateTime} when interpreted in the specified time zone.
     */
    @SuppressWarnings("WeakerAccess")
    public static int dayOfMonth(DateTime dateTime, TimeZone timeZone) {
        if (dateTime == null || timeZone == null) {
            return io.deephaven.util.QueryConstants.NULL_INT;
        }

        return dateTime.getJodaDateTime(timeZone).getDayOfMonth();
    }

    /**
     * Returns a 1-based int value of the day of the week for a {@link DateTime} in the specified time zone, with 1 being
     * Monday and 7 being Sunday.
     *
     * @param dateTime The {@link DateTime} for which to find the day of the week.
     * @param timeZone The {@link TimeZone} to use when interpreting the date/time.
     * @return A {@link QueryConstants#NULL_INT} if either input is null, otherwise, an int value of the day of the week
     *         represented by the {@link DateTime} when interpreted in the specified time zone.
     */
    public static int dayOfWeek(DateTime dateTime, TimeZone timeZone) {
        if (dateTime == null || timeZone == null) {
            return io.deephaven.util.QueryConstants.NULL_INT;
        }

        return dateTime.getJodaDateTime(timeZone).getDayOfWeek();
    }

    /**
     * Returns a 1-based int value of the day of the year (Julian date) for a {@link DateTime} in the specified time zone.
     *
     * @param dateTime The {@link DateTime} for which to find the day of the year.
     * @param timeZone The {@link TimeZone} to use when interpreting the date/time.
     * @return A {@link QueryConstants#NULL_INT} if either input is null, otherwise, an int value of the day of the year
     *         represented by the {@link DateTime} when interpreted in the specified time zone.
     */
    public static int dayOfYear(DateTime dateTime, TimeZone timeZone) {
        if (dateTime == null || timeZone == null) {
            return io.deephaven.util.QueryConstants.NULL_INT;
        }

        return dateTime.getJodaDateTime(timeZone).getDayOfYear();
    }

    /**
     * Returns an int value of the hour of the day for a {@link DateTime} in the specified time zone. The hour is on a
     * 24 hour clock (0 - 23).
     *
     * @param dateTime The {@link DateTime} for which to find the hour of the day.
     * @param timeZone The {@link TimeZone} to use when interpreting the date/time.
     * @return A {@link QueryConstants#NULL_INT} if either input is null, otherwise, an int value of the hour of the day
     *         represented by the {@link DateTime} when interpreted in the specified time zone.
     */
    @SuppressWarnings("WeakerAccess")
    public static int hourOfDay(DateTime dateTime, TimeZone timeZone) {
        if (dateTime == null || timeZone == null) {
            return io.deephaven.util.QueryConstants.NULL_INT;
        }

        return dateTime.getJodaDateTime(timeZone).getHourOfDay();
    }

    /**
     * Returns an int value of milliseconds since midnight for a {@link DateTime} in the specified time zone.
     *
     * @param dateTime The {@link DateTime} for which to find the milliseconds since midnight.
     * @param timeZone The {@link TimeZone} to use when interpreting the date/time.
     * @return A {@link QueryConstants#NULL_INT} if either input is null, otherwise, an int value of milliseconds since
     *         midnight for the date/time represented by the {@link DateTime} when interpreted in the specified time
     *         zone.
     */
    @SuppressWarnings("WeakerAccess")
    public static int millisOfDay(DateTime dateTime, TimeZone timeZone) {
        if (dateTime == null || timeZone == null) {
            return io.deephaven.util.QueryConstants.NULL_INT;
        }

        return dateTime.getJodaDateTime(timeZone).getMillisOfDay();
    }

    /**
     * Returns an int value of milliseconds since the top of the second for a {@link DateTime} in the specified time
     * zone.
     *
     * @param dateTime The {@link DateTime} for which to find the milliseconds.
     * @param timeZone The {@link TimeZone} to use when interpreting the date/time.
     * @return A {@link QueryConstants#NULL_INT} if either input is null, otherwise, an int value of milliseconds since
     *         the top of the second for the date/time represented by the {@link DateTime} when interpreted in the
     *         specified time zone.
     */
    @SuppressWarnings("WeakerAccess")
    public static int millisOfSecond(DateTime dateTime, TimeZone timeZone) {
        if (dateTime == null || timeZone == null) {
            return io.deephaven.util.QueryConstants.NULL_INT;
        }

        return dateTime.getJodaDateTime(timeZone).getMillisOfSecond();
    }

    /**
     * Returns a long value of nanoseconds since midnight for a {@link DateTime} in the specified time zone.
     *
     * @param dateTime The {@link DateTime} for which to find the nanoseconds since midnight.
     * @param timeZone The {@link TimeZone} to use when interpreting the date/time.
     * @return A {@link QueryConstants#NULL_LONG} if either input is null, otherwise, a long value of nanoseconds since
     *         midnight for the date/time represented by the {@link DateTime} when interpreted in the specified time
     *         zone.
     */
    @SuppressWarnings("WeakerAccess")
    public static long nanosOfDay(DateTime dateTime, TimeZone timeZone) {
        if (dateTime == null || timeZone == null) {
            return NULL_LONG;
        }

        return millisToNanos(dateTime.getJodaDateTime(timeZone).getMillisOfDay()) + dateTime.getNanosPartial();
    }

    /**
     * Returns a long value of nanoseconds since the top of the second for a {@link DateTime} in the specified time
     * zone.
     *
     * @param dateTime The {@link DateTime} for which to find the nanoseconds.
     * @param timeZone The {@link TimeZone} to use when interpreting the date/time.
     * @return A {@link QueryConstants#NULL_LONG} if either input is null, otherwise, a long value of nanoseconds since
     *         the top of the second for the date/time represented by the {@link DateTime} when interpreted in the
     *         specified time zone.
     */
    @SuppressWarnings("WeakerAccess")
    public static long nanosOfSecond(DateTime dateTime, TimeZone timeZone) {
        if (dateTime == null || timeZone == null) {
            return NULL_LONG;
        }

        return millisToNanos(dateTime.getJodaDateTime(timeZone).getMillisOfSecond()) + dateTime.getNanosPartial();
    }

    //TODO: no equivalent
    //TODO: not supported
    /**
     * Returns the number of microseconds that have elapsed since the start of the millisecond represented by the
     * provided {@code dateTime} in the specified time zone. Nanoseconds are rounded, not dropped --
     * '20:41:39.123456700' has 457 micros, not 456.
     *
     * @param dateTime The {@link DateTime} for which to find the microseconds.
     * @param timeZone The {@link TimeZone} to use when interpreting the date/time.
     * @return A {@link QueryConstants#NULL_INT} if either input is null, otherwise, an int value of microseconds since
     *         the top of the millisecond for the date/time represented by the {@link DateTime} when interpreted in the
     *         specified time zone.
     */
    @SuppressWarnings("WeakerAccess")
    public static int microsOfMilli(DateTime dateTime, TimeZone timeZone) {
        if (dateTime == null || timeZone == null) {
            return io.deephaven.util.QueryConstants.NULL_INT;
        }

        return (int) Math.round(dateTime.getNanosPartial() / 1000d);
    }

    /**
     * Returns an int value of minutes since midnight for a {@link DateTime} in the specified time zone.
     *
     * @param dateTime The {@link DateTime} for which to find the minutes.
     * @param timeZone The {@link TimeZone} to use when interpreting the date/time.
     * @return A {@link QueryConstants#NULL_INT} if either input is null, otherwise, an int value of minutes since
     *         midnight for the date/time represented by the {@link DateTime} when interpreted in the specified time
     *         zone.
     */
    @SuppressWarnings("WeakerAccess")
    public static int minuteOfDay(DateTime dateTime, TimeZone timeZone) {
        if (dateTime == null || timeZone == null) {
            return io.deephaven.util.QueryConstants.NULL_INT;
        }

        return dateTime.getJodaDateTime(timeZone).getMinuteOfDay();
    }

    /**
     * Returns an int value of minutes since the top of the hour for a {@link DateTime} in the specified time zone.
     *
     * @param dateTime The {@link DateTime} for which to find the minutes.
     * @param timeZone The {@link TimeZone} to use when interpreting the date/time.
     * @return A {@link QueryConstants#NULL_INT} if either input is null, otherwise, an int value of minutes since the
     *         top of the hour for the date/time represented by the {@link DateTime} when interpreted in the specified
     *         time zone.
     */
    @SuppressWarnings("WeakerAccess")
    public static int minuteOfHour(DateTime dateTime, TimeZone timeZone) {
        if (dateTime == null || timeZone == null) {
            return io.deephaven.util.QueryConstants.NULL_INT;
        }

        return dateTime.getJodaDateTime(timeZone).getMinuteOfHour();
    }

    /**
     * Returns an int value for the month of a {@link DateTime} in the specified time zone.
     *
     * @param dateTime The {@link DateTime} for which to find the month.
     * @param timeZone The {@link TimeZone} to use when interpreting the date/time.
     * @return A {@link QueryConstants#NULL_INT} if either input is null, otherwise, an int value of the month for the
     *         date/time represented by the {@link DateTime} when interpreted in the specified time zone. January is 1,
     *         February is 2, etc.
     */
    @SuppressWarnings("WeakerAccess")
    public static int monthOfYear(DateTime dateTime, TimeZone timeZone) {
        if (dateTime == null || timeZone == null) {
            return io.deephaven.util.QueryConstants.NULL_INT;
        }

        return dateTime.getJodaDateTime(timeZone).getMonthOfYear();
    }

    /**
     * Returns an int value of seconds since midnight for a {@link DateTime} in the specified time zone.
     *
     * @param dateTime The {@link DateTime} for which to find the seconds.
     * @param timeZone The {@link TimeZone} to use when interpreting the date/time.
     * @return A {@link QueryConstants#NULL_INT} if either input is null, otherwise, an int value of seconds since
     *         midnight for the date/time represented by the {@link DateTime} when interpreted in the specified time
     *         zone.
     */
    @SuppressWarnings("WeakerAccess")
    public static int secondOfDay(DateTime dateTime, TimeZone timeZone) {
        if (dateTime == null || timeZone == null) {
            return io.deephaven.util.QueryConstants.NULL_INT;
        }

        return dateTime.getJodaDateTime(timeZone).getSecondOfDay();
    }

    /**
     * Returns an int value of seconds since the top of the minute for a {@link DateTime} in the specified time zone.
     *
     * @param dateTime The {@link DateTime} for which to find the seconds.
     * @param timeZone The {@link TimeZone} to use when interpreting the date/time.
     * @return A {@link QueryConstants#NULL_INT} if either input is null, otherwise, an int value of seconds since the
     *         top of the minute for the date/time represented by the {@link DateTime} when interpreted in the specified
     *         time zone.
     */
    @SuppressWarnings("WeakerAccess")
    public static int secondOfMinute(DateTime dateTime, TimeZone timeZone) {
        if (dateTime == null || timeZone == null) {
            return io.deephaven.util.QueryConstants.NULL_INT;
        }

        return dateTime.getJodaDateTime(timeZone).getSecondOfMinute();
    }

    /**
     * Returns an int value of the year for a {@link DateTime} in the specified time zone.
     *
     * @param dateTime The {@link DateTime} for which to find the year.
     * @param timeZone The {@link TimeZone} to use when interpreting the date/time.
     * @return A {@link QueryConstants#NULL_INT} if either input is null, otherwise, an int value of the year for the
     *         date/time represented by the {@link DateTime} when interpreted in the specified time zone.
     */
    public static int year(DateTime dateTime, TimeZone timeZone) {
        if (dateTime == null || timeZone == null) {
            return io.deephaven.util.QueryConstants.NULL_INT;
        }

        return dateTime.getJodaDateTime(timeZone).getYear();
    }

    /**
     * Returns an int value of the two-digit year for a {@link DateTime} in the specified time zone.
     *
     * @param dateTime The {@link DateTime} for which to find the year.
     * @param timeZone The {@link TimeZone} to use when interpreting the date/time.
     * @return A {@link QueryConstants#NULL_INT} if either input is null, otherwise, an int value of the two-digit year
     *         for the date/time represented by the {@link DateTime} when interpreted in the specified time zone.
     */
    @SuppressWarnings("WeakerAccess")
    public static int yearOfCentury(DateTime dateTime, TimeZone timeZone) {
        if (dateTime == null || timeZone == null) {
            return io.deephaven.util.QueryConstants.NULL_INT;
        }

        return dateTime.getJodaDateTime(timeZone).getYearOfCentury();
    }
    // endregion

    // region Base and Unit conversion

    //TODO: no equivalent
    /**
     * Returns the Excel double time format representation of a {@link DateTime}.
     *
     * @param dateTime The {@link DateTime} to convert.
     * @param timeZone The {@link TimeZone} to use when interpreting the date/time.
     * @return 0.0 if either input is null, otherwise, a double value containing the Excel double format representation
     *         of a {@link DateTime} in the specified time zone.
     */
    @SuppressWarnings("WeakerAccess")
    public static double getExcelDateTime(DateTime dateTime, TimeZone timeZone) {
        return getExcelDateTime(dateTime, timeZone.getTimeZone().toTimeZone());
    }

    //TODO: no equivalent
    /**
     * Returns the Excel double time format representation of a {@link DateTime}.
     *
     * @param dateTime The {@link DateTime} to convert.
     * @param timeZone The {@link java.util.TimeZone} to use when interpreting the date/time.
     * @return 0.0 if either input is null, otherwise, a double value containing the Excel double format representation
     *         of a {@link DateTime} in the specified time zone.
     */
    @SuppressWarnings("WeakerAccess")
    public static double getExcelDateTime(DateTime dateTime, java.util.TimeZone timeZone) {
        if (dateTime == null || timeZone == null) {
            return 0.0d;
        }
        long millis = dateTime.getMillis();

        return (double) (millis + timeZone.getOffset(millis)) / 86400000 + 25569;
    }

    //TODO: no equivalent
    /**
     * Returns the Excel double time format representation of a {@link DateTime}.
     *
     * @param dateTime The {@link DateTime} to convert.
     * @return 0.0 if the input is null, otherwise, a double value containing the Excel double format representation of
     *         a {@link DateTime} in the New York time zone.
     */
    @SuppressWarnings("WeakerAccess")
    public static double getExcelDateTime(DateTime dateTime) {
        return getExcelDateTime(dateTime, TimeZones.TZ_NEWYORK);
    }

    //TODO: no equivalent
    /**
     * Converts microseconds to nanoseconds.
     *
     * @param micros The long value of microseconds to convert.
     * @return A {@link QueryConstants#NULL_LONG} if the input is null. Throws a {@link DateTimeOverflowException} if
     *         the resultant value would exceed the range that can be stored in a long. Otherwise, returns a long
     *         containing the equivalent number of nanoseconds for the input in microseconds.
     */
    public static long microsToNanos(long micros) {
        if (micros == NULL_LONG) {
            return NULL_LONG;
        }
        if (Math.abs(micros) > MAX_CONVERTIBLE_MICROS) {
            throw new DateTimeOverflowException("Converting " + micros + " micros to nanos would overflow");
        }
        return micros * 1000;
    }

    //TODO: no equivalent
    /**
     * Converts nanoseconds to microseconds.
     *
     * @param nanos The long value of nanoseconds to convert.
     * @return A {@link QueryConstants#NULL_LONG} if the input is null. Otherwise, returns a long containing the
     *         equivalent number of microseconds for the input in nanoseconds.
     */
    @SuppressWarnings("WeakerAccess")
    public static long nanosToMicros(long nanos) {
        if (nanos == NULL_LONG) {
            return NULL_LONG;
        }
        return nanos / 1000;
    }

    //TODO: no equivalent
    /**
     * Converts a value of microseconds from Epoch in the UTC time zone to a {@link DateTime}.
     *
     * @param micros The long microseconds value to convert.
     * @return {@link QueryConstants#NULL_LONG} if the input is null, otherwise, a {@link DateTime} representation of
     *         the input.
     */
    public static DateTime microsToTime(long micros) {
        return nanosToDateTime(microsToNanos(micros));
    }

    /**
     * Converts milliseconds to nanoseconds.
     *
     * @param millis The long milliseconds value to convert.
     * @return {@link QueryConstants#NULL_LONG} if the input is equal to {@link QueryConstants#NULL_LONG}. Throws
     *         {@link DateTimeOverflowException} if the input is too large for conversion. Otherwise returns a long of
     *         the equivalent number of nanoseconds to the input.
     */
    public static long millisToNanos(long millis) {
        if (millis == NULL_LONG) {
            return NULL_LONG;
        }
        if (Math.abs(millis) > MAX_CONVERTIBLE_MILLIS) {
            throw new DateTimeOverflowException("Converting " + millis + " millis to nanos would overflow");
        }
        return millis * 1000000;
    }

    //TODO: no equivalent
    /**
     * Converts seconds to nanoseconds.
     *
     * @param seconds The long value of seconds to convert.
     * @return A {@link QueryConstants#NULL_LONG} if the input is null. Throws a {@link DateTimeOverflowException} if
     *         the resultant value would exceed the range that can be stored in a long. Otherwise, returns a long
     *         containing the equivalent number of nanoseconds for the input in seconds.
     */
    public static long secondsToNanos(long seconds) {
        if (seconds == NULL_LONG) {
            return NULL_LONG;
        }
        if (Math.abs(seconds) > MAX_CONVERTIBLE_SECONDS) {
            throw new DateTimeOverflowException("Converting " + seconds + " seconds to nanos would overflow");
        }

        return seconds * 1000000000L;
    }

    /**
     * Converts nanoseconds to milliseconds.
     *
     * @param nanos The long value of nanoseconds to convert.
     * @return A {@link QueryConstants#NULL_LONG} if the input is null. Otherwise, returns a long containing the
     *         equivalent number of milliseconds for the input in nanoseconds.
     */
    public static long nanosToMillis(long nanos) {
        if (nanos == NULL_LONG) {
            return NULL_LONG;
        }

        return nanos / 1000000;
    }

    /**
     * Converts a value of milliseconds from Epoch in the UTC time zone to a {@link DateTime}.
     *
     * @param millis The long milliseconds value to convert.
     * @return {@link QueryConstants#NULL_LONG} if the input is null, otherwise, a {@link DateTime} representation of
     *         the input.
     */
    public static DateTime millisToDateTime(long millis) {
        return nanosToDateTime(millisToNanos(millis));
    }

    //TODO: no equivalent
    /**
     * Converts a value of seconds from Epoch in the UTC time zone to a {@link DateTime}.
     *
     * @param seconds The long seconds value to convert.
     * @return {@link QueryConstants#NULL_LONG} if the input is null, otherwise, a {@link DateTime} representation of
     *         the input.
     */
    public static DateTime secondsToTime(long seconds) {
        return nanosToDateTime(secondsToNanos(seconds));
    }


    //TODO: no equivalent
    /**
     * Returns the current clock. The current clock is {@link #clock} if set, otherwise {@link Clock#system()}.
     *
     * @return the current clock
     */
    public static Clock currentClock() {
        return Objects.requireNonNullElse(clock, Clock.system());
    }

    private static long safeComputeNanos(long epochSecond, long nanoOfSecond) {
        if (epochSecond >= MAX_CONVERTIBLE_SECONDS) {
            throw new IllegalArgumentException("Numeric overflow detected during conversion of " + epochSecond
                    + " to nanoseconds");
        }

        return epochSecond * 1_000_000_000L + nanoOfSecond;
    }

    //TODO: no equivalent
    /**
     * Convert the specified instant to nanoseconds since epoch, or {@link QueryConstants#NULL_LONG null}.
     *
     * @param value the instant to convert
     *
     * @return nanoseconds since epoch or {@link QueryConstants#NULL_LONG null}
     */
    public static long toEpochNano(@Nullable final Instant value) {
        if (value == null) {
            return NULL_LONG;
        }

        return safeComputeNanos(value.getEpochSecond(), value.getNano());
    }

    //TODO: no equivalent
    /**
     * Convert the specified {@link ZonedDateTime} to nanoseconds since epoch, or {@link QueryConstants#NULL_LONG null}.
     *
     * @param value the instant to convert
     *
     * @return nanoseconds since epoch or {@link QueryConstants#NULL_LONG null}
     */
    public static long toEpochNano(@Nullable final ZonedDateTime value) {
        if (value == null) {
            return NULL_LONG;
        }

        return safeComputeNanos(value.toEpochSecond(), value.getNano());
    }

    //TODO: no equivalent
    /**
     * Convert nanos since epoch to an {@link Instant} value.
     *
     * @param nanos nanoseconds since epoch
     * @return a new {@link Instant} or null if nanos was {@link QueryConstants#NULL_LONG}.
     */
    @Nullable
    public static Instant makeInstant(final long nanos) {
        return nanos == NULL_LONG ? null : Instant.ofEpochSecond(nanos / 1_000_000_000L, nanos % 1_000_000_000L);
    }

    //TODO: no equivalent
    /**
     * Converts nanos of epoch to a {@link ZonedDateTime} using the {@link TimeZone#TZ_DEFAULT default} time zone.
     *
     * @param nanos nanoseconds since epoch
     * @return a new {@link ZonedDateTime} or null if nanos was {@link QueryConstants#NULL_LONG}.
     */
    @Nullable
    public static ZonedDateTime makeZonedDateTime(final long nanos) {
        return makeZonedDateTime(nanos, TimeZone.TZ_DEFAULT.getZoneId());
    }

    //TODO: no equivalent
    /**
     * Converts nanos of epoch to a {@link ZonedDateTime}.
     *
     * @param nanos nanoseconds since epoch
     * @param timeZone the {@link TimeZone time zone}
     *
     * @return a new {@link ZonedDateTime} or null if nanos was {@link QueryConstants#NULL_LONG}.
     */
    @Nullable
    public static ZonedDateTime makeZonedDateTime(final long nanos, @NotNull final TimeZone timeZone) {
        return makeZonedDateTime(nanos, timeZone.getZoneId());
    }

    //TODO: no equivalent
    /**
     * Converts nanos of epoch to a {@link ZonedDateTime}.
     *
     * @param nanos nanoseconds since epoch
     * @param zone the {@link ZoneId time zone}
     *
     * @return a new {@link ZonedDateTime} or null if nanos was {@link QueryConstants#NULL_LONG}.
     */
    @Nullable
    public static ZonedDateTime makeZonedDateTime(final long nanos, ZoneId zone) {
        // noinspection ConstantConditions
        return nanos == NULL_LONG ? null : ZonedDateTime.ofInstant(makeInstant(nanos), zone);
    }

    //TODO: no equivalent
    /**
     * Converts a {@link DateTime} to a {@link ZonedDateTime}.
     *
     * @param dateTime The a {@link DateTime} to convert.
     * @return A {@link ZonedDateTime} using the default time zone for the session as indicated by
     *         {@link TimeZone#TZ_DEFAULT}.
     */
    @Nullable
    public static ZonedDateTime getZonedDateTime(final @Nullable DateTime dateTime) {
        return getZonedDateTime(dateTime, TimeZone.TZ_DEFAULT);
    }

    //TODO: no equivalent
    /**
     * Converts a {@link DateTime} to a {@link ZonedDateTime}.
     *
     * @param dateTime The a {@link DateTime} to convert.
     * @param timeZone The {@link TimeZone} to use for the conversion.
     * @return A {@link ZonedDateTime} using the specified time zone. or null if dateTime was null
     */
    @Nullable
    public static ZonedDateTime getZonedDateTime(@Nullable final DateTime dateTime, @NotNull final TimeZone timeZone) {
        if (dateTime == null) {
            return null;
        }

        final ZoneId zone = timeZone.getTimeZone().toTimeZone().toZoneId();
        return dateTime.toZonedDateTime(zone);
    }

    //TODO: no equivalent
    /**
     * Converts a {@link DateTime} to a {@link ZonedDateTime}.
     *
     * @param dateTime The a {@link DateTime} to convert.
     * @param timeZone The {@link ZoneId} to use for the conversion.
     * @return A {@link ZonedDateTime} using the specified time zone. or null if dateTime was null
     */
    @Nullable
    public static ZonedDateTime getZonedDateTime(@Nullable final DateTime dateTime, @NotNull final ZoneId timeZone) {
        if (dateTime == null) {
            return null;
        }

        return dateTime.toZonedDateTime(timeZone);
    }

    //TODO: no equivalent
    /**
     * Converts a {@link ZonedDateTime} to a {@link DateTime}.
     *
     * @param zonedDateTime The a {@link ZonedDateTime} to convert.
     * @throws DateTimeOverflowException if the input is out of the range for a {@link DateTime}, otherwise, a
     *         {@link DateTime} version of the input.
     */
    @Nullable
    public static DateTime toDateTime(@Nullable final ZonedDateTime zonedDateTime) {
        if (zonedDateTime == null) {
            return null;
        }

        int nanos = zonedDateTime.getNano();
        long seconds = zonedDateTime.toEpochSecond();

        long limit = (Long.MAX_VALUE - nanos) / DateTimeUtils.SECOND;
        if (seconds >= limit) {
            throw new DateTimeOverflowException("Overflow: cannot convert " + zonedDateTime + " to new DateTime");
        }

        return new DateTime(nanos + (seconds * DateTimeUtils.SECOND));
    }
    // endregion

    // region Query Helper Methods

    //TODO: separate now() methods for the current clock and the system clock? -- adjust docs accordingly
    //TODO: Equivalent to {@code DateTime.of(currentClock())}.
    /**
     * Provides the current DateTime.
     * *****TODOEquivalent to {@code DateTime.of(currentClock())}.
     *
     * @return the current date time
     */
    @ScriptApi
    public static DateTime now() {
        return DateTime.of(currentClock());
    }

    //TODO: no equivalent
    /**
     * Equivalent to {@code DateTime.ofMillis(currentClock())}.
     *
     * @return the current date time
     */
    public static DateTime currentTimeMillis() {
        return DateTime.ofMillis(currentClock());
    }

    private abstract static class CachedDate {

        final TimeZone timeZone;

        String value;
        long valueExpirationTimeMillis;

        private CachedDate(@NotNull final TimeZone timeZone) {
            this.timeZone = timeZone;
        }

        private TimeZone getTimeZone() {
            return timeZone;
        }

        public String get() {
            return get(System.currentTimeMillis());
        }

        public synchronized String get(final long currentTimeMillis) {
            if (currentTimeMillis >= valueExpirationTimeMillis) {
                update(currentTimeMillis);
            }
            return value;
        }

        abstract void update(long currentTimeMillis);
    }

    private static class CachedCurrentDate extends CachedDate {

        private CachedCurrentDate(@NotNull final TimeZone timeZone) {
            super(timeZone);
        }

        @Override
        void update(final long currentTimeMillis) {
            value = formatDate(millisToDateTime(currentTimeMillis), timeZone);
            valueExpirationTimeMillis = new org.joda.time.DateTime(currentTimeMillis, timeZone.getTimeZone())
                    .withFieldAdded(DurationFieldType.days(), 1).withTimeAtStartOfDay().getMillis();
        }
    }

    private static class CachedDateKey<CACHED_DATE_TYPE extends CachedDate>
            extends KeyedObjectKey.Basic<TimeZone, CACHED_DATE_TYPE> {

        @Override
        public TimeZone getKey(final CACHED_DATE_TYPE cachedDate) {
            return cachedDate.timeZone;
        }
    }

    private static final KeyedObjectHashMap<TimeZone, CachedCurrentDate> cachedCurrentDates =
            new KeyedObjectHashMap<>(new CachedDateKey<CachedCurrentDate>());

    //TODO: no equivalent
    /**
     * Returns a String of the current date in the specified {@link TimeZone}.
     *
     * @param timeZone The {@link TimeZone} to reference when evaluating the current date for "now".
     * @return A String in format yyyy-MM-dd.
     */
    public static String currentDate(TimeZone timeZone) {
        return cachedCurrentDates.putIfAbsent(timeZone, CachedCurrentDate::new).get();
    }

    /**
     * Converts a value of nanoseconds from Epoch to a {@link DateTime}.
     *
     * @param nanos The long nanoseconds since Epoch value to convert.
     * @return A DateTime for {@code nanos}, or {@code null} if {@code nanos} is equal to
     *         {@link QueryConstants#NULL_LONG NULL_LONG}.
     */
    public static DateTime nanosToDateTime(long nanos) {
        return nanos == NULL_LONG ? null : new DateTime(nanos);
    }

    //TODO: no equivalent
    /**
     * Converts a long offset from Epoch value to a {@link DateTime}. This method uses expected date ranges to infer
     * whether the passed value is in milliseconds, microseconds, or nanoseconds. Thresholds used are
     * {@link TimeConstants#MICROTIME_THRESHOLD} divided by 1000 for milliseconds, as-is for microseconds, and
     * multiplied by 1000 for nanoseconds. The value is tested to see if its ABS exceeds the threshold. E.g. a value
     * whose ABS is greater than 1000 * {@link TimeConstants#MICROTIME_THRESHOLD} will be treated as nanoseconds.
     *
     * @param epoch The long Epoch offset value to convert.
     * @return null, if the input is equal to {@link QueryConstants#NULL_LONG}, otherwise a {@link DateTime} based on
     *         the inferred conversion.
     */
    @SuppressWarnings("WeakerAccess")
    public static DateTime autoEpochToTime(long epoch) {
        return new DateTime(autoEpochToNanos(epoch));
    }

    //TODO: no equivalent
    /**
     * Converts a long offset from Epoch value to a nanoseconds as a long. This method uses expected date ranges to
     * infer whether the passed value is in milliseconds, microseconds, or nanoseconds. Thresholds used are
     * {@link TimeConstants#MICROTIME_THRESHOLD} divided by 1000 for milliseconds, as-is for microseconds, and
     * multiplied by 1000 for nanoseconds. The value is tested to see if its ABS exceeds the threshold. E.g. a value
     * whose ABS is greater than 1000 * {@link TimeConstants#MICROTIME_THRESHOLD} will be treated as nanoseconds.
     *
     * @param epoch The long Epoch offset value to convert.
     * @return null, if the input is equal to {@link QueryConstants#NULL_LONG}, otherwise a nanoseconds value
     *         corresponding to the passed in epoch value.
     */
    public static long autoEpochToNanos(final long epoch) {
        if (epoch == NULL_LONG) {
            return epoch;
        }
        final long absEpoch = Math.abs(epoch);
        if (absEpoch > 1000 * TimeConstants.MICROTIME_THRESHOLD) { // Nanoseconds
            return epoch;
        }
        if (absEpoch > TimeConstants.MICROTIME_THRESHOLD) { // Microseconds
            return 1000 * epoch;
        }
        if (absEpoch > TimeConstants.MICROTIME_THRESHOLD / 1000) { // Milliseconds
            return 1000 * 1000 * epoch;
        }
        // Seconds
        return 1000 * 1000 * 1000 * epoch;
    }

    //TODO: no equivalent
    /**
     * Returns a {@link DateTime} value based on a starting value and a {@link Period} to add to it, but with a cap max
     * value which is returned in case the starting value plus period exceeds the cap.
     *
     * @param original The starting {@link DateTime} value.
     * @param period The {@link Period} to add to dateTime.
     * @param cap A {@link DateTime} value to use as the maximum return value.
     * @return a null {@link DateTime} if either original or period are null; the starting {@link DateTime} plus the
     *         specified period, if the result is not too large for a DateTime and does not exceed the cap value; the
     *         cap value if this is less than offset plus period. Throws a {@link DateTimeOverflowException
     *         DateTimeOverflowException} if the resultant value is more than max long nanoseconds from Epoch.
     */
    public static DateTime cappedTimeOffset(DateTime original, Period period, DateTime cap) {
        DateTime offset = DateTimeUtils.plus(original, period);
        return (offset.compareTo(cap) > 0) ? cap : offset;
    }

    /**
     * Returns a {@link DateTime} value, which is at the starting (lower) end of a time range defined by the interval
     * nanoseconds. For example, a 5*MINUTE intervalNanos value would return the date/time value for the start of the
     * five minute window that contains the input date time.
     *
     * @param dateTime The {@link DateTime} for which to evaluate the start of the containing window.
     * @param intervalNanos The size of the window in nanoseconds.
     * @return Null if either input is null, otherwise a {@link DateTime} representing the start of the window.
     */
    public static DateTime lowerBin(DateTime dateTime, long intervalNanos) {
        if (dateTime == null || intervalNanos == NULL_LONG) {
            return null;
        }

        return nanosToDateTime(Numeric.lowerBin(dateTime.getNanos(), intervalNanos));
    }

    /**
     * Returns a {@link DateTime} value, which is at the starting (lower) end of a time range defined by the interval
     * nanoseconds. For example, a 5*MINUTE intervalNanos value would return the date/time value for the start of the
     * five minute window that contains the input date time.
     *
     * @param dateTime The {@link DateTime} for which to evaluate the start of the containing window.
     * @param intervalNanos The size of the window in nanoseconds.
     * @param offset The window start offset in nanoseconds. For example, a value of MINUTE would offset all windows by
     *        one minute.
     * @return Null if either input is null, otherwise a {@link DateTime} representing the start of the window.
     */
    public static DateTime lowerBin(DateTime dateTime, long intervalNanos, long offset) {
        if (dateTime == null || intervalNanos == NULL_LONG || offset == NULL_LONG) {
            return null;
        }

        return nanosToDateTime(Numeric.lowerBin(dateTime.getNanos() - offset, intervalNanos) + offset);
    }

    /**
     * Returns a {@link DateTime} value, which is at the ending (upper) end of a time range defined by the interval
     * nanoseconds. For example, a 5*MINUTE intervalNanos value would return the date/time value for the end of the five
     * minute window that contains the input date time.
     *
     * @param dateTime The {@link DateTime} for which to evaluate the end of the containing window.
     * @param intervalNanos The size of the window in nanoseconds.
     * @return Null if either input is null, otherwise a {@link DateTime} representing the end of the window.
     */
    public static DateTime upperBin(DateTime dateTime, long intervalNanos) {
        if (dateTime == null || intervalNanos == NULL_LONG) {
            return null;
        }

        return nanosToDateTime(Numeric.upperBin(dateTime.getNanos(), intervalNanos));
    }

    /**
     * Returns a {@link DateTime} value, which is at the ending (upper) end of a time range defined by the interval
     * nanoseconds. For example, a 5*MINUTE intervalNanos value would return the date/time value for the end of the five
     * minute window that contains the input date time.
     *
     * @param dateTime The {@link DateTime} for which to evaluate the end of the containing window.
     * @param intervalNanos The size of the window in nanoseconds.
     * @param offset The window start offset in nanoseconds. For example, a value of MINUTE would offset all windows by
     *        one minute.
     * @return Null if either input is null, otherwise a {@link DateTime} representing the end of the window.
     */
    public static DateTime upperBin(DateTime dateTime, long intervalNanos, long offset) {
        if (dateTime == null || intervalNanos == NULL_LONG
                || offset == NULL_LONG) {
            return null;
        }

        return nanosToDateTime(Numeric.upperBin(dateTime.getNanos() - offset, intervalNanos) + offset);
    }
    // endregion

    // + can only result in flow if both positive or both negative
    private static long checkOverflowPlus(final long l1, final long l2, final boolean minusOperation) {
        if (l1 > 0 && l2 > 0 && Long.MAX_VALUE - l1 < l2) {
            final String message = minusOperation
                    ? "Subtracting " + -l2 + " nanos from " + l1 + " would overflow"
                    : "Adding " + l2 + " nanos to " + l1 + " would overflow";
            throw new DateTimeOverflowException(message);
        }

        if (l1 < 0 && l2 < 0) {
            return checkUnderflowMinus(l1, -l2, false);
        }

        return l1 + l2;
    }

    // - can only result in flow if one is positive and one is negative
    private static long checkUnderflowMinus(final long l1, final long l2, final boolean minusOperation) {
        if (l1 < 0 && l2 > 0 && Long.MIN_VALUE + l2 > -l1) {
            final String message = minusOperation
                    ? "Subtracting " + l2 + " nanos from " + l1 + " would underflow"
                    : "Adding " + -l2 + " nanos to " + l1 + " would underflow";
            throw new DateTimeOverflowException(message);
        }

        if (l1 > 0 && l2 < 0) {
            return checkOverflowPlus(l1, -l2, true);
        }

        return l1 - l2;
    }

    //TODO: no equivalent
    /**
     * Converts an expression, replacing DateTime and Period literals with references to constant DateTime/Period
     * instances.
     *
     * @param formula The formula to convert.
     * @return A {@link Result} object, which includes the converted formula string, a string of instance variable
     *         declarations, and a map describing the names and types of these instance variables.
     *
     * @throws Exception If any error occurs or a literal value cannot be parsed.
     */
    // TODO: This should probably be handled in LanguageParser.accept(CharLiteralExpr, StringBuilder).
    public static Result convertExpression(String formula) throws Exception { // TODO: Why throw Exception?
        final StringBuilder instanceVariablesString = new StringBuilder();
        final HashMap<String, Class<?>> newVariables = new HashMap<>();

        final StringBuilder convertedFormula = new StringBuilder();

        int localDateIndex = 0;
        int dateTimeIndex = 0;
        int timeIndex = 0;
        int periodIndex = 0;

        final Matcher matcher = Pattern.compile("'[^']*'").matcher(formula);

        while (matcher.find()) {
            String s = formula.substring(matcher.start() + 1, matcher.end() - 1);

            if (s.length() <= 1) {
                // leave chars and also bad empty ones alone
                continue;
            }

            if (toDateTimeQuiet(s) != null) {
                matcher.appendReplacement(convertedFormula, "_date" + dateTimeIndex);
                instanceVariablesString.append("        private DateTime _date").append(dateTimeIndex)
                        .append("=DateTimeUtils.toDateTime(\"")
                        .append(formula, matcher.start() + 1, matcher.end() - 1).append("\");\n");
                newVariables.put("_date" + dateTimeIndex, DateTime.class);

                dateTimeIndex++;
            } else if (convertDateQuiet(s) != null) {
                matcher.appendReplacement(convertedFormula, "_localDate" + localDateIndex);
                instanceVariablesString.append("        private java.time.LocalDate _localDate").append(localDateIndex)
                        .append("=DateTimeUtils.convertDate(\"").append(formula, matcher.start() + 1, matcher.end() - 1)
                        .append("\");\n");
                newVariables.put("_localDate" + localDateIndex, LocalDate.class);
                localDateIndex++;
            } else if (toNanosQuiet(s) != NULL_LONG) {
                matcher.appendReplacement(convertedFormula, "_time" + timeIndex);
                instanceVariablesString.append("        private long _time").append(timeIndex)
                        .append("=DateTimeUtils.convertTime(\"").append(formula, matcher.start() + 1, matcher.end() - 1)
                        .append("\");\n");
                newVariables.put("_time" + timeIndex, long.class);

                timeIndex++;
            } else if (toPeriodQuiet(s) != null) {
                matcher.appendReplacement(convertedFormula, "_period" + periodIndex);
                instanceVariablesString.append("        private Period _period").append(periodIndex)
                        .append("=DateTimeUtils.convertPeriod(\"")
                        .append(formula, matcher.start() + 1, matcher.end() - 1)
                        .append("\");\n");
                newVariables.put("_period" + periodIndex, Period.class);

                periodIndex++;
            } else if (convertLocalTimeQuiet(s) != null) {
                matcher.appendReplacement(convertedFormula, "_localTime" + timeIndex);
                instanceVariablesString.append("        private java.time.LocalTime _localTime").append(timeIndex)
                        .append("=DateTimeUtils.convertLocalTime(\"")
                        .append(formula, matcher.start() + 1, matcher.end() - 1).append("\");\n");
                newVariables.put("_localTime" + timeIndex, LocalTime.class);
                timeIndex++;
            } else {
                throw new Exception("Cannot parse datetime/time/period : " + s);
            }
        }

        matcher.appendTail(convertedFormula);

        return new Result(convertedFormula.toString(), instanceVariablesString.toString(), newVariables);
    }

    //TODO: no equivalent
    /**
     * Converts a String date/time to nanoseconds from Epoch or a nanoseconds period. Three patterns are supported:
     * <p>
     * yyyy-MM-ddThh:mm:ss[.nnnnnnnnn] TZ for date/time values
     * </p>
     * <p>
     * hh:mm:ss[.nnnnnnnnn] for time values
     * </p>
     * <p>
     * Period Strings in the form of numbertype, e.g. 1W for one week, and Tnumbertype for times, e.g. T1M for one
     * minute
     * </p>
     *
     * @param formula The String to be evaluated and converted. Optionally, but preferred, enclosed in straight single
     *        ticks.
     * @return A long value representing an Epoch offset in nanoseconds for a time or date/time, or a duration in
     *         nanoseconds for a period. Throws {@link DateTimeOverflowException} if the resultant value would be longer
     *         than max long, or {@link IllegalArgumentException} if expression cannot be evaluated.
     */
    public static long expressionToNanos(String formula) {
        if (!formula.startsWith("'")) {
            formula = '\'' + formula + '\'';
        }
        Matcher matcher = Pattern.compile("'[^'][^']+'").matcher(formula);

        boolean result = matcher.find();

        String s = formula.substring(matcher.start() + 1, matcher.end() - 1);
        final DateTime dateTime = toDateTimeQuiet(s);
        if (dateTime != null) {
            return dateTime.getNanos();
        }
        long time = toNanosQuiet(s);
        if (time != NULL_LONG) {
            return time;
        }
        final Period period = toPeriodQuiet(s);
        if (period != null) {
            try {
                return StrictMath.multiplyExact(period.getJodaPeriod().toStandardDuration().getMillis(),
                        period.isPositive() ? 1_000_000L : -1_000_000L);
            } catch (ArithmeticException ex) {
                throw new DateTimeOverflowException("Period length in nanoseconds exceeds Long.MAX_VALUE : " + s, ex);
            }
        }
        throw new IllegalArgumentException("Cannot parse datetime/time/period : " + s);
    }

    //TODO: no equivalent
    /**
     * Attempt to convert the given string to a LocalDate. This should <b>not</b> accept dates with times, as we want
     * those to be interpreted as DateTime values. The ideal date format is YYYY-MM-DD since it's the least ambiguous,
     * but this method also parses slash-delimited dates according to the system "date style".
     *
     * @param s the date string to convert
     * @throws RuntimeException if the date cannot be converted, otherwise returns a {@link LocalDate}
     */
    @SuppressWarnings("WeakerAccess")
    public static LocalDate convertDate(String s) {
        final LocalDate ret = convertDateQuiet(s);

        if (ret == null) {
            throw new RuntimeException("Cannot parse date : " + s);
        }

        return ret;
    }

    //TODO: think through toDateTime vs toDateTimeQuiet
    /**
     * Converts a datetime string to a {@link DateTime} object.
     * <p>
     * Supports ISO 8601 format ({@link DateTimeFormatter#ISO_INSTANT}), "yyyy-MM-ddThh:mm:ss[.SSSSSSSSS] TZ", and others.
     *
     * @param s String to be converted
     * @return a {@link DateTime} represented by the input string.
     * @throws RuntimeException if the String cannot be converted, otherwise a {@link DateTime} from the parsed String.
     */
    public static DateTime toDateTime(String s) {
        DateTime ret = toDateTimeQuiet(s);

        if (ret == null) {
            throw new RuntimeException("Cannot parse datetime : " + s);
        }

        return ret;
    }

    //TODO: think through toNanos vs toNanosQuiet
    /**
     * Converts a time string to nanoseconds. The format for the String is "hh:mm:ss[.nnnnnnnnn]".
     *
     * @param s String to be converted.
     * @return the number of nanoseconds represented by the string.
     * @throws RuntimeException if the String cannot be parsed.
     */
    public static long toNanos(String s) {
        long ret = toNanosQuiet(s);

        if (ret == NULL_LONG) {
            throw new RuntimeException("Cannot parse time : " + s);
        }

        return ret;
    }

    //TODO: think through toPeriod vs toPeriodQuiet
    /**
     * Converts a String into a {@link Period} object.
     *
     * @param s a string in the form of nYnMnWnDTnHnMnS, with n being numeric values, e.g. 1W for one week, T1M for
     *          one minute, 1WT1H for one week plus one hour
     * @return a {@link Period} object.
     * @throws RuntimeException if the String cannot be parsed.
     */
    @SuppressWarnings("WeakerAccess")
    public static Period toPeriod(String s) {
        Period ret = toPeriodQuiet(s);

        if (ret == null) {
            throw new RuntimeException("Cannot parse period : " + s);
        }

        return ret;
    }

    private static int extractTwoDigitNum(String s, int startIndex) {
        return (s.charAt(startIndex) - '0') * 10 + (s.charAt(startIndex + 1) - '0');
    }

    private static int extractThreeDigitNum(String s, int startIndex) {
        return (s.charAt(startIndex) - '0') * 100 + (s.charAt(startIndex + 1) - '0') * 10
                + (s.charAt(startIndex + 2) - '0');
    }

    private static int extractFourDigitNum(String s, int startIndex) {
        return (s.charAt(startIndex) - '0') * 1000 + (s.charAt(startIndex + 1) - '0') * 100
                + (s.charAt(startIndex + 2) - '0') * 10 + (s.charAt(startIndex + 3) - '0');
    }

    private static int extractSixDigitNum(String s, int startIndex) {
        int result = 0;
        for (int i = startIndex; i < startIndex + 6; i++) {
            result = result * 10 + s.charAt(i) - '0';
        }
        return result;
    }

    //TODO: no equivalent
    /**
     * Converts a time String in the form hh:mm:ss[.nnnnnnnnn] to a {@link LocalTime}.
     *
     * @param s The String to convert.
     * @return null if the String cannot be parsed, otherwise a {@link LocalTime}.
     */
    public static LocalTime convertLocalTimeQuiet(String s) {
        try {
            // private static final Pattern LOCAL_TIME_PATTERN =
            // Pattern.compile("([0-9][0-9]):?([0-9][0-9])?:?([0-9][0-9])?(\\.([0-9]{1,9}))?");
            final Matcher matcher = LOCAL_TIME_PATTERN.matcher(s);
            if (matcher.matches()) {
                final int hour = Integer.parseInt(matcher.group(1)); // hour is the only required field
                final int minute = matcher.group(2) != null ? Integer.parseInt(matcher.group(2)) : 0;
                final int second = matcher.group(3) != null ? Integer.parseInt(matcher.group(3)) : 0;
                final int nanos;
                if (matcher.group(4) != null) {
                    final String fractionStr = matcher.group(5); // group 5 excludes the decimal pt
                    nanos = Integer.parseInt(fractionStr) * (int) Math.pow(10, 9 - fractionStr.length());
                } else {
                    nanos = 0;
                }
                return LocalTime.of(hour, minute, second, nanos);
            }
        } catch (Exception ex) {
            return null;
        }
        return null;
    }

    //TODO: no equivalent
    /**
     * Attempt to convert the given string to a LocalDate. This should <b>not</b> accept dates with times, as we want
     * those to be interpreted as DateTime values. The ideal date format is YYYY-MM-DD since it's the least ambiguous.
     *
     * @param s the date string to convert
     * @return the LocalDate formatted using the default date style.
     */
    public static LocalDate convertDateQuiet(String s) {
        return convertDateQuiet(s, DATE_STYLE);
    }

    private static LocalDate matchStdDate(Pattern pattern, String s) {
        final Matcher matcher = pattern.matcher(s);
        if (matcher.matches()) {
            final int year = Integer.parseInt(matcher.group("year"));
            final int month = Integer.parseInt(matcher.group("month"));
            final int dayOfMonth = Integer.parseInt(matcher.group("day"));
            return LocalDate.of(year, month, dayOfMonth);
        }
        return null;
    }

    /**
     * Attempt to convert the given string to a LocalDate. This should <b>not</b> accept dates with times, as we want
     * those to be interpreted as DateTime values. The ideal date format is YYYY-MM-DD since it's the least ambiguous.
     *
     * @param s the date string
     * @param dateStyle indicates how to interpret slash-delimited dates
     * @return the LocalDate
     */
    public static LocalDate convertDateQuiet(String s, DateStyle dateStyle) {
        try {
            LocalDate localDate = matchStdDate(STD_DATE_PATTERN, s);
            if (localDate != null) {
                return localDate;
            }
            localDate = matchStdDate(STD_DATE_PATTERN2, s);
            if (localDate != null) {
                return localDate;
            }

            // see if we can match one of the slash-delimited styles, the interpretation of which requires knowing the
            // system date style setting (for example Europeans often write dates as d/m/y).
            final Matcher slashMatcher = SLASH_DATE_PATTERN.matcher(s);
            if (slashMatcher.matches()) {
                final String yearGroup, monthGroup, dayGroup, yearFinal2DigitsGroup;
                // note we have nested groups which allow us to detect 2 vs 4 digit year
                // (groups 2 and 5 are the optional last 2 digits)
                switch (dateStyle) {
                    case MDY:
                        dayGroup = "part2";
                        monthGroup = "part1";
                        yearGroup = "part3";
                        yearFinal2DigitsGroup = "part3sub2";
                        break;
                    case DMY:
                        dayGroup = "part1";
                        monthGroup = "part2";
                        yearGroup = "part3";
                        yearFinal2DigitsGroup = "part3sub2";
                        break;
                    case YMD:
                        dayGroup = "part3";
                        monthGroup = "part2";
                        yearGroup = "part1";
                        yearFinal2DigitsGroup = "part1sub2";
                        break;
                    default:
                        throw new IllegalStateException("Unsupported DateStyle: " + DATE_STYLE);
                }
                final int year;
                // for 2 digit years, lean on java's standard interpretation
                if (slashMatcher.group(yearFinal2DigitsGroup) == null) {
                    year = Year.parse(slashMatcher.group(yearGroup), TWO_DIGIT_YR_FORMAT).getValue();
                } else {
                    year = Integer.parseInt(slashMatcher.group(yearGroup));
                }
                final int month = Integer.parseInt(slashMatcher.group(monthGroup));
                final int dayOfMonth = Integer.parseInt(slashMatcher.group(dayGroup));
                return LocalDate.of(year, month, dayOfMonth);
            }
        } catch (Exception ex) {
            return null;
        }
        return null;
    }

    //TODO: think through toDateTime vs toDateTimeQuiet
    /**
     * Converts a datetime string to a {@link DateTime} object.
     * <p>
     * Supports ISO 8601 format ({@link DateTimeFormatter#ISO_INSTANT}), "yyyy-MM-ddThh:mm:ss[.SSSSSSSSS] TZ", and others.
     *
     * @param s String to be converted
     * @return a {@link DateTime} represented by the input string, or null if the format is not recognized or an exception occurs.
     */
    public static DateTime toDateTimeQuiet(final String s) {
        try {
            return DateTime.of(Instant.parse(s));
        } catch (DateTimeParseException e) {
            // ignore
        }
        try {
            TimeZone timeZone = null;
            String dateTimeString = null;
            if (DATETIME_PATTERN.matcher(s).matches()) {
                int spaceIndex = s.indexOf(' ');
                if (spaceIndex == -1) { // no timezone
                    return null;
                }
                timeZone = TimeZone.valueOf("TZ_" + s.substring(spaceIndex + 1).trim().toUpperCase());
                dateTimeString = s.substring(0, spaceIndex);
            }

            if (timeZone == null) {
                return null;
            }
            int decimalIndex = dateTimeString.indexOf('.');
            if (decimalIndex == -1) {
                return new DateTime(
                        millisToNanos(new org.joda.time.DateTime(dateTimeString, timeZone.getTimeZone()).getMillis()));
            } else {
                final long subsecondNanos = parseNanos(dateTimeString.substring(decimalIndex + 1));

                return new DateTime(millisToNanos(new org.joda.time.DateTime(dateTimeString.substring(0, decimalIndex),
                        timeZone.getTimeZone()).getMillis()) + subsecondNanos);
            }
        } catch (Exception e) {
            // shouldn't get here too often, but somehow something snuck through. we'll just return null below...
        }

        return null;
    }

    /**
     * Converts a String of digits of any length to a nanoseconds long value. Will ignore anything longer than 9 digits,
     * and will throw a NumberFormatException if any non-numeric character is found. Strings shorter than 9 digits will
     * be interpreted as sub-second values to the right of the decimal point.
     *
     * @param input The String to convert
     * @return long value in nanoseconds
     */
    private static long parseNanos(@NotNull final String input) {
        long result = 0;
        for (int i = 0; i < 9; i++) {
            result *= 10;
            final int digit;
            if (i >= input.length()) {
                digit = 0;
            } else {
                digit = Character.digit(input.charAt(i), 10);
                if (digit < 0) {
                    throw new NumberFormatException("Invalid character for nanoseconds conversion: " + input.charAt(i));
                }
            }
            result += digit;
        }
        return result;
    }

    //TODO: think through toNanos vs toNanosQuiet
    /**
     * Converts a time string to nanoseconds. The format for the String is "hh:mm:ss[.nnnnnnnnn]".
     *
     * @param s String to be converted.
     * @return {@link QueryConstants#NULL_LONG} if the String cannot be parsed, otherwise a the number of nanoseconds represented by the string.
     */
    public static long toNanosQuiet(String s) {
        try {
            if (TIME_AND_DURATION_PATTERN.matcher(s).matches()) {
                long multiplier = 1;
                long dayNanos = 0;
                long subsecondNanos = 0;

                if (s.charAt(0) == '-') {
                    multiplier = -1;

                    s = s.substring(1);
                }

                int tIndex = s.indexOf('T');

                if (tIndex != -1) {
                    dayNanos = 86400000000000L * Integer.parseInt(s.substring(0, tIndex));

                    s = s.substring(tIndex + 1);
                }

                int decimalIndex = s.indexOf('.');

                if (decimalIndex != -1) {
                    subsecondNanos = parseNanos(s.substring(decimalIndex + 1));

                    s = s.substring(0, decimalIndex);
                }

                String[] tokens = s.split(":");

                if (tokens.length == 2) { // hh:mm
                    return multiplier
                            * (1000000000L * (3600 * Integer.parseInt(tokens[0]) + 60 * Integer.parseInt(tokens[1]))
                                    + dayNanos + subsecondNanos);
                } else if (tokens.length == 3) { // hh:mm:ss
                    return multiplier
                            * (1000000000L * (3600 * Integer.parseInt(tokens[0]) + 60 * Integer.parseInt(tokens[1])
                                    + Integer.parseInt(tokens[2])) + dayNanos + subsecondNanos);
                }
            }
        } catch (Exception e) {
            // shouldn't get here too often, but somehow something snuck through. we'll just return null below...
        }

        return NULL_LONG;
    }

    //TODO: think through toPeriod vs toPeriodQuiet
    /**
     * Converts a String into a {@link Period} object.
     *
     * @param s a string in the form of nYnMnWnDTnHnMnS, with n being numeric values, e.g. 1W for one week, T1M for
     *          one minute, 1WT1H for one week plus one hour
     * @return a {@link Period} object, or null if the string can not be parsed.
     */
    public static Period toPeriodQuiet(String s) {
        if (s.length() <= 1) {
            return null;
        }

        try {
            if (PERIOD_PATTERN.matcher(s).matches()) {
                return new Period(s);
            }
        } catch (Exception e) {
            // shouldn't get here too often, but somehow something snuck through. we'll just return null below...
        }

        return null;
    }

    //TODO: no equivalent
    /**
     * Returns a {@link ChronoField} indicating the level of precision in a String time value.
     *
     * @param timeDef The time String to evaluate.
     * @return null if the time String cannot be parsed, otherwise a {@link ChronoField} for the finest units in the
     *         String (e.g. "10:00:00" would yield SecondOfMinute).
     */
    public static ChronoField getFinestDefinedUnit(String timeDef) {
        Matcher dtMatcher = CAPTURING_DATETIME_PATTERN.matcher(timeDef);
        if (dtMatcher.matches()) {
            DateGroupId[] parts = DateGroupId.values();
            for (int i = parts.length - 1; i >= 0; i--) {
                String part = dtMatcher.group(parts[i].id);
                if (part != null && !part.isEmpty()) {
                    return parts[i].field;
                }
            }
        }

        return null;
    }

    /**
     * A container object for the result of {@link #convertExpression(String)}, which includes the converted formula
     * String, a String of instance variable declarations, and a map describing the names and types of these instance
     * variables.
     */
    public static class Result {
        private final String convertedFormula;
        private final String instanceVariablesString;
        private final HashMap<String, Class<?>> newVariables;

        public Result(String convertedFormula, String instanceVariablesString, HashMap<String, Class<?>> newVariables) {
            this.convertedFormula = convertedFormula;
            this.instanceVariablesString = instanceVariablesString;
            this.newVariables = newVariables;
        }

        public String getConvertedFormula() {
            return convertedFormula;
        }

        public String getInstanceVariablesString() {
            return instanceVariablesString;
        }

        public HashMap<String, Class<?>> getNewVariables() {
            return newVariables;
        }
    }

    /**
     * A type of RuntimeException thrown when operations resulting in {@link DateTime} values would exceed the range
     * available by max or min long nanoseconds.
     */
    public static class DateTimeOverflowException extends RuntimeException {
        private DateTimeOverflowException() {
            super("Operation failed due to overflow");
        }

        private DateTimeOverflowException(String s) {
            super(s);
        }

        private DateTimeOverflowException(String message, Throwable cause) {
            super(message, cause);
        }
    }

    //TODO: no equivalent
    /**
     * Create a DateTimeFormatter formatter with the specified time zone name using the standard yyyy-MM-dd format.
     *
     * @param timeZoneName the time zone name
     * @return a formatter set for the specified time zone
     */
    public static DateTimeFormatter createFormatter(final String timeZoneName) {
        final ZoneId zoneId = ZoneId.of(timeZoneName);
        return DateTimeFormatter.ofPattern(DATE_COLUMN_PARTITION_FORMAT_STRING).withZone(zoneId);
    }

    //TODO: no equivalent
    /**
     * Given a DateTimeFormatter and a timestamp in millis, return the date as a String in standard column-partition
     * format of yyyy-MM-dd. A timestamp of NULL_LONG means use the system current time.
     *
     * @param dateTimeFormatter the date formatter
     * @param timestampMillis the timestamp in millis
     * @return the formatted date
     */
    public static String getPartitionFromTimestampMillis(@NotNull final DateTimeFormatter dateTimeFormatter,
            final long timestampMillis) {
        if (timestampMillis == NULL_LONG) {
            return dateTimeFormatter.format(Instant.ofEpochMilli(System.currentTimeMillis()));
        }
        return dateTimeFormatter.format(Instant.ofEpochMilli(timestampMillis));
    }

    //TODO: no equivalent
    /**
     * Given a DateTimeFormatter and a timestamp in micros from epoch, return the date as a String in standard
     * column-partition format of yyyy-MM-dd. A timestamp of NULL_LONG means use the system current time.
     *
     * @param dateTimeFormatter the date formatter
     * @param timestampMicros the timestamp in micros
     * @return the formatted date
     */
    public static String getPartitionFromTimestampMicros(@NotNull final DateTimeFormatter dateTimeFormatter,
            final long timestampMicros) {
        if (timestampMicros == NULL_LONG) {
            return dateTimeFormatter.format(Instant.ofEpochMilli(System.currentTimeMillis()));
        }
        return dateTimeFormatter.format(Instant.ofEpochMilli(timestampMicros / 1_000));
    }

    //TODO: no equivalent
    /**
     * Given a DateTimeFormatter and a timestamp in nanos from epoch, return the date as a String in standard
     * column-partition format of yyyy-MM-dd. A timestamp of NULL_LONG means use the system current time.
     *
     * @param dateTimeFormatter the date formatter
     * @param timestampNanos the timestamp in nanos
     * @return the formatted date
     */
    public static String getPartitionFromTimestampNanos(@NotNull final DateTimeFormatter dateTimeFormatter,
            final long timestampNanos) {
        if (timestampNanos == NULL_LONG) {
            return dateTimeFormatter.format(Instant.ofEpochMilli(System.currentTimeMillis()));
        }
        return dateTimeFormatter.format(Instant.ofEpochMilli(timestampNanos / 1_000_000));
    }

    //TODO: no equivalent
    /**
     * Given a DateTimeFormatter and a timestamp in seconds from epoch, return the date as a String in standard
     * column-partition format of yyyy-MM-dd. A timestamp of NULL_LONG means use the system current time.
     *
     * @param dateTimeFormatter the date formatter
     * @param timestampSeconds the timestamp in seconds
     * @return the formatted date
     */
    public static String getPartitionFromTimestampSeconds(@NotNull final DateTimeFormatter dateTimeFormatter,
            final long timestampSeconds) {
        if (timestampSeconds == NULL_LONG) {
            return dateTimeFormatter.format(Instant.ofEpochMilli(System.currentTimeMillis()));
        }
        return dateTimeFormatter.format(Instant.ofEpochMilli(timestampSeconds * 1_000));
    }
}
