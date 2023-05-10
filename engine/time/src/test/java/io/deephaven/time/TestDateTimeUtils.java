/**
 * Copyright (c) 2016-2022 Deephaven Data Labs and Patent Pending
 */
package io.deephaven.time;

import io.deephaven.base.CompareUtils;
import io.deephaven.base.clock.TimeZones;
import io.deephaven.base.testing.BaseArrayTestCase;
import io.deephaven.util.DateUtil;
import io.deephaven.util.QueryConstants;
import junit.framework.TestCase;
import org.joda.time.DateTimeZone;
import org.joda.time.LocalTime;

import java.time.Instant;
import java.time.LocalDate;
import java.time.ZonedDateTime;

public class TestDateTimeUtils extends BaseArrayTestCase {

    public void testMillis() throws Exception {
        org.joda.time.DateTime jodaDateTime = new org.joda.time.DateTime("2010-01-01T12:13:14.999");

        DateTime dateTime = new DateTime(jodaDateTime.getMillis() * 1000000 + 123456);

        TestCase.assertEquals(jodaDateTime.getMillis(), DateTimeUtils.epochMillis(dateTime));

        TestCase.assertEquals(io.deephaven.util.QueryConstants.NULL_LONG, DateTimeUtils.epochMillis(null));
    }

    public void testNanos() throws Exception {
        org.joda.time.DateTime jodaDateTime = new org.joda.time.DateTime("2010-01-01T12:13:14.999");

        DateTime dateTime = new DateTime(jodaDateTime.getMillis() * 1000000 + 123456);

        TestCase.assertEquals(jodaDateTime.getMillis() * 1000000 + 123456, DateTimeUtils.epochNanos(dateTime));

        TestCase.assertEquals(io.deephaven.util.QueryConstants.NULL_LONG, DateTimeUtils.epochNanos((DateTime) null));
    }

    public void testMidnightConversion() throws Exception {
        org.joda.time.DateTime jodaDateTime = new org.joda.time.DateTime("2010-01-01T12:13:14.999");
        org.joda.time.DateTime jodaMidnight = new org.joda.time.DateTime("2010-01-01T00:00:00.000-05");

        DateTime dateTime = new DateTime(jodaDateTime.getMillis() * 1000000 + 123456);
        DateTime midnight = DateTimeUtils.dateTimeAtMidnight(dateTime, TimeZone.TZ_NY);

        TestCase.assertEquals(jodaMidnight.getMillis(), DateTimeUtils.epochMillis(midnight));
    }

    public void testIsBefore() throws Exception {
        org.joda.time.DateTime jodaDateTime1 = new org.joda.time.DateTime("2010-01-01T12:13:14.999");
        org.joda.time.DateTime jodaDateTime2 = new org.joda.time.DateTime("2010-01-01T12:13:14.999");

        DateTime dateTime1 = new DateTime(jodaDateTime1.getMillis() * 1000000 + 123456);
        DateTime dateTime2 = new DateTime(jodaDateTime2.getMillis() * 1000000 + 123457);

        TestCase.assertTrue(DateTimeUtils.isBefore(dateTime1, dateTime2));
        TestCase.assertFalse(DateTimeUtils.isBefore(dateTime2, dateTime1));
        TestCase.assertFalse(DateTimeUtils.isBefore(null, dateTime2));
        TestCase.assertFalse(DateTimeUtils.isBefore(null, null));
        TestCase.assertFalse(DateTimeUtils.isBefore(dateTime1, null));
    }

    public void testIsAfter() throws Exception {
        org.joda.time.DateTime jodaDateTime1 = new org.joda.time.DateTime("2010-01-01T12:13:14.999");
        org.joda.time.DateTime jodaDateTime2 = new org.joda.time.DateTime("2010-01-01T12:13:14.999");

        DateTime dateTime1 = new DateTime(jodaDateTime1.getMillis() * 1000000 + 123456);
        DateTime dateTime2 = new DateTime(jodaDateTime2.getMillis() * 1000000 + 123457);

        TestCase.assertFalse(DateTimeUtils.isAfter(dateTime1, dateTime2));
        TestCase.assertTrue(DateTimeUtils.isAfter(dateTime2, dateTime1));
        TestCase.assertFalse(DateTimeUtils.isAfter(null, dateTime2));
        TestCase.assertFalse(DateTimeUtils.isAfter(null, null));
        TestCase.assertFalse(DateTimeUtils.isAfter(dateTime1, null));
    }

    public void testPlus() throws Exception {
        org.joda.time.DateTime jodaDateTime = new org.joda.time.DateTime("2010-01-01T12:13:14.999");

        DateTime dateTime = new DateTime(jodaDateTime.getMillis() * 1000000 + 123456);

        Period period = new Period("T1h");

        TestCase.assertEquals(dateTime.getNanos() + 3600000000000L, DateTimeUtils.plus(dateTime, period).getNanos());

        period = new Period("-T1h");

        TestCase.assertEquals(dateTime.getNanos() - 3600000000000L, DateTimeUtils.plus(dateTime, period).getNanos());


        // overflow plus
        DateTimeUtils.plus(new DateTime(Long.MAX_VALUE - 10), 10); // edge at max
        try {
            DateTimeUtils.plus(new DateTime(Long.MAX_VALUE), 1);
            TestCase.fail("This should have overflowed");
        } catch (DateTimeUtils.DateTimeOverflowException e) {
            // ok
        }

        DateTimeUtils.plus(new DateTime(Long.MIN_VALUE + 10), -10); // edge at min
        try {
            DateTimeUtils.plus(new DateTime(Long.MIN_VALUE), -1);
            TestCase.fail("This should have overflowed");
        } catch (DateTimeUtils.DateTimeOverflowException e) {
            // ok
        }
    }

