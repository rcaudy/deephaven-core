/*
 * Copyright (c) 2016-2020 Deephaven Data Labs and Patent Pending
 */
#include <string>
#include "highlevel/data/column_data.h"

namespace deephaven {
namespace openAPI {
namespace highlevel {
namespace data {

typedef deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData LowLevelColumnData;

using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnDefinition;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnDataVisitor;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::BigDecimalArrayColumnData;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::BigIntegerArrayColumnData;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ByteArrayColumnData;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::CharArrayColumnData;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::DoubleArrayColumnData;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::FloatArrayColumnData;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::IntArrayColumnData;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::LocalDateArrayColumnData;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::LocalTimeArrayColumnData;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::LongArrayColumnData;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ShortArrayColumnData;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::StringArrayArrayColumnData;
using deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::StringArrayColumnData;

namespace {
struct CDVisitor_t final : public ColumnDataVisitor {
  explicit CDVisitor_t(const ColumnDefinition &colDef) : colDef_(colDef) {}

  void visit(const BigDecimalArrayColumnData *self) final {
    throw std::runtime_error("Not implemented");
  }
  void visit(const BigIntegerArrayColumnData *self) final {
    throw std::runtime_error("Not implemented");
  }
  void visit(const ByteArrayColumnData *self) final {
    if (*colDef_.type() == "java.lang.Boolean") {
      result_ = BooleanColumnData::create(self->data());
    } else {
      result_ = ByteColumnData::create(self->data());
    }
  }
  void visit(const CharArrayColumnData *self) final {
    result_ = CharColumnData::create(self->data());
  }
  void visit(const LowLevelColumnData *self) final {
    throw std::runtime_error("Not implemented");
  }
  void visit(const DoubleArrayColumnData *self) final {
    result_ = DoubleColumnData::create(self->data());
  }
  void visit(const FloatArrayColumnData *self) final {
    result_ = FloatColumnData::create(self->data());
  }
  void visit(const IntArrayColumnData *self) final {
    result_ = IntColumnData::create(self->data());
  }
  void visit(const LocalDateArrayColumnData *self) final {
    throw std::runtime_error("Not implemented");
  }
  void visit(const LocalTimeArrayColumnData *self) final {
    throw std::runtime_error("Not implemented");
  }
  void visit(const LongArrayColumnData *self) final {
    if (*colDef_.type() == "com.illumon.iris.db.tables.utils.DBDateTime") {
      result_ = DBDateTimeColumnData::create(self->data());
    } else {
      result_ = LongColumnData::create(self->data());
    }
  }
  void visit(const ShortArrayColumnData *self) final {
    result_ = ShortColumnData::create(self->data());
  }
  void visit(const StringArrayArrayColumnData *self) final {
    throw std::runtime_error("Not implemented");
  }
  void visit(const StringArrayColumnData *self) final {
    result_ = StringColumnData::create(self->data());
  }

