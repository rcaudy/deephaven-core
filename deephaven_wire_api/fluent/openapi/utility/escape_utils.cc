#include "utility/escape_utils.h"

#include <codecvt>
#include <locale>
#include <string>
#include <boost/utility/string_view.hpp>

namespace deephaven {
namespace openAPI {
namespace utility {
std::string EscapeUtils::escapeJava(boost::string_view s) {
  std::string result;
  appendEscapedJava(s, &result);
  return result;
}

void EscapeUtils::appendEscapedJava(boost::string_view s, std::string *result) {
  typedef std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter_t;
  std::u16string u16s = converter_t().from_bytes(s.begin(), s.end());

  for (auto u16ch : u16s) {
    switch (u16ch) {
      case '\b':
        result->append("\\b");
        continue;
      case '\f':
        result->append("\\f");
        continue;
      case '\n':
        result->append("\\n");
        continue;
      case '\r':
        result->append("\\r");
        continue;
      case '\t':
        result->append("\\t");
        continue;
      case '"':
      case '\'':
      case '\\':
        result->push_back('\\');
        result->push_back(u16ch);
        continue;
      default:
        break;
    }

    if (u16ch < 32 || u16ch > 0x7f) {
      char buffer[16];  // plenty
      snprintf(buffer, sizeof(buffer), "\\u%04x", u16ch);
      result->append(buffer);
      continue;
    }
    result->push_back(u16ch);
  }
}
}  // namespace utility
}  // namespace openAPI
}  // namespace deephaven