    public void testMinus() throws Exception {
        org.joda.time.DateTime jodaDateTime1 = new org.joda.time.DateTime("2010-01-01T12:13:14.999");
        org.joda.time.DateTime jodaDateTime2 = new org.joda.time.DateTime("2010-01-01T13:13:14.999");

        DateTime dateTime1 = new DateTime(jodaDateTime1.getMillis() * 1000000 + 123456);
        DateTime dateTime2 = new DateTime(jodaDateTime2.getMillis() * 1000000 + 123456);

        TestCase.assertEquals(-3600000000000L, DateTimeUtils.minus(dateTime1, dateTime2));
        TestCase.assertEquals(3600000000000L, DateTimeUtils.minus(dateTime2, dateTime1));

        Period period = new Period("T1h");

        TestCase.assertEquals(dateTime1.getNanos() - 3600000000000L, DateTimeUtils.minus(dateTime1, period).getNanos());

        period = new Period("-T1h");

        TestCase.assertEquals(dateTime1.getNanos() + 3600000000000L, DateTimeUtils.minus(dateTime1, period).getNanos());



        // overflow minus
        DateTimeUtils.minus(new DateTime(Long.MAX_VALUE - 10), -10); // edge at max
        try {
            DateTimeUtils.minus(new DateTime(Long.MAX_VALUE), -1);
            TestCase.fail("This should have overflowed");
        } catch (DateTimeUtils.DateTimeOverflowException e) {
            // ok
        }

        DateTimeUtils.minus(new DateTime(Long.MIN_VALUE + 10), 10); // edge at min
        try {
            DateTimeUtils.minus(new DateTime(Long.MIN_VALUE), 1);
            TestCase.fail("This should have overflowed");
        } catch (DateTimeUtils.DateTimeOverflowException e) {
            // ok
        }
    }

    public void testDiff() throws Exception {
        org.joda.time.DateTime jodaDateTime1 = new org.joda.time.DateTime("2010-01-01T12:13:14.999");
        org.joda.time.DateTime jodaDateTime2 = new org.joda.time.DateTime("2010-01-01T13:13:14.999");

        DateTime dateTime1 = new DateTime(jodaDateTime1.getMillis() * 1000000 + 123456);
        DateTime dateTime2 = new DateTime(jodaDateTime2.getMillis() * 1000000 + 123456);

        TestCase.assertEquals(3600000000000L, DateTimeUtils.diffNanos(dateTime1, dateTime2));
        TestCase.assertEquals(-3600000000000L, DateTimeUtils.diffNanos(dateTime2, dateTime1));

        TestCase.assertEquals(3600000000000L, DateTimeUtils.diffNanos(dateTime1, dateTime2));
        TestCase.assertEquals(-3600000000000L, DateTimeUtils.diffNanos(dateTime2, dateTime1));
    }

    public void testYearDiff() throws Exception {
        org.joda.time.DateTime jt1 = new org.joda.time.DateTime("2010-01-01T12:13:14.999");
        org.joda.time.DateTime jt2 = new org.joda.time.DateTime("2011-01-01T13:13:14.999");
        org.joda.time.DateTime jt3 = new org.joda.time.DateTime("2010-06-30T13:13:14.999");

        DateTime t1 = new DateTime(jt1.getMillis() * 1000000 + 123456);
        DateTime t2 = new DateTime(jt2.getMillis() * 1000000 + 123456);
        DateTime t3 = new DateTime(jt3.getMillis() * 1000000 + 123456);


        TestCase.assertEquals(1.0, DateTimeUtils.diffYears(t1, t2), 0.01);
        TestCase.assertEquals(0.5, DateTimeUtils.diffYears(t1, t3), 0.01);
        TestCase.assertEquals(io.deephaven.util.QueryConstants.NULL_DOUBLE, DateTimeUtils.diffYears(null, t1));
        TestCase.assertEquals(io.deephaven.util.QueryConstants.NULL_DOUBLE, DateTimeUtils.diffYears(t1, null));

        TestCase.assertEquals(1.0, DateTimeUtils.diffYears(t1, t2), 0.01);
        TestCase.assertEquals(0.5, DateTimeUtils.diffYears(t1, t3), 0.01);
        TestCase.assertEquals(io.deephaven.util.QueryConstants.NULL_DOUBLE, DateTimeUtils.diffYears(null, t1));
        TestCase.assertEquals(io.deephaven.util.QueryConstants.NULL_DOUBLE, DateTimeUtils.diffYears(t1, null));
    }

    public void testMillisToNanos() throws Exception {
        TestCase.assertEquals(1000000, DateTimeUtils.millisToNanos(1));

        // The next two tests will fail if DateTimeUtils.ENABLE_MICROTIME_HACK is true
        try {
            DateTimeUtils.millisToNanos(Long.MAX_VALUE / 1_000_000 + 1);
            TestCase.fail("Should have thrown a DateTimeUtils.DateTimeOverflowException");
        } catch (DateTimeUtils.DateTimeOverflowException ignored) {
            /* Exception is expected. */
        }

        try {
            DateTimeUtils.millisToNanos(-Long.MAX_VALUE / 1_000_000 - 1);
            TestCase.fail("Should have thrown a DateTimeUtils.DateTimeOverflowException");
        } catch (DateTimeUtils.DateTimeOverflowException ignored) {
            /* Exception is expected. */
        }
    }

