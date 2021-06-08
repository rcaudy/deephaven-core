#include "string_expression_impl.h"

#include <memory>
#include <vector>
#include "highlevel/impl/boolean_expression_impl.h"
#include "highlevel/impl/expression_impl.h"
#include "utility/escape_utils.h"
#include "utility/utility.h"

using deephaven::openAPI::utility::appendSeparatedList;
using deephaven::openAPI::utility::EscapeUtils;

namespace deephaven {
namespace openAPI {
namespace highlevel {
namespace fluent {
namespace impl {
namespace {
class StringLiteralImpl final : public StringExpressionImpl {
  struct Private {};
public:
  explicit StringLiteralImpl(std::string value) : value_(std::move(value)) {}
  ~StringLiteralImpl() final = default;

  void appendIrisRepresentation(std::string *result) const final;

private:
  std::string value_;
};

class StringConcatImpl final : public StringExpressionImpl {
public:
  static std::shared_ptr<StringExpressionImpl> create(std::shared_ptr<StringExpressionImpl> lhs,
      std::shared_ptr<StringExpressionImpl> rhs);

  explicit StringConcatImpl(std::vector<std::shared_ptr<StringExpressionImpl>> children) :
      children_(std::move(children)) {}
  ~StringConcatImpl() final = default;

  void appendIrisRepresentation(std::string *result) const final;

private:
  std::vector<std::shared_ptr<StringExpressionImpl>> children_;
};

class StringComparisonImpl final : public BooleanExpressionImpl {
public:
  StringComparisonImpl(std::shared_ptr<StringExpressionImpl> lhs, const char *compareOp,
      std::shared_ptr<StringExpressionImpl> rhs) : lhs_(std::move(lhs)), compareOp_(compareOp),
      rhs_(std::move(rhs)) {}
  ~StringComparisonImpl() final = default;

  void appendIrisRepresentation(std::string *result) const final;

private:
  std::shared_ptr<StringExpressionImpl> lhs_;
  const char *compareOp_ = nullptr;
  std::shared_ptr<StringExpressionImpl> rhs_;
};

struct IrisAppender {
  void operator()(const std::shared_ptr<IrisRepresentableImpl> &item, std::string *result) const {
    item->appendIrisRepresentation(result);
  }
};
}  // namespace

std::shared_ptr<StringExpressionImpl> StringExpressionImpl::createLiteral(std::string value) {
  return std::make_shared<StringLiteralImpl>(std::move(value));
}

std::shared_ptr<StringExpressionImpl> StringExpressionImpl::createAppend(
    std::shared_ptr<StringExpressionImpl> lhs, std::shared_ptr<StringExpressionImpl> rhs) {
  return StringConcatImpl::create(std::move(lhs), std::move(rhs));
}

std::shared_ptr<BooleanExpressionImpl> StringExpressionImpl::createComparison(
    std::shared_ptr<StringExpressionImpl> lhs, const char *op,
     std::shared_ptr<StringExpressionImpl> rhs) {
  return std::make_shared<StringComparisonImpl>(std::move(lhs), op, std::move(rhs));
}

StringExpressionImpl::~StringExpressionImpl() = default;

namespace {
void StringLiteralImpl::appendIrisRepresentation(std::string *result) const {
  result->push_back('`');
  EscapeUtils::appendEscapedJava(value_, result);
  result->push_back('`');
}

std::shared_ptr<StringExpressionImpl> StringConcatImpl::create(
    std::shared_ptr<StringExpressionImpl> lhs, std::shared_ptr<StringExpressionImpl> rhs) {
  std::vector<std::shared_ptr<StringExpressionImpl>> children;
  const auto *lhsAsConcat = dynamic_cast<const StringConcatImpl*>(lhs.get());
  if (lhsAsConcat != nullptr) {
    children.insert(children.end(), lhsAsConcat->children_.begin(), lhsAsConcat->children_.end());
  } else {
    children.push_back(std::move(lhs));
  }

  const auto *rhsAsAnd = dynamic_cast<const StringConcatImpl*>(rhs.get());
  if (rhsAsAnd != nullptr) {
    children.insert(children.end(), rhsAsAnd->children_.begin(), rhsAsAnd->children_.end());
  } else {
    children.push_back(std::move(rhs));
  }

  return std::make_shared<StringConcatImpl>(std::move(children));
}

void StringConcatImpl::appendIrisRepresentation(std::string *result) const {
  appendSeparatedList(children_.begin(), children_.end(), " + ", IrisAppender(), result);
}

void StringComparisonImpl::appendIrisRepresentation(std::string *result) const {
  result->push_back('(');
  lhs_->appendIrisRepresentation(result);
  result->push_back(' ');
  result->append(compareOp_);
  result->push_back(' ');
  rhs_->appendIrisRepresentation(result);
  result->push_back(')');
}
}  // namespace
}  // namespace impl
}  // namespace fluent
}  // namespace highlevel
}  // namespace openAPI
}  // namespace deephaven
