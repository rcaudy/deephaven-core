#include "highlevel/impl/expression_impl.h"

#include <memory>
#include "highlevel/impl/boolean_expression_impl.h"

namespace deephaven {
namespace openAPI {
namespace highlevel {
namespace fluent {
namespace impl {
namespace {
class IsNullExpressionImpl final : public BooleanExpressionImpl {
public:
  explicit IsNullExpressionImpl(std::shared_ptr<impl::ExpressionImpl> impl) : impl_(std::move(impl)) {}
  IsNullExpressionImpl(const IsNullExpressionImpl &) = delete;
  IsNullExpressionImpl &operator=(const IsNullExpressionImpl &) = delete;
  ~IsNullExpressionImpl() final;

  void appendIrisRepresentation(std::string *result) const final;

private:
  std::shared_ptr<impl::ExpressionImpl> impl_;
};
}  // namespace

IrisRepresentableImpl::~IrisRepresentableImpl() = default;
std::string IrisRepresentableImpl::toIrisRepresentation() const {
  std::string result;
  appendIrisRepresentation(&result);
  return result;
}

std::shared_ptr<BooleanExpressionImpl> ExpressionImpl::createIsNull(
    std::shared_ptr<ExpressionImpl> impl) {
  return std::make_shared<IsNullExpressionImpl>(std::move(impl));
}

ExpressionImpl::~ExpressionImpl() = default;

namespace {
IsNullExpressionImpl::~IsNullExpressionImpl() = default;
void IsNullExpressionImpl::appendIrisRepresentation(std::string *result) const {
  // TODO(kosak)
  result->append("isNull(");
  impl_->appendIrisRepresentation(result);
  result->push_back(')');
}
}  // namespace
}  // namespace impl {
}  // namespace fluent
}  // namespace highlevel
}  // namespace openAPI
}  // namespace deephaven