    /*
     * public void testMillisToNanosWithHack() throws Exception { // For this to pass, ENABLE_MICROTIME_HACK in
     * DateTimeUtils must be true (i.e. you have // to run the tests with -DDateTimeUtil.enableMicrotimeHack=true)
     * assertEquals(1_000_000, DateTimeUtils.millisToNanos(1)); assertEquals(1_000_000_000,
     * DateTimeUtils.millisToNanos(1_000)); assertEquals(1531315655_000_000_000L,
     * DateTimeUtils.millisToNanos(1531315655_000L)); assertEquals(1531315655_000_000_000L,
     * DateTimeUtils.millisToNanos(1531315655_000_000L)); }
     */

    public void testNanosToMillis() throws Exception {
        TestCase.assertEquals(1, DateTimeUtils.nanosToMillis(1000000));
    }

    public void testMicroToNanos() throws Exception {
        TestCase.assertEquals(1000, DateTimeUtils.microsToNanos(1));

        try {
            DateTimeUtils.microsToNanos(Long.MAX_VALUE / 1_000 + 1);
            TestCase.fail("Should have thrown a DateTimeUtils.DateTimeOverflowException");
        } catch (DateTimeUtils.DateTimeOverflowException ignored) {
            /* Exception is expected. */
        }

        try {
            DateTimeUtils.microsToNanos(-Long.MAX_VALUE / 1_000 - 1);
            TestCase.fail("Should have thrown a DateTimeUtils.DateTimeOverflowException");
        } catch (DateTimeUtils.DateTimeOverflowException ignored) {
            /* Exception is expected. */
        }
    }

    public void testNanosToMicros() throws Exception {
        TestCase.assertEquals(1, DateTimeUtils.nanosToMicros(1000));
    }

    public void testConvertDateQuiet() throws Exception {
        // ISO formats
        TestCase.assertEquals(LocalDate.of(2018, 1, 1), DateTimeUtils.parseDateQuiet("2018-01-01"));
        TestCase.assertEquals(LocalDate.of(2018, 12, 31), DateTimeUtils.parseDateQuiet("2018-12-31"));
        TestCase.assertEquals(LocalDate.of(2018, 1, 1), DateTimeUtils.parseDateQuiet("20180101"));
        TestCase.assertEquals(LocalDate.of(2018, 12, 31), DateTimeUtils.parseDateQuiet("20181231"));

        // extremities of the format (LocalDate can store a much larger range than this but we aren't that interested)
        TestCase.assertEquals(LocalDate.of(0, 1, 1), DateTimeUtils.parseDateQuiet("0000-01-01"));
        TestCase.assertEquals(LocalDate.of(9999, 12, 31), DateTimeUtils.parseDateQuiet("9999-12-31"));

        // other variants
        TestCase.assertEquals(LocalDate.of(2018, 1, 1),
                DateTimeUtils.parseDateQuiet("01/01/2018", DateTimeUtils.DateStyle.MDY));
        TestCase.assertEquals(LocalDate.of(2018, 12, 31),
                DateTimeUtils.parseDateQuiet("12/31/2018", DateTimeUtils.DateStyle.MDY));
        TestCase.assertEquals(LocalDate.of(2018, 12, 31),
                DateTimeUtils.parseDateQuiet("12/31/18", DateTimeUtils.DateStyle.MDY));
        TestCase.assertEquals(LocalDate.of(2024, 6, 25),
                DateTimeUtils.parseDateQuiet("6/25/24", DateTimeUtils.DateStyle.MDY));
        TestCase.assertEquals(LocalDate.of(2024, 6, 2),
                DateTimeUtils.parseDateQuiet("6/2/24", DateTimeUtils.DateStyle.MDY));
        TestCase.assertEquals(LocalDate.of(2024, 6, 2),
                DateTimeUtils.parseDateQuiet("6/2/2024", DateTimeUtils.DateStyle.MDY));

        TestCase.assertEquals(LocalDate.of(2018, 1, 1),
                DateTimeUtils.parseDateQuiet("01/01/2018", DateTimeUtils.DateStyle.DMY));
        TestCase.assertEquals(LocalDate.of(2018, 12, 31),
                DateTimeUtils.parseDateQuiet("31/12/2018", DateTimeUtils.DateStyle.DMY));
        TestCase.assertEquals(LocalDate.of(2018, 12, 31),
                DateTimeUtils.parseDateQuiet("31/12/18", DateTimeUtils.DateStyle.DMY));
        TestCase.assertEquals(LocalDate.of(2024, 6, 25),
                DateTimeUtils.parseDateQuiet("25/6/24", DateTimeUtils.DateStyle.DMY));
        TestCase.assertEquals(LocalDate.of(2024, 6, 2),
                DateTimeUtils.parseDateQuiet("2/6/24", DateTimeUtils.DateStyle.DMY));
        TestCase.assertEquals(LocalDate.of(2024, 6, 2),
                DateTimeUtils.parseDateQuiet("2/6/2024", DateTimeUtils.DateStyle.DMY));


        TestCase.assertEquals(LocalDate.of(2018, 1, 1),
                DateTimeUtils.parseDateQuiet("2018/01/01", DateTimeUtils.DateStyle.YMD));
        TestCase.assertEquals(LocalDate.of(2018, 12, 31),
                DateTimeUtils.parseDateQuiet("2018/12/31", DateTimeUtils.DateStyle.YMD));
        TestCase.assertEquals(LocalDate.of(2018, 12, 31),
                DateTimeUtils.parseDateQuiet("18/12/31", DateTimeUtils.DateStyle.YMD));
        TestCase.assertEquals(LocalDate.of(2024, 6, 25),
                DateTimeUtils.parseDateQuiet("24/6/25", DateTimeUtils.DateStyle.YMD));
        TestCase.assertEquals(LocalDate.of(2024, 6, 2),
                DateTimeUtils.parseDateQuiet("24/6/2", DateTimeUtils.DateStyle.YMD));
        TestCase.assertEquals(LocalDate.of(2024, 6, 2),
                DateTimeUtils.parseDateQuiet("2024/6/2", DateTimeUtils.DateStyle.YMD));
    }

