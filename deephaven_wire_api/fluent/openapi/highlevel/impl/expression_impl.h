#pragma once

#include <iostream>
#include <memory>
#include <boost/utility/string_view.hpp>

namespace deephaven {
namespace openAPI {
namespace highlevel {
namespace fluent {
namespace impl {
class BooleanExpressionImpl;

class IrisRepresentableImpl {
public:
  virtual ~IrisRepresentableImpl();
  virtual void streamIrisRepresentation(std::ostream &s) const = 0;

  // std::string toIrisRepresentation() const;
};

void streamIris(std::ostream &s, const std::shared_ptr<IrisRepresentableImpl> &o);

class ExpressionImpl : public virtual IrisRepresentableImpl {
public:
  static std::shared_ptr<BooleanExpressionImpl> createIsNull(std::shared_ptr<ExpressionImpl> impl);
  ~ExpressionImpl() override;
};
}  // namespace impl {
}  // namespace fluent
}  // namespace highlevel
}  // namespace openAPI
}  // namespace deephaven
