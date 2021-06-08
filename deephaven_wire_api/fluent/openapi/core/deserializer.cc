#include "core/deserializer.h"
#include "utility/utility.h"

using deephaven::openAPI::utility::stringf;

namespace deephaven {
namespace openAPI {
namespace core {
namespace remoting {
namespace util {
Deserializer::Deserializer(const char **dynamicSerializerNames,
    const Deserializer::objectFactory_t *dynamicSerializerMethods, size_t numDeserializers) {
  for (size_t i = 0; i < numDeserializers; ++i) {
    factories_[dynamicSerializerNames[i]] = dynamicSerializerMethods[i];
  }
}
Deserializer::~Deserializer() = default;

void Deserializer::reset(const char *data, size_t size) {
  current_ = data;
  end_ = data == nullptr ? nullptr : data + size;
  stringPool_.clear();
  backReferences_.clear();
}

void Deserializer::initStringPool(size_t poolOffset) {
  auto save = current_;
  current_ += poolOffset;
  auto numStrings = readInt32();
  for (int i = 0; i < numStrings; ++i) {
    auto nextSize = readInt32();
    auto nextString = std::make_shared<std::string>(current_, nextSize);
    stringPool_.push_back(std::move(nextString));
    advance(nextSize);
  }
  current_ = save;
}

const std::shared_ptr<std::string> &Deserializer::readSharedString() {
  auto index = readInt32();
  // String pools are one-based. 0 is the null string
  if (index == 0) {
    return nullString_;
  }
  return stringPool_[index - 1];
}

std::shared_ptr<Object> Deserializer::lookupOrDeserializeHelper(boost::string_view typeHint,
    objectFactory_t factoryHint) {
  auto index = readInt32();
  if (index < 0) {
    return backReferences_[-(index + 1)];
  }
  // The empty string pool reference is code for the null pointer
  if (index == 0) {
    return nullptr;
  }
  // The deserialization is typically recursive. So we reserve a slot for the result now, let the
  // recursion play out, and then store the result in that reserved slot.
  auto emptySlot = backReferences_.size();
  backReferences_.push_back({});

  const auto &spDtn = stringPool_[index - 1];
  boost::string_view dynamicTypeName(*spDtn);
  objectFactory_t factoryToUse;
  if (factoryHint != nullptr && dynamicTypeName == typeHint) {
    factoryToUse = factoryHint;
  } else {
    auto fp = factories_.find(dynamicTypeName);
    if (fp == factories_.end()) {
      throw std::runtime_error(stringf("Can't find a deserializer factory for %o", dynamicTypeName));
    }
    factoryToUse = fp->second;
  }
  auto result = (*factoryToUse)(this);
  backReferences_[emptySlot] = result;
  return result;
}
}  // namespace util
}  // namespace remoting
}  // namespace core
}  // namespace openAPI
}  // namespace deephaven
