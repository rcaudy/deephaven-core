#pragma once

#include <vector>
#include <string>
#include <cstring>
#include <cstdint>
#include <boost/utility/string_view.hpp>
#include "utility/utility.h"

namespace deephaven {
namespace openAPI {
namespace core {
namespace remoting {
namespace util {
class Serializer {
public:
  Serializer();
  Serializer(const Serializer &other) = delete;
  Serializer &operator=(const Serializer &other) = delete;
  ~Serializer();

  void writeBytes(const char *src, size_t srcSize) {
    if (writing_) {
      std::memcpy(buffer_.data() + size_, src, srcSize);
    }
    size_ += srcSize;
  }

  void writeBool(bool value) {
    static_assert(sizeof(value) == 1, "sizeof");
    writeBytes(deephaven::openAPI::utility::bit_cast<const char *>(&value), sizeof(value));
  }

  void writeByte(int8_t value) {
    static_assert(sizeof(value) == 1, "sizeof");
    writeBytes(deephaven::openAPI::utility::bit_cast<const char *>(&value), sizeof(value));
  }

  void writeChar16(char16_t value) {
    static_assert(sizeof(value) == 2, "sizeof");
    writeBytes(deephaven::openAPI::utility::bit_cast<const char *>(&value), sizeof(value));
  }

  void writeInt16(int16_t value) {
    static_assert(sizeof(value) == 2, "sizeof");
    writeBytes(deephaven::openAPI::utility::bit_cast<const char *>(&value), sizeof(value));
  }

  void writeInt32(int32_t value) {
    static_assert(sizeof(value) == 4, "sizeof");
    writeBytes(deephaven::openAPI::utility::bit_cast<const char *>(&value), sizeof(value));
  }

  void writeInt64(int64_t value) {
    static_assert(sizeof(value) == 8, "sizeof");
    writeBytes(deephaven::openAPI::utility::bit_cast<const char *>(&value), sizeof(value));
  }

  void writeFloat(float value) {
    static_assert(sizeof(value) == 4, "sizeof");
    writeBytes(deephaven::openAPI::utility::bit_cast<const char *>(&value), sizeof(value));
  }

  void writeDouble(double value) {
    static_assert(sizeof(value) == 8, "sizeof");
    writeBytes(deephaven::openAPI::utility::bit_cast<const char *>(&value), sizeof(value));
  }

  void writeSharedString(const std::string *s) {
    auto result = s == nullptr ? 0 : lookupStringView(*s);
    writeInt32(result);
  }

  void writeStringView(boost::string_view value) {
    auto result = lookupStringView(value);
    writeInt32(result);
  }

  int32_t lookupStringView(boost::string_view value);

  // Resets the object to the "measuring" state
  void resetAndStartMeasuring();
  // Resets the object to the "writing" state
  void finishMeasuringStartWriting();
  // Finishes the "writing" state. After this call the buffer is ready.
  void finishWriting();

  const char *data() const { return buffer_.data(); }
  size_t size() const { return size_; }

private:
  void commitStrings();

  std::vector<char> buffer_;
  std::vector<boost::string_view> strings_;
  bool writing_ = false;
  size_t size_ = 0;
};
}  // namespace util
}  // namespace remoting
}  // namespace core
}  // namespace openAPI
}  // namespace deephaven
