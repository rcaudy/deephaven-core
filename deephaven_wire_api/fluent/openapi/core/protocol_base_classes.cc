#include "core/protocol_base_classes.h"

namespace deephaven {
namespace openAPI {
namespace core {
namespace remoting {
constexpr const int32_t Constants::openAPIVersion;
constexpr const int32_t Constants::openAPIFlags;

Request::~Request() = default;
Object::~Object() = default;
Notification::~Notification() = default;
}  // namespace remoting
}  // namespace core
}  // namespace openAPI
}  // namespace deephaven
