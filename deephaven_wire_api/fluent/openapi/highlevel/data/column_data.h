///*
// * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
// */
//#pragma once
//#include <cstdint>
//#include <string>
//#include <boost/optional.hpp>
//#include <boost/utility/string_view.hpp>
//#include "highlevel/data/dbdatetime.h"
//#include "highlevel/data/deephaven_constants.h"
//
//namespace deephaven {
//namespace openAPI {
//namespace highlevel {
//namespace data {
//
//class ColumnData {
//protected:
//  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnDefinition ColumnDefinition;
//  typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData LowLevelColumnData;
//public:
//  struct Internal {
//    const char *getColumnType() const { return owner_->getColumnType(); }
//    const std::shared_ptr<LowLevelColumnData> getLowLevelColumnData() const {
//      return owner_->getLowLevelColumnData();
//    }
//
//    const ColumnData *owner_;
//  };
//
//  static std::shared_ptr<ColumnData> createFromColdef(const ColumnDefinition &colDef,
//      const LowLevelColumnData &colData);
//  virtual int32_t length() const = 0;
//  virtual bool isNull(int32_t row) const = 0;
//
//  virtual bool getBoolean(int32_t row) const = 0;
//  virtual char16_t getChar(int32_t row) const = 0;
//  virtual int8_t getByte(int32_t row) const = 0;
//  virtual int16_t getInt16(int32_t row) const = 0;
//  virtual int32_t getInt32(int32_t row) const = 0;
//  virtual int64_t getInt64(int32_t row) const = 0;
//  virtual float getFloat(int32_t row) const = 0;
//  virtual double getDouble(int32_t row) const = 0;
////  decimal? GetDecimal(int32_t row) const = 0;
////  DHDecimal? GetDHDecimal(int32_t row) const = 0;
////  DHDate GetDHDate(int32_t row) const = 0;
////  DHTime GetDHTime(int32_t row) const = 0;
////  DBDateTime GetDBDateTime(int32_t row) const = 0;
////  BigInteger? GetBigInteger(int32_t row) const = 0;
//
//  virtual const std::string &getString(int32_t row) const = 0;
//  virtual void streamTo(std::ostream &s, int32_t row) const = 0;
//
//  Internal internal() const { return Internal{this}; }
//
//protected:
//  virtual const char *getColumnType() const = 0;
//  virtual std::shared_ptr<LowLevelColumnData> getLowLevelColumnData() const = 0;
//};
//
//class AbstractColumnData : public ColumnData {
//public:
//  virtual ~AbstractColumnData() = default;
//  bool getBoolean(int32_t row) const override;
//  char16_t getChar(int32_t row) const override;
//  int8_t getByte(int32_t row) const override;
//  int16_t getInt16(int32_t row) const override;
//  int32_t getInt32(int32_t row) const override;
//  int64_t getInt64(int32_t row) const override;
//  float getFloat(int32_t row) const override;
//  double getDouble(int32_t row) const override;
//  const std::string &getString(int32_t row) const override;
//};
//
//class ByteColumnData final : public AbstractColumnData {
//  struct Private {};
//
//  // typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::IntArrayColumnData IntArrayColumnData;
//public:
//  typedef int8_t dataType_t;
//  typedef int8_t underlyingType_t;
//  // typedef IntArrayColumnData columnDataType_t;
//
//  static std::shared_ptr<ByteColumnData> create(std::vector<underlyingType_t> intData);
//  static std::shared_ptr<ByteColumnData> create(std::shared_ptr<std::vector<underlyingType_t>> intData);
//
//  explicit ByteColumnData(Private, std::shared_ptr<std::vector<underlyingType_t>> data);
//  ByteColumnData(const ByteColumnData &other) = delete;
//  ByteColumnData &operator=(const ByteColumnData &other) = delete;
//  ByteColumnData(ByteColumnData &&other) noexcept;
//  ByteColumnData &operator=(ByteColumnData &&other) noexcept;
//  ~ByteColumnData() final;
//
//  dataType_t getValue(int32_t row) const {
//    return (*data_)[row];
//  }
//
//  void setValue(int32_t row, dataType_t value) {
//    (*data_)[row] = value;
//  }
//
//  int32_t length() const final {
//    return data_->size();
//  }
//
//  int8_t getByte(int32_t row) const final {
//    return getValue(row);
//  }
//
//  int16_t getInt16(int32_t row) const final {
//    return getValue(row);
//  }
//
//  int32_t getInt32(int32_t row) const final {
//    return getValue(row);
//  }
//
//  int64_t getInt64(int32_t row) const final {
//    return getValue(row);
//  }
//
//  bool isNull(int32_t row) const final {
//    return valueIsNull(getValue(row));
//  }
//
//  void streamTo(std::ostream &s, int32_t row) const final {
//    auto value = getValue(row);
//    if (valueIsNull(value)) {
//      s << "(null)";
//    } else {
//      s << static_cast<int32_t>(getValue(row));
//    }
//  }
//
//protected:
//  static bool valueIsNull(dataType_t value) {
//    return value == DeephavenConstants::NULL_BYTE;
//  }
//
//  const char *getColumnType() const final {
//    return "byte";
//  }
//
//  std::shared_ptr<LowLevelColumnData> getLowLevelColumnData() const final;
//
//private:
//  std::shared_ptr<std::vector<underlyingType_t>> data_;
//};
//
//class BooleanColumnData final : public AbstractColumnData {
//  struct Private {};
//
//  // typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::IntArrayColumnData IntArrayColumnData;
//public:
//  typedef boost::optional<bool> dataType_t;
//  typedef int8_t underlyingType_t;
//  // typedef IntArrayColumnData columnDataType_t;
//
//  static std::shared_ptr<BooleanColumnData> create(const std::vector<dataType_t> &data);
//  static std::shared_ptr<BooleanColumnData> create(std::vector<underlyingType_t> data);
//  static std::shared_ptr<BooleanColumnData> create(std::shared_ptr<std::vector<underlyingType_t>> data);
//
//  BooleanColumnData(Private, std::shared_ptr<std::vector<underlyingType_t>> data);
//  BooleanColumnData(const BooleanColumnData &other) = delete;
//  BooleanColumnData &operator=(const BooleanColumnData &other) = delete;
//  ~BooleanColumnData() final;
//
//  dataType_t getValue(int32_t row) const {
//    return sbyteToBool((*data_)[row]);
//  }
//
//  void setValue(int32_t row, dataType_t value) {
//    (*data_)[row] = boolToSbyte(value);
//  }
//
//  int32_t length() const final {
//    return data_->size();
//  }
//
//  bool getBoolean(int32_t row) const override {
//    auto temp = getValue(row);
//    return temp.has_value() && *temp;
//  }
//
//  bool isNull(int32_t row) const final {
//    return valueIsNull(getValue(row));
//  }
//
//  void streamTo(std::ostream &s, int32_t row) const final {
//    auto value = getValue(row);
//    if (valueIsNull(value)) {
//      s << "(null)";
//    } else {
//      s << (*value ? "true" : "false");
//    }
//  }
//
//  static boost::optional<bool> sbyteToBool(int8_t b)
//  {
//    if (b == 0)
//      return false;
//    if (b == 1)
//      return true;
//    return {};
//  }
//
//  static int8_t boolToSbyte(boost::optional<bool> b)
//  {
//    if (b.has_value()) {
//      return *b;
//    }
//    return -1;
//  }
//
//protected:
//  static bool valueIsNull(dataType_t value) {
//    return !value.has_value();
//  }
//
//  const char *getColumnType() const final {
//    return "java.lang.Boolean";
//  }
//
//  std::shared_ptr<LowLevelColumnData> getLowLevelColumnData() const final;
//
//private:
//  std::shared_ptr<std::vector<underlyingType_t>> data_;
//};
//
//class CharColumnData final : public AbstractColumnData {
//  struct Private {};
//  // typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::IntArrayColumnData IntArrayColumnData;
//public:
//  typedef char16_t dataType_t;
//  typedef char16_t underlyingType_t;
//
//  static std::shared_ptr<CharColumnData> create(std::vector<underlyingType_t> data);
//  static std::shared_ptr<CharColumnData> create(std::shared_ptr<std::vector<underlyingType_t>> data);
//
//  CharColumnData(Private, std::shared_ptr<std::vector<underlyingType_t>> data);
//  CharColumnData(const CharColumnData &other) = delete;
//  CharColumnData &operator=(const CharColumnData &other) = delete;
//  ~CharColumnData() final;
//
//  dataType_t getValue(int32_t row) const {
//    return (*data_)[row];
//  }
//
//  void setValue(int32_t row, dataType_t value) {
//    (*data_)[row] = value;
//  }
//
//  int32_t length() const final {
//    return data_->size();
//  }
//
//  char16_t getChar(int32_t row) const final {
//    return getValue(row);
//  }
//
//  int16_t getInt16(int32_t row) const final {
//    return getValue(row);
//  }
//
//  int32_t getInt32(int32_t row) const final {
//    return getValue(row);
//  }
//
//  int64_t getInt64(int32_t row) const final {
//    return getValue(row);
//  }
//
//  bool isNull(int32_t row) const final {
//    return valueIsNull(getValue(row));
//  }
//
//  void streamTo(std::ostream &s, int32_t row) const final {
//    auto value = getValue(row);
//    if (valueIsNull(value)) {
//      s << "(null)";
//    } else {
//      s << value;
//    }
//  }
//
//protected:
//  static bool valueIsNull(dataType_t value) {
//    return value == DeephavenConstants::NULL_CHAR;
//  }
//
//  const char *getColumnType() const final {
//    return "char";
//  }
//
//  std::shared_ptr<LowLevelColumnData> getLowLevelColumnData() const final;
//
//private:
//  std::shared_ptr<std::vector<underlyingType_t>> data_;
//};
//
//class ShortColumnData final : public AbstractColumnData {
//  struct Private {};
//  // typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::IntArrayColumnData IntArrayColumnData;
//public:
//  typedef int16_t dataType_t;
//  typedef int16_t underlyingType_t;
//  // typedef IntArrayColumnData columnDataType_t;
//
//  static std::shared_ptr<ShortColumnData> create(std::vector<underlyingType_t> data);
//  static std::shared_ptr<ShortColumnData> create(std::shared_ptr<std::vector<underlyingType_t>> data);
//
//  ShortColumnData(Private, std::shared_ptr<std::vector<underlyingType_t>> data);
//  ShortColumnData(const ShortColumnData &other) = delete;
//  ShortColumnData &operator=(const ShortColumnData &other) = delete;
//  ShortColumnData(ShortColumnData &&other) noexcept;
//  ShortColumnData &operator=(ShortColumnData &&other) noexcept;
//  ~ShortColumnData() final;
//
//  dataType_t getValue(int32_t row) const {
//    return (*data_)[row];
//  }
//
//  void setValue(int32_t row, dataType_t value) {
//    (*data_)[row] = value;
//  }
//
//  int32_t length() const final {
//    return data_->size();
//  }
//
//  int16_t getInt16(int32_t row) const final {
//    return getValue(row);
//  }
//
//  int32_t getInt32(int32_t row) const final {
//    return getValue(row);
//  }
//
//  int64_t getInt64(int32_t row) const final {
//    return getValue(row);
//  }
//
//  bool isNull(int32_t row) const final {
//    return valueIsNull(getValue(row));
//  }
//
//  void streamTo(std::ostream &s, int32_t row) const final {
//    auto value = getValue(row);
//    if (valueIsNull(value)) {
//      s << "(null)";
//    } else {
//      s << value;
//    }
//  }
//
//protected:
//  static bool valueIsNull(dataType_t value) {
//    return value == DeephavenConstants::NULL_SHORT;
//  }
//
//  const char *getColumnType() const final {
//    return "short";
//  }
//
//  std::shared_ptr<LowLevelColumnData> getLowLevelColumnData() const final;
//
//private:
//  std::shared_ptr<std::vector<underlyingType_t>> data_;
//};
//
//// put here for now until I get this right
//class IntColumnData final : public AbstractColumnData {
//  struct Private {};
//  // typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::IntArrayColumnData IntArrayColumnData;
//public:
//  typedef int32_t dataType_t;
//  typedef int32_t underlyingType_t;
//  // typedef IntArrayColumnData columnDataType_t;
//
//  static std::shared_ptr<IntColumnData> create(std::vector<underlyingType_t> intData);
//  static std::shared_ptr<IntColumnData> create(std::shared_ptr<std::vector<underlyingType_t>> intData);
//
//  IntColumnData(Private, std::shared_ptr<std::vector<underlyingType_t>> data);
//  IntColumnData(const IntColumnData &other) = delete;
//  IntColumnData &operator=(const IntColumnData &other) = delete;
//  IntColumnData(IntColumnData &&other) noexcept;
//  IntColumnData &operator=(IntColumnData &&other) noexcept;
//  ~IntColumnData() final;
//
//  dataType_t getValue(int32_t row) const {
//    return (*data_)[row];
//  }
//
//  void setValue(int32_t row, dataType_t value) {
//    (*data_)[row] = value;
//  }
//
//  int32_t length() const final {
//    return data_->size();
//  }
//
//  int32_t getInt32(int32_t row) const final {
//    return getValue(row);
//  }
//
//  int64_t getInt64(int32_t row) const final {
//    return getValue(row);
//  }
//
//  bool isNull(int32_t row) const final {
//    return valueIsNull(getValue(row));
//  }
//
//  void streamTo(std::ostream &s, int32_t row) const final {
//    auto value = getValue(row);
//    if (valueIsNull(value)) {
//      s << "(null)";
//    } else {
//      s << value;
//    }
//  }
//
//protected:
//  static bool valueIsNull(dataType_t value) {
//    return value == DeephavenConstants::NULL_INT;
//  }
//
//  const char *getColumnType() const final {
//    return "int";
//  }
//
//  std::shared_ptr<LowLevelColumnData> getLowLevelColumnData() const final;
//
//private:
//  std::shared_ptr<std::vector<underlyingType_t>> data_;
//};
//
//class LongColumnData final : public AbstractColumnData {
//  struct Private {};
//
//  // typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::IntArrayColumnData IntArrayColumnData;
//public:
//  typedef int64_t dataType_t;
//  typedef int64_t underlyingType_t;
//  // typedef IntArrayColumnData columnDataType_t;
//
//  static std::shared_ptr<LongColumnData> create(std::vector<underlyingType_t> data);
//  static std::shared_ptr<LongColumnData> create(std::shared_ptr<std::vector<underlyingType_t>> data);
//
//  LongColumnData(Private, std::shared_ptr<std::vector<underlyingType_t>> data);
//  LongColumnData(const LongColumnData &other) = delete;
//  LongColumnData &operator=(const LongColumnData &other) = delete;
//  LongColumnData(LongColumnData &&other) noexcept;
//  LongColumnData &operator=(LongColumnData &&other) noexcept;
//  ~LongColumnData() final;
//
//  dataType_t getValue(int32_t row) const {
//    return (*data_)[row];
//  }
//
//  void setValue(int32_t row, dataType_t value) {
//    (*data_)[row] = value;
//  }
//
//  int32_t length() const final {
//    return data_->size();
//  }
//
//  int64_t getInt64(int32_t row) const final {
//    return getValue(row);
//  }
//
//  bool isNull(int32_t row) const final {
//    return valueIsNull(getValue(row));
//  }
//
//  void streamTo(std::ostream &s, int32_t row) const final {
//    auto value = getValue(row);
//    if (valueIsNull(value)) {
//      s << "(null)";
//    } else {
//      s << value;
//    }
//  }
//
//protected:
//  static bool valueIsNull(dataType_t value) {
//    return value == DeephavenConstants::NULL_LONG;
//  }
//
//  const char *getColumnType() const final {
//    return "long";
//  }
//
//  std::shared_ptr<LowLevelColumnData> getLowLevelColumnData() const final;
//
//private:
//  std::shared_ptr<std::vector<underlyingType_t>> data_;
//};
//
//class FloatColumnData final : public AbstractColumnData {
//  struct Private {};
//
//  // typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::IntArrayColumnData IntArrayColumnData;
//public:
//  typedef float dataType_t;
//  typedef float underlyingType_t;
//  // typedef IntArrayColumnData columnDataType_t;
//
//  static std::shared_ptr<FloatColumnData> create(std::vector<underlyingType_t> data);
//  static std::shared_ptr<FloatColumnData> create(std::shared_ptr<std::vector<underlyingType_t>> data);
//
//  FloatColumnData(Private, std::shared_ptr<std::vector<underlyingType_t>> data);
//  FloatColumnData(const FloatColumnData &other) = delete;
//  FloatColumnData &operator=(const FloatColumnData &other) = delete;
//  ~FloatColumnData() final;
//
//  dataType_t getValue(int32_t row) const {
//    return (*data_)[row];
//  }
//
//  void setValue(int32_t row, dataType_t value) {
//    (*data_)[row] = value;
//  }
//
//  int32_t length() const final {
//    return data_->size();
//  }
//
//  float getFloat(int32_t row) const final {
//    return getValue(row);
//  }
//
//  double getDouble(int32_t row) const final {
//    return getValue(row);
//  }
//
//  bool isNull(int32_t row) const final {
//    return valueIsNull(getValue(row));
//  }
//
//  void streamTo(std::ostream &s, int32_t row) const final {
//    auto value = getValue(row);
//    if (valueIsNull(value)) {
//      s << "(null)";
//    } else {
//      s << value;
//    }
//  }
//
//protected:
//  static bool valueIsNull(dataType_t value) {
//    return value == DeephavenConstants::NULL_FLOAT;
//  }
//
//  const char *getColumnType() const final {
//    return "float";
//  }
//
//  std::shared_ptr<LowLevelColumnData> getLowLevelColumnData() const final;
//
//private:
//  std::shared_ptr<std::vector<underlyingType_t>> data_;
//};
//
//class DoubleColumnData final : public AbstractColumnData {
//  struct Private {};
//  // typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::IntArrayColumnData IntArrayColumnData;
//public:
//  typedef double dataType_t;
//  typedef double underlyingType_t;
//  // typedef IntArrayColumnData columnDataType_t;
//
//  static std::shared_ptr<DoubleColumnData> create(std::vector<underlyingType_t> intData);
//  static std::shared_ptr<DoubleColumnData> create(std::shared_ptr<std::vector<underlyingType_t>> intData);
//
//  DoubleColumnData(Private, std::shared_ptr<std::vector<underlyingType_t>> data);
//  DoubleColumnData(const DoubleColumnData &other) = delete;
//  DoubleColumnData &operator=(const DoubleColumnData &other) = delete;
//  DoubleColumnData(DoubleColumnData &&other) noexcept;
//  DoubleColumnData &operator=(DoubleColumnData &&other) noexcept;
//  ~DoubleColumnData() final;
//
//  dataType_t getValue(int32_t row) const {
//    return (*data_)[row];
//  }
//
//  void setValue(int32_t row, dataType_t value) {
//    (*data_)[row] = value;
//  }
//
//  int32_t length() const final {
//    return data_->size();
//  }
//
//  double getDouble(int32_t row) const final {
//    return getValue(row);
//  }
//
//  bool isNull(int32_t row) const final {
//    return valueIsNull(getValue(row));
//  }
//
//  void streamTo(std::ostream &s, int32_t row) const final {
//    auto value = getValue(row);
//    if (valueIsNull(value)) {
//      s << "(null)";
//    } else {
//      s << value;
//    }
//  }
//
//protected:
//  static bool valueIsNull(dataType_t value) {
//    return value == DeephavenConstants::NULL_DOUBLE;
//  }
//
//  const char *getColumnType() const final {
//    return "double";
//  }
//
//  std::shared_ptr<LowLevelColumnData> getLowLevelColumnData() const final;
//
//private:
//  std::shared_ptr<std::vector<underlyingType_t>> data_;
//};
//
//class DBDateTimeColumnData final : public AbstractColumnData {
//  struct Private {};
//
//  // typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::IntArrayColumnData IntArrayColumnData;
//public:
//  typedef DBDateTime dataType_t;
//  typedef int64_t underlyingType_t;
//  // typedef IntArrayColumnData columnDataType_t;
//
//  static std::shared_ptr<DBDateTimeColumnData> create(const std::vector<dataType_t> &data);
//  static std::shared_ptr<DBDateTimeColumnData> create(std::vector<underlyingType_t> data);
//  static std::shared_ptr<DBDateTimeColumnData> create(std::shared_ptr<std::vector<underlyingType_t>> data);
//
//  DBDateTimeColumnData(Private, std::shared_ptr<std::vector<underlyingType_t>> data);
//  DBDateTimeColumnData(const DBDateTimeColumnData &other) = delete;
//  DBDateTimeColumnData &operator=(const DBDateTimeColumnData &other) = delete;
//  DBDateTimeColumnData(DBDateTimeColumnData &&other) noexcept;
//  DBDateTimeColumnData &operator=(DBDateTimeColumnData &&other) noexcept;
//  ~DBDateTimeColumnData() final;
//
//  dataType_t getValue(int32_t row) const {
//    return DBDateTime::fromNanos((*data_)[row]);
//  }
//
//  void setValue(int32_t row, dataType_t value) {
//    (*data_)[row] = value.nanos();
//  }
//
//  int32_t length() const final {
//    return data_->size();
//  }
//
//  int64_t getInt64(int32_t row) const final {
//    return (*data_)[row];
//  }
//
//  bool isNull(int32_t row) const final {
//    return valueIsNull(getValue(row));
//  }
//
//  void streamTo(std::ostream &s, int32_t row) const final {
//    auto value = getValue(row);
//    if (valueIsNull(value)) {
//      s << "(null)";
//    } else {
//      s << value;
//    }
//  }
//
//protected:
//  static bool valueIsNull(dataType_t value) {
//    return value.nanos() == DeephavenConstants::NULL_LONG;
//  }
//
//  const char *getColumnType() const final {
//    return "com.illumon.iris.db.tables.utils.DBDateTime";
//  }
//
//  std::shared_ptr<LowLevelColumnData> getLowLevelColumnData() const final;
//
//private:
//  std::shared_ptr<std::vector<underlyingType_t>> data_;
//};
//
//class StringColumnData final : public AbstractColumnData {
//  struct Private {};
//
//  // typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::IntArrayColumnData IntArrayColumnData;
//public:
//  typedef std::shared_ptr<std::string> dataType_t;
//  typedef std::shared_ptr<std::string> underlyingType_t;
//
//  static std::shared_ptr<StringColumnData> create(std::vector<underlyingType_t> data);
//  static std::shared_ptr<StringColumnData> create(std::shared_ptr<std::vector<underlyingType_t>> data);
//
//  StringColumnData(Private, std::shared_ptr<std::vector<underlyingType_t>> data);
//  StringColumnData(const StringColumnData &other) = delete;
//  StringColumnData &operator=(const StringColumnData &other) = delete;
//  StringColumnData(StringColumnData &&other) noexcept;
//  StringColumnData &operator=(StringColumnData &&other) noexcept;
//  ~StringColumnData() final;
//
//  const dataType_t &getValue(int32_t row) const {
//    return (*data_)[row];
//  }
//
//  void setValue(int32_t row, dataType_t value) {
//    (*data_)[row] = std::move(value);
//  }
//
//  int32_t length() const final {
//    return data_->size();
//  }
//
//  bool isNull(int32_t row) const final {
//    return valueIsNull(getValue(row));
//  }
//
//  void streamTo(std::ostream &s, int32_t row) const final {
//    const auto &value = getValue(row);
//    if (valueIsNull(value)) {
//      s << "(null)";
//    } else {
//      s << *value;
//    }
//  }
//
//protected:
//  static bool valueIsNull(const dataType_t &value) {
//    return value == nullptr;
//  }
//
//  const char *getColumnType() const final {
//    return "java.lang.String";
//  }
//
//  std::shared_ptr<LowLevelColumnData> getLowLevelColumnData() const final;
//
//private:
//  std::shared_ptr<std::vector<underlyingType_t>> data_;
//};
//}  // namespace data
//}  // namespace highlevel
//}  // namespace openAPI
//}  // namespace deephaven
