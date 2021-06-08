#pragma once

#include <memory>
#include <vector>
#include <boost/utility/string_view.hpp>
#include "highlevel/data/dbdatetime.h"
#include "highlevel/impl/expression_impl.h"

namespace deephaven {
namespace openAPI {
namespace highlevel {
namespace fluent {
namespace impl {
class DateTimeExpressionImpl : public ExpressionImpl {
protected:
  typedef deephaven::openAPI::highlevel::data::DBDateTime DBDateTime;

public:
  static std::shared_ptr<DateTimeExpressionImpl> createFromLiteral(std::string value);
  static std::shared_ptr<DateTimeExpressionImpl> createFromDBDateTime(const DBDateTime &value);

  static std::shared_ptr<BooleanExpressionImpl> createComparison(
      std::shared_ptr<DateTimeExpressionImpl> lhs, const char *op,
      std::shared_ptr<DateTimeExpressionImpl> rhs);

  ~DateTimeExpressionImpl() override;
};
}  // namespace impl
}  // namespace fluent
}  // namespace highlevel
}  // namespace openAPI
}  // namespace deephaven
