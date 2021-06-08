#pragma once

#include <string>
#include <boost/utility/string_view.hpp>

namespace deephaven {
namespace openAPI {
namespace utility {
class EscapeUtils {
public:
  static std::string escapeJava(boost::string_view s);
  static void appendEscapedJava(boost::string_view s, std::string *dest);
};
}  // namespace utility
}  // namespace openAPI
}  // namespace deephaven