    public void testConvertLocalTimeQuiet() throws Exception {

        TestCase.assertEquals(java.time.LocalTime.of(12, 59, 59), DateTimeUtils.parseLocalTimeQuiet("L12:59:59"));
        TestCase.assertEquals(java.time.LocalTime.of(0, 0, 0), DateTimeUtils.parseLocalTimeQuiet("L00:00:00"));
        TestCase.assertEquals(java.time.LocalTime.of(23, 59, 59), DateTimeUtils.parseLocalTimeQuiet("L23:59:59"));

        TestCase.assertEquals(java.time.LocalTime.of(12, 59, 59), DateTimeUtils.parseLocalTimeQuiet("L125959"));
        TestCase.assertEquals(java.time.LocalTime.of(0, 0, 0), DateTimeUtils.parseLocalTimeQuiet("L000000"));
        TestCase.assertEquals(java.time.LocalTime.of(23, 59, 59), DateTimeUtils.parseLocalTimeQuiet("L235959"));

        TestCase.assertEquals(java.time.LocalTime.of(12, 0, 0), DateTimeUtils.parseLocalTimeQuiet("L12"));
        TestCase.assertEquals(java.time.LocalTime.of(12, 59, 0), DateTimeUtils.parseLocalTimeQuiet("L12:59"));
        TestCase.assertEquals(java.time.LocalTime.of(12, 59, 59, 123_000_000),
                DateTimeUtils.parseLocalTimeQuiet("L12:59:59.123"));
        TestCase.assertEquals(java.time.LocalTime.of(12, 59, 59, 123_456_000),
                DateTimeUtils.parseLocalTimeQuiet("L12:59:59.123456"));
        TestCase.assertEquals(java.time.LocalTime.of(12, 59, 59, 123_456_789),
                DateTimeUtils.parseLocalTimeQuiet("L12:59:59.123456789"));

        TestCase.assertEquals(java.time.LocalTime.of(12, 0, 0), DateTimeUtils.parseLocalTimeQuiet("L12"));
        TestCase.assertEquals(java.time.LocalTime.of(12, 59, 0), DateTimeUtils.parseLocalTimeQuiet("L1259"));
        TestCase.assertEquals(java.time.LocalTime.of(12, 59, 59, 123_000_000),
                DateTimeUtils.parseLocalTimeQuiet("L125959.123"));
        TestCase.assertEquals(java.time.LocalTime.of(12, 59, 59, 123_456_000),
                DateTimeUtils.parseLocalTimeQuiet("L125959.123456"));
        TestCase.assertEquals(java.time.LocalTime.of(12, 59, 59, 123_456_789),
                DateTimeUtils.parseLocalTimeQuiet("L125959.123456789"));
    }

    public void testConvertDate() throws Exception {
        DateTimeUtils.parseDate("2010-01-01"); // shouldn't have an exception

        try {
            DateTimeUtils.parseDate("2010-01-01 NY");
            TestCase.fail("Should have thrown an exception");
        } catch (Exception e) {
        }

        TestCase.assertEquals("DateTimeUtils.convertDate(\"9999-12-31\")",
                LocalDate.of(9999, 12, 31),
                DateTimeUtils.parseDate("9999-12-31"));
    }

