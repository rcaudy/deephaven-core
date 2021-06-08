#pragma once

#include <cstdlib>
#include <memory>

namespace deephaven {
namespace openAPI {
namespace core {
namespace remoting {

// forward declarations
namespace util {
class Serializer;
class Deserializer;
}  // namespace util

struct Constants {
  static constexpr const int32_t openAPIVersion = 7;
  static constexpr const int32_t openAPIFlags = 0;
};

class Request {
public:
  virtual ~Request();
  virtual void serializeRequest(deephaven::openAPI::core::remoting::util::Serializer *s,
      int32_t callbackId) const = 0;
};

class Object {
protected:
  struct Private {};
public:
  // Also, all inherited classes of type T have a static method
  //   static shared_ptr<T> deserializeObject(Deserializer *d);
  virtual ~Object();
  virtual void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const = 0;
};

class Notification {
public:
  virtual ~Notification();
};
}  // namespace remoting
}  // namespace core
}  // namespace openAPI
}  // namespace deephaven
