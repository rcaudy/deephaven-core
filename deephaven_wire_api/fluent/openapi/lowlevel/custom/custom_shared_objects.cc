#include "lowlevel/custom/custom_shared_objects.h"
#include "lowlevel/util/deserializer_adapter.h"
#include "lowlevel/util/serializer_adapter.h"

using deephaven::openAPI::core::remoting::util::Deserializer;
using deephaven::openAPI::core::remoting::util::Serializer;
using deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter;
using deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter;

namespace deephaven {
namespace openAPI {
namespace lowlevel {
namespace remoting {
namespace custom {
namespace com {
namespace illumon {
namespace iris {
namespace web {
namespace shared {
namespace data {
void TableHandleCustom::serialize(Serializer *serializer) const {
  SerializerAdapter sa(serializer);
  sa.write(&connectionId_);
  sa.write(&clientId_);
  sa.write(&serverId_);
}

TableHandleCustom TableHandleCustom::deserialize(Deserializer *deserializer) {
  int32_t connectionId;
  int32_t clientId;
  int32_t serverId;
  DeserializerAdapter da(deserializer);
  da.read(&connectionId);
  da.read(&clientId);
  da.read(&serverId);
  return {connectionId, clientId, serverId};
}

namespace treetable {
//public object Leaf { get; set; }
//public long? Nanos { get; set; }
//public object[] Array { get; set; }
//public object[] List { get; set; }
// class KeyCustom
}  // namespace treetable
}  // namespace data {

namespace ide {
// class ExecutionHandleCustom {
// class ScriptHandleCustom {
}  // namespace ide
}  // namespace shared {
}  // namespace web {
}  // namespace iris {
}  // namespace illumon {
}  // namespace com {

namespace java {
namespace lang {
// class BooleanCustom {
// class ByteCustom {
// class CharacterCustom {
// class DoubleCustom {
// class FloatCustom {
// class IntegerCustom {
// class LongCustom {
// class ShortCustom {
// class StringCustom {
// class VoidCustom {
}  // namespace lang
namespace math {
// class BigDecimalCustom {
// class BigIntegerCustom {
}  // namespace math
namespace util {
void BitSetCustom::serialize(Serializer *serializer) const {
  SerializerAdapter sa(serializer);
  int32_t size = items_.size();
  sa.write(&size);
  for (const auto &item : items_) {
    sa.write(&item);
  }
}

BitSetCustom BitSetCustom::deserialize(Deserializer *deserializer) {
  DeserializerAdapter da(deserializer);
  int32_t size;
  std::vector<int32_t> items;
  da.read(&size);
  items.reserve(size);
  for (int32_t i = 0; i < size; ++i) {
    int32_t item;
    da.read(&item);
    items.push_back(item);
  }
  return BitSetCustom(std::move(items));
}
}  // namespace util
}  // namespace java
}  // namespace custom
}  // namespace remoting
}  // namespace lowlevel
}  // namespace openAPI
}  // namespace deephaven