    public void testParseDateTimeQuiet() throws Exception {
        TestCase.assertEquals(
                new DateTime(
                        new org.joda.time.DateTime("2010-01-01", DateTimeZone.forID("America/New_York")).getMillis()
                                * 1000000),
                DateTimeUtils.parseDateTimeQuiet("2010-01-01 NY"));
        TestCase.assertEquals(new DateTime(
                new org.joda.time.DateTime("2010-01-01T12:00:00", DateTimeZone.forID("America/New_York")).getMillis()
                        * 1000000),
                DateTimeUtils.parseDateTimeQuiet("2010-01-01T12:00:00 NY"));
        TestCase.assertEquals(new DateTime(
                new org.joda.time.DateTime("2010-01-01T12:00:00.1", DateTimeZone.forID("America/New_York")).getMillis()
                        * 1000000),
                DateTimeUtils.parseDateTimeQuiet("2010-01-01T12:00:00.1 NY"));
        TestCase.assertEquals(new DateTime(
                new org.joda.time.DateTime("2010-01-01T12:00:00.123", DateTimeZone.forID("America/New_York"))
                        .getMillis() * 1000000),
                DateTimeUtils.parseDateTimeQuiet("2010-01-01T12:00:00.123 NY"));
        TestCase.assertEquals(new DateTime(
                new org.joda.time.DateTime("2010-01-01T12:00:00.123", DateTimeZone.forID("America/New_York"))
                        .getMillis() * 1000000
                        + 400000),
                DateTimeUtils.parseDateTimeQuiet("2010-01-01T12:00:00.1234 NY"));
        TestCase.assertEquals(
                new DateTime(
                        new org.joda.time.DateTime("2010-01-01T12:00:00.123", DateTimeZone.forID("America/New_York"))
                                .getMillis()
                                * 1000000 + 456789),
                DateTimeUtils.parseDateTimeQuiet("2010-01-01T12:00:00.123456789 NY"));

        TestCase.assertEquals(
                new DateTime(new org.joda.time.DateTime("2010-01-01", DateTimeZone.forID("America/Chicago")).getMillis()
                        * 1000000),
                DateTimeUtils.parseDateTimeQuiet("2010-01-01 MN"));
        TestCase.assertEquals(new DateTime(
                new org.joda.time.DateTime("2010-01-01T12:00:00", DateTimeZone.forID("America/Chicago")).getMillis()
                        * 1000000),
                DateTimeUtils.parseDateTimeQuiet("2010-01-01T12:00:00 MN"));
        TestCase.assertEquals(new DateTime(
                new org.joda.time.DateTime("2010-01-01T12:00:00.1", DateTimeZone.forID("America/Chicago")).getMillis()
                        * 1000000),
                DateTimeUtils.parseDateTimeQuiet("2010-01-01T12:00:00.1 MN"));
        TestCase.assertEquals(new DateTime(
                new org.joda.time.DateTime("2010-01-01T12:00:00.123", DateTimeZone.forID("America/Chicago")).getMillis()
                        * 1000000),
                DateTimeUtils.parseDateTimeQuiet("2010-01-01T12:00:00.123 MN"));
        TestCase.assertEquals(new DateTime(
                new org.joda.time.DateTime("2010-01-01T12:00:00.123", DateTimeZone.forID("America/Chicago")).getMillis()
                        * 1000000
                        + 400000),
                DateTimeUtils.parseDateTimeQuiet("2010-01-01T12:00:00.1234 MN"));
        TestCase.assertEquals(
                new DateTime(
                        new org.joda.time.DateTime("2010-01-01T12:00:00.123", DateTimeZone.forID("America/Chicago"))
                                .getMillis()
                                * 1000000 + 456789),
                DateTimeUtils.parseDateTimeQuiet("2010-01-01T12:00:00.123456789 MN"));

        TestCase.assertEquals(new DateTime(1503343549064106107L),
                DateTimeUtils.parseDateTimeQuiet("2017-08-21T15:25:49.064106107 NY"));

        // assertEquals(new DateTime(new DateTime("2010-01-01T12:00:00.123", DateTimeZone.UTC).getMillis()*1000000),
        // DateTimeUtils.convertDateTimeQuiet("2010-01-01T12:00:00.123+0000"));
        // assertEquals(new DateTime(new DateTime("2010-01-01T12:00:00.123",
        // DateTimeZone.forID("America/New_York")).getMillis()*1000000),
        // DateTimeUtils.convertDateTimeQuiet("2010-01-01T12:00:00.123-0400"));
        // assertEquals(new DateTime(new DateTime("2010-01-01T12:00:00.123",
        // DateTimeZone.forID("Asia/Seoul")).getMillis()*1000000),
        // DateTimeUtils.convertDateTimeQuiet("2010-01-01T12:00:00.123+0900"));
    }

    public void testParseDateTime() throws Exception {
        DateTimeUtils.parseDateTime("2010-01-01 NY"); // shouldn't have an exception

        try {
            DateTimeUtils.parseDateTime("2010-01-01");
            TestCase.fail("Should have thrown an exception");
        } catch (Exception e) {
        }

        TestCase.assertEquals("DateTimeUtils.convertDateTime(\"2262-04-11T19:47:16.854775807 NY\").getNanos()",
                Long.MAX_VALUE,
                DateTimeUtils.parseDateTime("2262-04-11T19:47:16.854775807 NY").getNanos());
    }

    public void testParseNanosQuiet() throws Exception {
        TestCase.assertEquals(new LocalTime("12:00").getMillisOfDay() * 1000000L,
                DateTimeUtils.parseNanosQuiet("12:00"));
        TestCase.assertEquals(new LocalTime("12:00:00").getMillisOfDay() * 1000000L,
                DateTimeUtils.parseNanosQuiet("12:00:00"));
        TestCase.assertEquals(new LocalTime("12:00:00.123").getMillisOfDay() * 1000000L,
                DateTimeUtils.parseNanosQuiet("12:00:00.123"));
        TestCase.assertEquals(new LocalTime("12:00:00.123").getMillisOfDay() * 1000000L + 400000,
                DateTimeUtils.parseNanosQuiet("12:00:00.1234"));
        TestCase.assertEquals(new LocalTime("12:00:00.123").getMillisOfDay() * 1000000L + 456789,
                DateTimeUtils.parseNanosQuiet("12:00:00.123456789"));

        TestCase.assertEquals(new LocalTime("2:00").getMillisOfDay() * 1000000L,
                DateTimeUtils.parseNanosQuiet("2:00"));
        TestCase.assertEquals(new LocalTime("2:00:00").getMillisOfDay() * 1000000L,
                DateTimeUtils.parseNanosQuiet("2:00:00"));
        TestCase.assertEquals(new LocalTime("2:00:00.123").getMillisOfDay() * 1000000L,
                DateTimeUtils.parseNanosQuiet("2:00:00.123"));
        TestCase.assertEquals(new LocalTime("2:00:00.123").getMillisOfDay() * 1000000L + 400000,
                DateTimeUtils.parseNanosQuiet("2:00:00.1234"));
        TestCase.assertEquals(new LocalTime("2:00:00.123").getMillisOfDay() * 1000000L + 456789,
                DateTimeUtils.parseNanosQuiet("2:00:00.123456789"));

        TestCase.assertEquals(
                new LocalTime("2:00").getMillisOfDay() * 1000000L + 3L * 1000000 * DateUtil.MILLIS_PER_DAY,
                DateTimeUtils.parseNanosQuiet("3T2:00"));
        TestCase.assertEquals(
                new LocalTime("2:00:00").getMillisOfDay() * 1000000L + 3L * 1000000 * DateUtil.MILLIS_PER_DAY,
                DateTimeUtils.parseNanosQuiet("3T2:00:00"));
        TestCase.assertEquals(
                new LocalTime("2:00:00.123").getMillisOfDay() * 1000000L + 3L * 1000000 * DateUtil.MILLIS_PER_DAY,
                DateTimeUtils.parseNanosQuiet("3T2:00:00.123"));
        TestCase.assertEquals(new LocalTime("2:00:00.123").getMillisOfDay() * 1000000L + 400000
                + 3L * 1000000 * DateUtil.MILLIS_PER_DAY, DateTimeUtils.parseNanosQuiet("3T2:00:00.1234"));
        TestCase.assertEquals(new LocalTime("2:00:00.123").getMillisOfDay() * 1000000L + 456789
                + 3L * 1000000 * DateUtil.MILLIS_PER_DAY, DateTimeUtils.parseNanosQuiet("3T2:00:00.123456789"));

        TestCase.assertEquals(55549064106107L, DateTimeUtils.parseNanosQuiet("15:25:49.064106107"));
    }

