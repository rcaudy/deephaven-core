#pragma once

#include <cstdlib>
#include <memory>

namespace deephaven {
namespace openAPI {
namespace lowlevel {
namespace remoting {
// This type enables a compile type lookup for array type names. This particular "master"
// template should never be expanded. Instead, there should always be a specialization for the T you
// are looking for. If you try to use this non-specialized template, the static assertion will fire.
template<typename T>
struct AggregateTypeName {
  // If you expand this template, you are missing a template specialization
  static_assert(!std::is_same<T,T>::value, "Failed to specialize AggregateTypeName for this type");
  // Useless, but helpful for documentation.
  static constexpr const char typeName[] = "type-name-string-goes-here";
};
}  // namespace remoting
}  // namespace lowlevel
}  // namespace openAPI
}  // namespace deephaven