  const ColumnDefinition &colDef_;
  std::shared_ptr<ColumnData> result_;
};
}  // namespace

std::shared_ptr<ColumnData> ColumnData::createFromColdef(const ColumnDefinition &colDef,
    const LowLevelColumnData &colData) {
  CDVisitor_t visitor(colDef);
  colData.acceptVisitor(&visitor);
  return std::move(visitor.result_);
}

bool AbstractColumnData::getBoolean(int32_t row) const {
  throw std::runtime_error("Not implemented");
}

char16_t AbstractColumnData::getChar(int32_t row) const {
  throw std::runtime_error("Not implemented");
}

int8_t AbstractColumnData::getByte(int32_t row) const {
  throw std::runtime_error("Not implemented");
}

int16_t AbstractColumnData::getInt16(int32_t row) const {
  throw std::runtime_error("Not implemented");
}

int32_t AbstractColumnData::getInt32(int32_t row) const {
  throw std::runtime_error("Not implemented");
}

int64_t AbstractColumnData::getInt64(int32_t row) const {
  throw std::runtime_error("Not implemented");
}

float AbstractColumnData::getFloat(int32_t row) const {
  throw std::runtime_error("Not implemented");
}

double AbstractColumnData::getDouble(int32_t row) const {
  throw std::runtime_error("Not implemented");
}

const std::string &AbstractColumnData::getString(int32_t row) const {
  throw std::runtime_error("Not implemented");
}

std::shared_ptr<ByteColumnData> ByteColumnData::create(std::vector<underlyingType_t> data) {
  auto spData = std::make_shared<std::vector<underlyingType_t>>(std::move(data));
  return create(std::move(spData));
}

std::shared_ptr<ByteColumnData> ByteColumnData::create(
    std::shared_ptr<std::vector<underlyingType_t>> data) {
  return std::make_shared<ByteColumnData>(Private(), std::move(data));
}

ByteColumnData::ByteColumnData(Private, std::shared_ptr<std::vector<underlyingType_t>> data) :
    data_(std::move(data)) {}

ByteColumnData::~ByteColumnData() = default;

std::shared_ptr<LowLevelColumnData> ByteColumnData::getLowLevelColumnData() const {
  return ByteArrayColumnData::create(data_);
}

std::shared_ptr<BooleanColumnData> BooleanColumnData::create(const std::vector<dataType_t> &data) {
  auto spData = std::make_shared<std::vector<underlyingType_t>>();
  spData->reserve(data.size());
  for (const auto &element : data) {
    spData->push_back(boolToSbyte(element));
  }
  return create(std::move(spData));
}

std::shared_ptr<BooleanColumnData> BooleanColumnData::create(std::vector<underlyingType_t> data) {
  auto spData = std::make_shared<std::vector<underlyingType_t>>(std::move(data));
  return create(std::move(spData));
}

std::shared_ptr<BooleanColumnData> BooleanColumnData::create(
    std::shared_ptr<std::vector<underlyingType_t>> data) {
  return std::make_shared<BooleanColumnData>(Private(), std::move(data));
}

BooleanColumnData::BooleanColumnData(Private, std::shared_ptr<std::vector<underlyingType_t>> data) :
    data_(std::move(data)) {}
BooleanColumnData::~BooleanColumnData() = default;

std::shared_ptr<LowLevelColumnData> BooleanColumnData::getLowLevelColumnData() const {
  return ByteArrayColumnData::create(data_);
}

std::shared_ptr<CharColumnData> CharColumnData::create(std::vector<underlyingType_t> data) {
  auto spData = std::make_shared<std::vector<underlyingType_t>>(std::move(data));
  return create(std::move(spData));
}

std::shared_ptr<CharColumnData> CharColumnData::create(
    std::shared_ptr<std::vector<underlyingType_t>> data) {
  return std::make_shared<CharColumnData>(Private(), std::move(data));
}

CharColumnData::CharColumnData(Private, std::shared_ptr<std::vector<underlyingType_t>> data) :
    data_(std::move(data)) {}
CharColumnData::~CharColumnData() = default;

std::shared_ptr<LowLevelColumnData> CharColumnData::getLowLevelColumnData() const {
  return CharArrayColumnData::create(data_);
}

std::shared_ptr<ShortColumnData> ShortColumnData::create(std::vector<underlyingType_t> data) {
  auto spData = std::make_shared<std::vector<underlyingType_t>>(std::move(data));
  return create(std::move(spData));
}

std::shared_ptr<ShortColumnData> ShortColumnData::create(
    std::shared_ptr<std::vector<underlyingType_t>> data) {
  return std::make_shared<ShortColumnData>(Private(), std::move(data));
}

ShortColumnData::ShortColumnData(Private, std::shared_ptr<std::vector<underlyingType_t>> data) :
    data_(std::move(data)) {}
ShortColumnData::~ShortColumnData() = default;

std::shared_ptr<LowLevelColumnData> ShortColumnData::getLowLevelColumnData() const {
  return ShortArrayColumnData::create(data_);
}

std::shared_ptr<IntColumnData> IntColumnData::create(std::vector<underlyingType_t> data) {
  auto spData = std::make_shared<std::vector<underlyingType_t>>(std::move(data));
  return create(std::move(spData));
}

std::shared_ptr<IntColumnData> IntColumnData::create(
    std::shared_ptr<std::vector<underlyingType_t>> data) {
  return std::make_shared<IntColumnData>(Private(), std::move(data));
}

IntColumnData::IntColumnData(Private, std::shared_ptr<std::vector<underlyingType_t>> data) :
    data_(std::move(data)) {}
IntColumnData::IntColumnData(IntColumnData &&other) noexcept = default;
IntColumnData &IntColumnData::operator=(IntColumnData &&other) noexcept = default;
IntColumnData::~IntColumnData() = default;

std::shared_ptr<LowLevelColumnData> IntColumnData::getLowLevelColumnData() const {
  return IntArrayColumnData::create(data_);
}

std::shared_ptr<LongColumnData> LongColumnData::create(std::vector<underlyingType_t> data) {
  auto spData = std::make_shared<std::vector<underlyingType_t>>(std::move(data));
  return create(std::move(spData));
}

std::shared_ptr<LongColumnData> LongColumnData::create(
    std::shared_ptr<std::vector<underlyingType_t>> data) {
  return std::make_shared<LongColumnData>(Private(), std::move(data));
}

LongColumnData::LongColumnData(Private, std::shared_ptr<std::vector<underlyingType_t>> data) :
    data_(std::move(data)) {}
LongColumnData::~LongColumnData() = default;

std::shared_ptr<LowLevelColumnData> LongColumnData::getLowLevelColumnData() const {
  return LongArrayColumnData::create(data_);
}

std::shared_ptr<FloatColumnData> FloatColumnData::create(std::vector<underlyingType_t> data) {
  return create(std::make_shared<std::vector<underlyingType_t >>(std::move(data)));
}

std::shared_ptr<FloatColumnData> FloatColumnData::create(
    std::shared_ptr<std::vector<underlyingType_t>> intData) {
  return std::make_shared<FloatColumnData>(Private(), std::move(intData));
}

FloatColumnData::FloatColumnData(Private, std::shared_ptr<std::vector<underlyingType_t>> data) :
    data_(std::move(data)) {}
FloatColumnData::~FloatColumnData() = default;

std::shared_ptr<LowLevelColumnData> FloatColumnData::getLowLevelColumnData() const {
  return FloatArrayColumnData::create(data_);
}

std::shared_ptr<DoubleColumnData> DoubleColumnData::create(std::vector<underlyingType_t> data) {
  return create(std::make_shared<std::vector<underlyingType_t >>(std::move(data)));
}

std::shared_ptr<DoubleColumnData> DoubleColumnData::create(
    std::shared_ptr<std::vector<underlyingType_t>> intData) {
  return std::make_shared<DoubleColumnData>(Private(), std::move(intData));
}

DoubleColumnData::DoubleColumnData(Private, std::shared_ptr<std::vector<underlyingType_t>> data) :
    data_(std::move(data)) {}
DoubleColumnData::DoubleColumnData(DoubleColumnData &&other) noexcept = default;
DoubleColumnData &DoubleColumnData::operator=(DoubleColumnData &&other) noexcept = default;
DoubleColumnData::~DoubleColumnData() = default;

std::shared_ptr<DBDateTimeColumnData> DBDateTimeColumnData::create(
    const std::vector<dataType_t> &data) {
  auto spData = std::make_shared<std::vector<underlyingType_t>>();
  spData->reserve(data.size());
  for (const auto &element : data) {
    spData->push_back(element.nanos());
  }
  return create(std::move(spData));
}

std::shared_ptr<LowLevelColumnData> DoubleColumnData::getLowLevelColumnData() const {
  return DoubleArrayColumnData::create(data_);
}

std::shared_ptr<DBDateTimeColumnData> DBDateTimeColumnData::create(
    std::vector<underlyingType_t> data) {
  auto spData = std::make_shared<std::vector<underlyingType_t>>(std::move(data));
  return create(std::move(spData));
}

std::shared_ptr<DBDateTimeColumnData> DBDateTimeColumnData::create(
    std::shared_ptr<std::vector<underlyingType_t>> data) {
  return std::make_shared<DBDateTimeColumnData>(Private(), std::move(data));
}

DBDateTimeColumnData::DBDateTimeColumnData(Private, std::shared_ptr<std::vector<underlyingType_t>> data) :
    data_(std::move(data)) {}
DBDateTimeColumnData::~DBDateTimeColumnData() = default;

std::shared_ptr<LowLevelColumnData> DBDateTimeColumnData::getLowLevelColumnData() const {
  return LongArrayColumnData::create(data_);
}

std::shared_ptr<StringColumnData> StringColumnData::create(std::vector<underlyingType_t> data) {
  return create(std::make_shared<std::vector<underlyingType_t>>(std::move(data)));
}

std::shared_ptr<StringColumnData> StringColumnData::create(
    std::shared_ptr<std::vector<underlyingType_t>> intData) {
  return std::make_shared<StringColumnData>(Private(), std::move(intData));
}

StringColumnData::StringColumnData(Private, std::shared_ptr<std::vector<underlyingType_t>> data) :
    data_(std::move(data)) {}
StringColumnData::StringColumnData(StringColumnData &&other) noexcept = default;
StringColumnData & StringColumnData::operator=(StringColumnData &&other) noexcept = default;
StringColumnData::~StringColumnData() = default;

std::shared_ptr<LowLevelColumnData> StringColumnData::getLowLevelColumnData() const {
  return StringArrayColumnData::create(data_);
}
}  // namespace data
}  // namespace highlevel
}  // namespace openAPI
}  // namespace deephaven
