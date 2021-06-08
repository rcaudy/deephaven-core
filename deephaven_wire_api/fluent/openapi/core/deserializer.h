#pragma once

#include <cstdint>
#include <cstring>
#include <map>
#include <memory>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <vector>
#include <boost/utility/string_view.hpp>
#include "core/protocol_base_classes.h"
#include "utility/utility.h"

namespace deephaven {
namespace openAPI {
namespace core {
namespace remoting {
namespace util {

class Deserializer {
  using Object = deephaven::openAPI::core::remoting::Object;

public:
  typedef std::shared_ptr<Object> (*objectFactory_t)(Deserializer *);
  Deserializer(const char **dynamicSerializerNames,
      const Deserializer::objectFactory_t *dynamicSerializerMethods, size_t numDeserializers);
  Deserializer(const Deserializer &other) = delete;
  Deserializer &operator=(const Deserializer &other) = delete;
  ~Deserializer();

  void reset(const char *data, size_t size);
  void initStringPool(size_t poolOffset);

  bool readBool() {
    auto byte = readByte();
    return byte != 0;
  }

  int8_t readByte() {
    int8_t result;
    memcpy(&result, current_, sizeof(result));
    current_ += sizeof(result);
    return result;
  }

  char16_t readChar16() {
    char16_t result;
    memcpy(&result, current_, sizeof(result));
    current_ += sizeof(result);
    return result;
  }

  int16_t readInt16() {
    int16_t result;
    memcpy(&result, current_, sizeof(result));
    current_ += sizeof(result);
    return result;
  }

  int32_t readInt32() {
    int32_t result;
    memcpy(&result, current_, sizeof(result));
    current_ += sizeof(result);
    return result;
  }

  int64_t readInt64() {
    int64_t result;
    memcpy(&result, current_, sizeof(result));
    current_ += sizeof(result);
    return result;
  }

  float readFloat() {
    float result;
    memcpy(&result, current_, sizeof(result));
    current_ += sizeof(result);
    return result;
  }

  double readDouble() {
    double result;
    memcpy(&result, current_, sizeof(result));
    current_ += sizeof(result);
    return result;
  }

  const std::shared_ptr<std::string> &readSharedString();

  size_t remaining() const {
    return end_ - current_;
  }

  void advance(size_t offset) {
    current_ += offset;
  }

  template<typename T>
  std::shared_ptr<T> lookupOrDeserialize(boost::string_view typeHint,
      objectFactory_t factoryHint);

  const char *current() const { return current_; }

private:
  std::shared_ptr<Object> lookupOrDeserializeHelper(boost::string_view typeHint,
      objectFactory_t factoryHint);

  std::map<boost::string_view, objectFactory_t> factories_;
  const char *current_ = nullptr;
  const char *end_ = nullptr;
  std::shared_ptr<std::string> nullString_;
  std::vector<std::shared_ptr<std::string>> stringPool_;
  std::vector<std::shared_ptr<Object>> backReferences_;
};

template<typename T>
std::shared_ptr<T> Deserializer::lookupOrDeserialize(boost::string_view typeHint,
    objectFactory_t factoryHint) {
  auto result = lookupOrDeserializeHelper(typeHint, factoryHint);
  if (result == nullptr) {
    return nullptr;
  }
  auto typedResult = std::dynamic_pointer_cast<T>(result);
  if (typedResult == nullptr) {
    const auto &dereffed = *result;
    throw std::runtime_error(
        deephaven::openAPI::utility::stringf("Couldn't cast pointer of type %o down to %o",
        typeid(dereffed).name(), typeid(T).name()));
  }
  return typedResult;
}
}  // namespace util
}  // namespace remoting
}  // namespace core
}  // namespace openAPI
}  // namespace deephaven
