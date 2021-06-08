#pragma once

#include <iostream>
#include <memory>
#include <type_traits>
#include <boost/utility/string_view.hpp>
#include "core/serializer.h"
#include "core/protocol_base_classes.h"
#include "lowlevel/util/protocol_container_classes.h"

namespace deephaven {
namespace openAPI {
namespace lowlevel {
namespace remoting {
namespace util {
class SerializerAdapter {
  using Object = deephaven::openAPI::core::remoting::Object;
  using Serializer = deephaven::openAPI::core::remoting::util::Serializer;
public:
  explicit SerializerAdapter(Serializer *serializer) : serializer_(serializer) {}

  // We take a pointer so that we can suppress any type promotions that the compiler might otherwise
  // try to do

  // At the topmost level, we decide whether T is an enum or not
  template<typename T>
  void write(const T *item) {
    writeHelper(item, std::is_enum<T>{});
  }

  // If T is an enum, we handle it here.
  template<typename T>
  void writeHelper(const T *theEnum, std::true_type) {
    auto raw = static_cast<int32_t>(*theEnum);
    auto typeName = AggregateTypeName<T>::typeName;
    serializer_->writeStringView(typeName);
    serializer_->writeInt32(raw);
  }

  // If T is not an enum, then it's
  // 1. a shared_ptr<vector<U>>, and deserializing U involves a wrapping cache object
  // 2. a shared_ptr<string>
  // 3. a shared_ptr<U> where U is some Object
  // 4. a simple type other than enum
  template<typename U>
  void writeHelper(const std::shared_ptr<U> *sp, std::false_type) {
    writeHelperSharedPtr(sp->get());
  }

  // case 1. a shared_ptr<vector<U>>, and deserializing U involves recursion
  template<typename U>
  void writeHelperSharedPtr(const std::vector<U> *vec) {
    if (vec == nullptr) {
      serializer_->writeInt32(0);
      return;
    }
    auto typeName = AggregateTypeName<std::vector<U>>::typeName;
    serializer_->writeStringView(typeName);
    serializer_->writeInt32(vec->size());
    // TODO(kosak): blast these out as a range if they are simple types
    for (const auto &element : *vec) {
      write(&element);
    }
  }

  void writeHelperSharedPtr(const std::string *s) {
    serializer_->writeSharedString(s);
  }

  // 3. a shared_ptr<U> where U is some Object
  void writeHelperSharedPtr(const Object *object) {
    if (object == nullptr) {
      serializer_->writeInt32(0);
      return;
    }
    object->serializeObject(serializer_);
  }

  // The rest of these are case 3
  void writeHelper(const bool *value, std::false_type) {
    serializer_->writeBool(*value);
  }

  void writeHelper(const int8_t *value, std::false_type) {
    serializer_->writeByte(*value);
  }

  void writeHelper(const char16_t *value, std::false_type) {
    serializer_->writeChar16(*value);
  }

  void writeHelper(const int16_t *value, std::false_type) {
    serializer_->writeInt16(*value);
  }

  void writeHelper(const int32_t *value, std::false_type) {
    serializer_->writeInt32(*value);
  }

  void writeHelper(const int64_t *value, std::false_type) {
    serializer_->writeInt64(*value);
  }

  void writeHelper(const float *value, std::false_type) {
    serializer_->writeFloat(*value);
  }

  void writeHelper(const double *value, std::false_type) {
    serializer_->writeDouble(*value);
  }

private:
  // Does not own.
  Serializer *serializer_ = nullptr;
};
}  // namespace util
}  // namespace remoting
}  // namespace lowlevel
}  // namespace openAPI
}  // namespace deephaven