    public void testParseNanos() throws Exception {
        DateTimeUtils.parseNanos("12:00"); // shouldn't have an exception

        try {
            DateTimeUtils.parseNanos("12");
            TestCase.fail("Should have thrown an exception");
        } catch (Exception e) {
        }
    }

    public void testParsePeriodQuiet() throws Exception {
        TestCase.assertEquals(java.time.Duration.parse("PT1s"),
                DateTimeUtils.parsePeriodQuiet("T1S").getDuration());
        TestCase.assertEquals(java.time.Duration.parse("P1wT1m"),
                DateTimeUtils.parsePeriodQuiet("1WT1M").getDuration());
        TestCase.assertEquals(java.time.Duration.parse("P1w"), DateTimeUtils.parsePeriodQuiet("1W").getDuration());

        TestCase.assertEquals(null, DateTimeUtils.parsePeriodQuiet("-"));
    }

    public void testParsePeriod() throws Exception {
        DateTimeUtils.parsePeriod("T1S"); // shouldn't have an exception

        try {
            DateTimeUtils.parsePeriod("1S");
            TestCase.fail("Should have thrown an exception");
        } catch (Exception e) {
        }
    }

    public void testTimeFormat() throws Exception {
        TestCase.assertEquals("12:00:00", DateTimeUtils.formatNanos(DateTimeUtils.parseNanosQuiet("12:00")));
        TestCase.assertEquals("12:00:00", DateTimeUtils.formatNanos(DateTimeUtils.parseNanosQuiet("12:00:00")));
        TestCase.assertEquals("12:00:00.123000000",
                DateTimeUtils.formatNanos(DateTimeUtils.parseNanosQuiet("12:00:00.123")));
        TestCase.assertEquals("12:00:00.123400000",
                DateTimeUtils.formatNanos(DateTimeUtils.parseNanosQuiet("12:00:00.1234")));
        TestCase.assertEquals("12:00:00.123456789",
                DateTimeUtils.formatNanos(DateTimeUtils.parseNanosQuiet("12:00:00.123456789")));

        TestCase.assertEquals("2:00:00", DateTimeUtils.formatNanos(DateTimeUtils.parseNanosQuiet("2:00")));
        TestCase.assertEquals("2:00:00", DateTimeUtils.formatNanos(DateTimeUtils.parseNanosQuiet("2:00:00")));
        TestCase.assertEquals("2:00:00.123000000", DateTimeUtils.formatNanos(DateTimeUtils.parseNanosQuiet("2:00:00.123")));
        TestCase.assertEquals("2:00:00.123400000",
                DateTimeUtils.formatNanos(DateTimeUtils.parseNanosQuiet("2:00:00.1234")));
        TestCase.assertEquals("2:00:00.123456789",
                DateTimeUtils.formatNanos(DateTimeUtils.parseNanosQuiet("2:00:00.123456789")));

        TestCase.assertEquals("3T2:00:00", DateTimeUtils.formatNanos(DateTimeUtils.parseNanosQuiet("3T2:00")));
        TestCase.assertEquals("3T2:00:00", DateTimeUtils.formatNanos(DateTimeUtils.parseNanosQuiet("3T2:00:00")));
        TestCase.assertEquals("3T2:00:00.123000000",
                DateTimeUtils.formatNanos(DateTimeUtils.parseNanosQuiet("3T2:00:00.123")));
        TestCase.assertEquals("3T2:00:00.123400000",
                DateTimeUtils.formatNanos(DateTimeUtils.parseNanosQuiet("3T2:00:00.1234")));
        TestCase.assertEquals("3T2:00:00.123456789",
                DateTimeUtils.formatNanos(DateTimeUtils.parseNanosQuiet("3T2:00:00.123456789")));
    }

    public void testFormatDate() throws Exception {
        TestCase.assertEquals("2010-01-01",
                DateTimeUtils.formatDate(DateTimeUtils.parseDateTimeQuiet("2010-01-01 NY"), TimeZone.TZ_NY));
    }

