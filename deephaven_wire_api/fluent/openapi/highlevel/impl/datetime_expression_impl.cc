#include "datetime_expression_impl.h"

#include <memory>
#include <vector>
#include "highlevel/data/dbdatetime.h"
#include "highlevel/impl/boolean_expression_impl.h"
#include "highlevel/impl/expression_impl.h"
#include "utility/escape_utils.h"
#include "utility/utility.h"

using deephaven::openAPI::highlevel::data::DBDateTime;
using deephaven::openAPI::utility::appendSeparatedList;
using deephaven::openAPI::utility::EscapeUtils;

namespace deephaven {
namespace openAPI {
namespace highlevel {
namespace fluent {
namespace impl {
namespace {
class DateTimeLiteralImpl final : public DateTimeExpressionImpl {
public:
  explicit DateTimeLiteralImpl(std::string value) : value_(std::move(value)) {}
  ~DateTimeLiteralImpl() final = default;

  void appendIrisRepresentation(std::string *result) const final;

private:
  std::string value_;
};

class DateTimeDBDateTimeImpl final : public DateTimeExpressionImpl {
public:
  explicit DateTimeDBDateTimeImpl(const DBDateTime &value) : value_(value) {}
  ~DateTimeDBDateTimeImpl() final = default;

  void appendIrisRepresentation(std::string *result) const final;

private:
  DBDateTime value_;
};

class DateTimeComparisonImpl final : public BooleanExpressionImpl {
public:
  DateTimeComparisonImpl(std::shared_ptr<DateTimeExpressionImpl> lhs, const char *compareOp,
      std::shared_ptr<DateTimeExpressionImpl> rhs) : lhs_(std::move(lhs)), compareOp_(compareOp),
      rhs_(std::move(rhs)) {}
  ~DateTimeComparisonImpl() final = default;

  void appendIrisRepresentation(std::string *result) const final;

private:
  std::shared_ptr<DateTimeExpressionImpl> lhs_;
  const char *compareOp_ = nullptr;
  std::shared_ptr<DateTimeExpressionImpl> rhs_;
};

struct IrisAppender {
  void operator()(const std::shared_ptr<IrisRepresentableImpl> &item, std::string *result) const {
    item->appendIrisRepresentation(result);
  }
};
}  // namespace

std::shared_ptr<DateTimeExpressionImpl> DateTimeExpressionImpl::createFromLiteral(std::string value) {
  return std::make_shared<DateTimeLiteralImpl>(std::move(value));
}

std::shared_ptr<DateTimeExpressionImpl> DateTimeExpressionImpl::createFromDBDateTime(const DBDateTime &value) {
  return std::make_shared<DateTimeDBDateTimeImpl>(std::move(value));
}

std::shared_ptr<BooleanExpressionImpl> DateTimeExpressionImpl::createComparison(
    std::shared_ptr<DateTimeExpressionImpl> lhs, const char *op,
    std::shared_ptr<DateTimeExpressionImpl> rhs) {
  return std::make_shared<DateTimeComparisonImpl>(std::move(lhs), op, std::move(rhs));
}

DateTimeExpressionImpl::~DateTimeExpressionImpl() = default;

namespace {
void DateTimeLiteralImpl::appendIrisRepresentation(std::string *result) const {
  result->push_back('`');
  EscapeUtils::appendEscapedJava(value_, result);
  result->push_back('`');
}

void DateTimeDBDateTimeImpl::appendIrisRepresentation(std::string *result) const {
  result->push_back('`');
  value_.appendIrisRepresentation(result);
  result->push_back('`');
}

void DateTimeComparisonImpl::appendIrisRepresentation(std::string *result) const {
  result->push_back('(');
  lhs_->appendIrisRepresentation(result);
  result->push_back(' ');
  result->append(compareOp_);
  result->push_back(' ');
  rhs_->appendIrisRepresentation(result);
  result->push_back(')');
}
}   // namespace
}  // namespace impl
}  // namespace fluent
}  // namespace highlevel
}  // namespace openAPI
}  // namespace deephaven
