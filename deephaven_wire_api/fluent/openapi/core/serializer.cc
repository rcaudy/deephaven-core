#include "core/serializer.h"
#include "utility/utility.h"

using deephaven::openAPI::utility::stringf;

namespace deephaven {
namespace openAPI {
namespace core {
namespace remoting {
namespace util {
Serializer::Serializer() = default;
Serializer::~Serializer() = default;

void Serializer::resetAndStartMeasuring() {
  writing_ = false;
  size_ = 0;
  strings_.clear();
}

void Serializer::finishMeasuringStartWriting() {
  std::sort(strings_.begin(), strings_.end());
  auto up = std::unique(strings_.begin(), strings_.end());
  strings_.erase(up, strings_.end());
  commitStrings();
  buffer_.resize(size_);
  size_ = 0;
  writing_ = true;
}

void Serializer::finishWriting() {
  commitStrings();
  // For hygeine... I don't want to see dangling string_views
  strings_.clear();
}

void Serializer::commitStrings() {
  if (strings_.empty()) {
    return;
  }
  writeInt32(strings_.size());
  for (const auto &sv : strings_) {
    writeInt32(sv.size());
    writeBytes(sv.data(), sv.size());
  }
}

int32_t Serializer::lookupStringView(boost::string_view value) {
  if (!writing_) {
    strings_.push_back(value);
    return 0;
  }
  auto ip = std::find(strings_.begin(), strings_.end(), value);
  if (ip == strings_.end()) {
    throw std::runtime_error(stringf("Can't find %o in string pool", value));
  }
  // Note: string offsets in our protocol are 1-based
  return (int) (std::distance(strings_.begin(), ip) + 1);
}
}  // namespace util
}  // namespace remoting
}  // namespace core
}  // namespace openAPI
}  // namespace deephaven
