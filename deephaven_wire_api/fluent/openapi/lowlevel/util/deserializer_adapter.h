#pragma once

#include <iostream>
#include <memory>
#include <type_traits>
#include <boost/utility/string_view.hpp>
#include "core/protocol_base_classes.h"
#include "core/deserializer.h"
#include "lowlevel/util/protocol_container_classes.h"

using deephaven::openAPI::core::remoting::Object;

namespace deephaven {
namespace openAPI {
namespace lowlevel {
namespace remoting {
namespace util {
namespace internal {
template<typename T>
class CachedEnum final : public deephaven::openAPI::core::remoting::Object {
  typedef deephaven::openAPI::core::remoting::util::Deserializer Deserializer;
  struct Private {};
public:
  CachedEnum(Private, T data) : data_(data) {}
  ~CachedEnum() final = default;

  static std::shared_ptr<CachedEnum> deserializeObject(Deserializer *deserializer) {
    auto typeName = AggregateTypeName<T>::typeName;
    return deserializer->lookupOrDeserialize<CachedEnum>(typeName, &deserializeObjectHelper);
  }

  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final {
    // We never serialize CachedVectors... the SerializerAdapter just does it for the underlying
    // vectors.
    throw std::runtime_error("Not implemented");
  }

  T data() const { return data_; }

private:
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(Deserializer *deserializer);
  T data_;
};

template<typename T>
class CachedVector final : public deephaven::openAPI::core::remoting::Object {
  typedef deephaven::openAPI::core::remoting::util::Deserializer Deserializer;
  struct Private {};
public:
  CachedVector(Private, std::shared_ptr<std::vector<T>> data) : data_(std::move(data)) {}
  ~CachedVector() final = default;

  static std::shared_ptr<CachedVector> deserializeObject(Deserializer *deserializer) {
    auto typeName = AggregateTypeName<std::vector<T>>::typeName;
    return deserializer->lookupOrDeserialize<CachedVector>(typeName, &deserializeObjectHelper);
  }

  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final {
    // We never serialize CachedVectors... the SerializerAdapter just does it for the underlying
    // vectors.
    throw std::runtime_error("Not implemented");
  }

  const std::shared_ptr<std::vector<T>> &data() const { return data_; }

private:
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(Deserializer *deserializer);
  std::shared_ptr<std::vector<T>> data_;
};
}  // namespace internal

class DeserializerAdapter {
  typedef deephaven::openAPI::core::remoting::util::Deserializer Deserializer;
public:
  explicit DeserializerAdapter(Deserializer *deserializer) : deserializer_(deserializer) {}

  // We take a pointer so that we can suppress any type promotions that the compiler might otherwise
  // try to do

  // At the topmost level, we decide whether T is an enum or not
  template<typename T>
  void read(T *result) {
    readHelper(result, std::is_enum<T>());
  }

  // If T is an enum, we handle it here.
  template<typename T>
  void readHelper(T *theEnum, std::true_type) {
    auto cachedEnum = internal::CachedEnum<T>::deserializeObject(deserializer_);
    if (cachedEnum == nullptr) {
      // weird.
      *theEnum = static_cast<T>(0);
      return;
    }
    *theEnum = cachedEnum->data();
  }

  // If T is not an enum, then it's
  // 1. a shared_ptr<vector<V>>, and deserializing V involves a wrapping cache object
  // 2. a shared_ptr<std::string>
  // 3. a shared_ptr<U> where U is some Object
  // 4. a simple type other than enum
  template<typename U>
  void readHelper(std::shared_ptr<U> *sp, std::false_type) {
    readHelperSharedPtr(sp, sp->get());
  }

  // case 1. a shared_ptr<vector<V>>, and deserializing V involves recursion
  template<typename V>
  void readHelperSharedPtr(std::shared_ptr<std::vector<V>> *sp,
      const std::vector<V> *) {
    auto cachedVector = internal::CachedVector<V>::deserializeObject(deserializer_);
    if (cachedVector == nullptr) {
      sp->reset();
      return;
    }
    *sp = cachedVector->data();
  }

  // 2. a shared_ptr<std::string>
  void readHelperSharedPtr(std::shared_ptr<std::string> *sp, const std::string *) {
    *sp = deserializer_->readSharedString();
  }

  // 3. a shared_ptr<U> where U is some Object
  template<typename U>
  void readHelperSharedPtr(std::shared_ptr<U> *sp, const Object *) {
    *sp = U::deserializeObject(deserializer_);
  }

  // The rest of these are case 3
  void readHelper(bool *result, std::false_type) {
    *result = deserializer_->readBool();
  }

  void readHelper(int8_t *result, std::false_type) {
    *result = deserializer_->readByte();
  }

  void readHelper(int16_t *result, std::false_type) {
    *result = deserializer_->readInt16();
  }

  void readHelper(char16_t *result, std::false_type) {
    *result = deserializer_->readChar16();
  }

  void readHelper(int32_t *result, std::false_type) {
    *result = deserializer_->readInt32();
  }

  void readHelper(int64_t *result, std::false_type) {
    *result = deserializer_->readInt64();
  }

  void readHelper(float *result, std::false_type) {
    *result = deserializer_->readFloat();
  }

  void readHelper(double *result, std::false_type) {
    *result = deserializer_->readDouble();
  }

private:
  // Does not own.
  Deserializer *deserializer_ = nullptr;
};

namespace internal {
template<typename T>
std::shared_ptr<deephaven::openAPI::core::remoting::Object>
CachedVector<T>::deserializeObjectHelper(Deserializer *deserializer) {
  auto size = deserializer->readInt32();
  auto data = std::make_shared<std::vector<T>>();
  data->resize(size);

  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  for (int32_t i = 0; i < size; ++i) {
    da.read(&(*data)[i]);
  }
  return std::make_shared<CachedVector>(Private(), std::move(data));
}

template<typename T>
std::shared_ptr<deephaven::openAPI::core::remoting::Object>
CachedEnum<T>::deserializeObjectHelper(Deserializer *deserializer) {
  auto raw = deserializer->readInt32();
  auto data = static_cast<T>(raw);
  return std::make_shared<CachedEnum>(Private(), data);
}
}  // namespace internal
}  // namespace util
}  // namespace remoting
}  // namespace lowlevel
}  // namespace openAPI
}  // namespace deephaven