    public void testLowerBin() {
        final long second = 1000000000L;
        final long minute = 60 * second;
        final long hour = 60 * minute;
        DateTime time = DateTimeUtils.parseDateTime("2010-06-15T06:14:01.2345 NY");

        TestCase.assertEquals(DateTimeUtils.parseDateTime("2010-06-15T06:14:01 NY"),
                DateTimeUtils.lowerBin(time, second));
        TestCase.assertEquals(DateTimeUtils.parseDateTime("2010-06-15T06:10:00 NY"),
                DateTimeUtils.lowerBin(time, 5 * minute));
        TestCase.assertEquals(DateTimeUtils.parseDateTime("2010-06-15T06:00:00 NY"),
                DateTimeUtils.lowerBin(time, hour));
        TestCase.assertEquals(null, DateTimeUtils.lowerBin(null, 5 * minute));
        TestCase.assertEquals(null, DateTimeUtils.lowerBin(time, io.deephaven.util.QueryConstants.NULL_LONG));

        TestCase.assertEquals(DateTimeUtils.lowerBin(time, second),
                DateTimeUtils.lowerBin(DateTimeUtils.lowerBin(time, second), second));
    }

    public void testLowerBinWithOffset() {
        final long second = 1000000000L;
        final long minute = 60 * second;
        final long hour = 60 * minute;
        DateTime time = DateTimeUtils.parseDateTime("2010-06-15T06:14:01.2345 NY");

        TestCase.assertEquals(DateTimeUtils.parseDateTime("2010-06-15T06:11:00 NY"),
                DateTimeUtils.lowerBin(time, 5 * minute, minute));
        TestCase.assertEquals(null, DateTimeUtils.lowerBin(null, 5 * minute, minute));
        TestCase.assertEquals(null, DateTimeUtils.lowerBin(time, QueryConstants.NULL_LONG, minute));
        TestCase.assertEquals(null, DateTimeUtils.lowerBin(time, 5 * minute, QueryConstants.NULL_LONG));

        TestCase.assertEquals(DateTimeUtils.lowerBin(time, second, second),
                DateTimeUtils.lowerBin(DateTimeUtils.lowerBin(time, second, second), second, second));
    }

    public void testUpperBin() {
        final long second = 1000000000L;
        final long minute = 60 * second;
        final long hour = 60 * minute;
        DateTime time = DateTimeUtils.parseDateTime("2010-06-15T06:14:01.2345 NY");

        TestCase.assertEquals(DateTimeUtils.parseDateTime("2010-06-15T06:14:02 NY"),
                DateTimeUtils.upperBin(time, second));
        TestCase.assertEquals(DateTimeUtils.parseDateTime("2010-06-15T06:15:00 NY"),
                DateTimeUtils.upperBin(time, 5 * minute));
        TestCase.assertEquals(DateTimeUtils.parseDateTime("2010-06-15T07:00:00 NY"),
                DateTimeUtils.upperBin(time, hour));
        TestCase.assertEquals(null, DateTimeUtils.upperBin(null, 5 * minute));
        TestCase.assertEquals(null, DateTimeUtils.upperBin(time, io.deephaven.util.QueryConstants.NULL_LONG));

        TestCase.assertEquals(DateTimeUtils.upperBin(time, second),
                DateTimeUtils.upperBin(DateTimeUtils.upperBin(time, second), second));
    }

    public void testUpperBinWithOffset() {
        final long second = 1000000000L;
        final long minute = 60 * second;
        final long hour = 60 * minute;
        DateTime time = DateTimeUtils.parseDateTime("2010-06-15T06:14:01.2345 NY");

        TestCase.assertEquals(DateTimeUtils.parseDateTime("2010-06-15T06:16:00 NY"),
                DateTimeUtils.upperBin(time, 5 * minute, minute));
        TestCase.assertEquals(null, DateTimeUtils.upperBin(null, 5 * minute, minute));
        TestCase.assertEquals(null, DateTimeUtils.upperBin(time, io.deephaven.util.QueryConstants.NULL_LONG, minute));
        TestCase.assertEquals(null, DateTimeUtils.upperBin(time, 5 * minute, QueryConstants.NULL_LONG));

        TestCase.assertEquals(DateTimeUtils.upperBin(time, second, second),
                DateTimeUtils.upperBin(DateTimeUtils.upperBin(time, second, second), second, second));
    }

    public void testDateTimeToExcel() {
        DateTime time = DateTimeUtils.parseDateTime("2010-06-15T16:00:00 NY");
        TestCase.assertTrue(CompareUtils.doubleEquals(40344.666666666664, DateTimeUtils.toExcelTime(time, TimeZone.TZ_NY)));
        TestCase.assertTrue(
                CompareUtils.doubleEquals(40344.625, DateTimeUtils.toExcelTime(time, TimeZone.TZ_CT)));
        TestCase.assertTrue(CompareUtils.doubleEquals(40344.625, DateTimeUtils.toExcelTime(time, TimeZone.TZ_MN)));
    }

    /**
     * Test autoEpcohTime with the given epoch time.
     *
     * @param epoch Epoch time (in seconds)
     * @return The year (in the New York timezone) in which the given time falls.
     */
    public int doTestAutoEpochToTime(long epoch) {
        TestCase.assertEquals(DateTimeUtils.epochAutoToDateTime(epoch).getMillis(), epoch * 1000);
        TestCase.assertEquals(DateTimeUtils.epochAutoToDateTime(epoch).getMicros(), epoch * 1000 * 1000);
        TestCase.assertEquals(DateTimeUtils.epochAutoToDateTime(epoch).getNanos(), epoch * 1000 * 1000 * 1000);

        final long milliValue = epoch * 1000 + (int) (Math.signum(epoch) * 123);
        TestCase.assertEquals(DateTimeUtils.epochAutoToDateTime(milliValue).getMillis(), milliValue);
        TestCase.assertEquals(DateTimeUtils.epochAutoToDateTime(milliValue).getMicros(), milliValue * 1000);
        TestCase.assertEquals(DateTimeUtils.epochAutoToDateTime(milliValue).getNanos(), milliValue * 1000 * 1000);

        final long microValue = milliValue * 1000 + (int) (Math.signum(milliValue) * 456);
        TestCase.assertEquals(DateTimeUtils.epochAutoToDateTime(microValue).getMillis(), milliValue);
        TestCase.assertEquals(DateTimeUtils.epochAutoToDateTime(microValue).getMicros(), microValue);
        TestCase.assertEquals(DateTimeUtils.epochAutoToDateTime(microValue).getNanos(), microValue * 1000);

        final long nanoValue = microValue * 1000 + (int) (Math.signum(microValue) * 789);
        TestCase.assertEquals(DateTimeUtils.epochAutoToDateTime(nanoValue).getMillis(), milliValue);
        TestCase.assertEquals(DateTimeUtils.epochAutoToDateTime(nanoValue).getMicros(), microValue);
        TestCase.assertEquals(DateTimeUtils.epochAutoToDateTime(nanoValue).getNanos(), nanoValue);

        return DateTimeUtils.year(DateTimeUtils.epochAutoToDateTime(nanoValue), TimeZone.TZ_NY);
    }

    public void testAutoEpochToTime() {
        long inTheYear2035 = 2057338800;
        TestCase.assertEquals("doTestAutoEpochToTime(inTheYear2035)", 2035, doTestAutoEpochToTime(inTheYear2035));
        long inTheYear1993 = 731966400;
        TestCase.assertEquals("doTestAutoEpochToTime(inTheYear1993)", 1993, doTestAutoEpochToTime(inTheYear1993));
        long inTheYear2013 = 1363114800;
        TestCase.assertEquals("doTestAutoEpochToTime(inTheYear2013)", 2013, doTestAutoEpochToTime(inTheYear2013));

        long inTheYear1904 = -2057338800;
        TestCase.assertEquals("doTestAutoEpochToTime(inTheYear1904)", 1904, doTestAutoEpochToTime(inTheYear1904));
        long inTheYear1946 = -731966400;
        TestCase.assertEquals("doTestAutoEpochToTime(inTheYear1946)", 1946, doTestAutoEpochToTime(inTheYear1946));
        long inTheYear1926 = -1363114800;
        TestCase.assertEquals("doTestAutoEpochToTime(inTheYear1926)", 1926, doTestAutoEpochToTime(inTheYear1926));
    }

    public void testMicrosOfMilli() {
        TestCase.assertEquals(0,
                DateTimeUtils.microsOfMilli(DateTimeUtils.parseDateTime("2015-07-31T20:40 NY")));
        TestCase.assertEquals(0,
                DateTimeUtils.microsOfMilli(DateTimeUtils.parseDateTime("2015-07-31T20:40:00 NY")));
        TestCase.assertEquals(0,
                DateTimeUtils.microsOfMilli(DateTimeUtils.parseDateTime("2015-07-31T20:40:00.123 NY")
                ));
        TestCase.assertEquals(400,
                DateTimeUtils.microsOfMilli(DateTimeUtils.parseDateTime("2015-07-31T20:40:00.1234 NY")
                ));
        TestCase.assertEquals(456,
                DateTimeUtils.microsOfMilli(DateTimeUtils.parseDateTime("2015-07-31T20:40:00.123456 NY")
                ));
        // this one should round up
        TestCase.assertEquals(457,
                DateTimeUtils.microsOfMilli(DateTimeUtils.parseDateTime("2015-07-31T20:40:00.1234567 NY")
                ));
        // this one should round up
        TestCase.assertEquals(457,
                DateTimeUtils.microsOfMilli(DateTimeUtils.parseDateTime("2015-07-31T20:40:00.123456789 NY")
                ));
    }

    public void testZonedDateTime() {
        final DateTime dateTime1 = DateTimeUtils.parseDateTime("2015-07-31T20:40 NY");
        final ZonedDateTime zonedDateTime1 =
                ZonedDateTime.of(2015, 7, 31, 20, 40, 0, 0, TimeZone.TZ_NY.getTimeZone().toTimeZone().toZoneId());
        TestCase.assertEquals(zonedDateTime1, DateTimeUtils.toZonedDateTime(dateTime1, TimeZone.TZ_NY));
        TestCase.assertEquals(dateTime1, DateTimeUtils.toDateTime(zonedDateTime1));

        final DateTime dateTime2 = DateTimeUtils.parseDateTime("2020-07-31T20:40 NY");
        TestCase.assertEquals(dateTime2,
                DateTimeUtils.toDateTime(DateTimeUtils.toZonedDateTime(dateTime2, TimeZone.TZ_NY)));

        final DateTime dateTime3 = DateTimeUtils.parseDateTime("2050-07-31T20:40 NY");
        TestCase.assertEquals(dateTime3,
                DateTimeUtils.toDateTime(DateTimeUtils.toZonedDateTime(dateTime3, TimeZone.TZ_NY)));
    }

    public void testISO8601() {
        final String iso8601 = "2022-04-26T00:30:31.087360Z";
        assertEquals(DateTime.of(Instant.parse(iso8601)), DateTimeUtils.parseDateTime(iso8601));
    }


    public void testISO8601_druation() {
        final long dayNanos = 1_000_000_000L * 60 * 60 * 24;

        assertEquals(7 * dayNanos, DateTimeUtils.parseNanos("1W"));
        assertEquals(-7 * dayNanos, DateTimeUtils.parseNanos("-1W"));
    }
}
