#pragma once
#include <cstdint>
#include "core/deserializer.h"
#include "core/serializer.h"

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
class TableHandleCustom {
public:
  TableHandleCustom() = default;
  TableHandleCustom(int32_t connectionId, int32_t clientId, int32_t serverId)
      : connectionId_(connectionId), clientId_(clientId), serverId_(serverId) {}
  TableHandleCustom(TableHandleCustom &&other) noexcept = default;
  TableHandleCustom &operator=(TableHandleCustom &&other) noexcept = default;

  void serialize(deephaven::openAPI::core::remoting::util::Serializer *serializer) const;

  static TableHandleCustom deserialize(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);

  int32_t connectionId() const { return connectionId_; }
  int32_t clientId() const { return clientId_; }
  int32_t serverId() const { return serverId_; }

private:
  int32_t connectionId_ = 0;
  int32_t clientId_ = 0;
  int32_t serverId_ = 0;
};

namespace treetable {
//public object Leaf { get; set; }
//public long? Nanos { get; set; }
//public object[] Array { get; set; }
//public object[] List { get; set; }
class KeyCustom {
public:
  KeyCustom(KeyCustom &&other) noexcept = default;
  KeyCustom &operator=(KeyCustom &&other) noexcept = default;

  void serialize(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {}
  static KeyCustom deserialize(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    // TODO(kosak)
    return {};
  }
};
}  // namespace treetable
}  // namespace data {
namespace ide {
class ExecutionHandleCustom {
public:
  ExecutionHandleCustom(ExecutionHandleCustom &&other) noexcept = default;
  ExecutionHandleCustom &operator=(ExecutionHandleCustom &&other) noexcept = default;

  void serialize(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {}
  static ExecutionHandleCustom deserialize(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    // TODO(kosak)
    return {};
  }
};

class ScriptHandleCustom {
public:
  ScriptHandleCustom(ScriptHandleCustom &&other) noexcept = default;
  ScriptHandleCustom &operator=(ScriptHandleCustom &&other) noexcept = default;

  void serialize(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {}
  static ScriptHandleCustom deserialize(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return {};
  }
};

}  // namespace ide
}  // namespace shared {
}  // namespace web {
}  // namespace iris {
}  // namespace illumon {
}  // namespace com {

namespace java {
namespace lang {
class BooleanCustom {
public:
  BooleanCustom(BooleanCustom &&other) noexcept = default;
  BooleanCustom &operator=(BooleanCustom &&other) noexcept = default;

  void serialize(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {}
  static BooleanCustom deserialize(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    // TODO(kosak)
    return {};
  }
};
class ByteCustom {
public:
  ByteCustom(ByteCustom &&other) noexcept = default;
  ByteCustom &operator=(ByteCustom &&other) noexcept = default;

  void serialize(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {}
  static ByteCustom deserialize(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    // TODO(kosak)
    return {};
  }
};
class CharacterCustom {
public:
  CharacterCustom(CharacterCustom &&other) noexcept = default;
  CharacterCustom &operator=(CharacterCustom &&other) noexcept = default;

  void serialize(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {}
  static CharacterCustom deserialize(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    // TODO(kosak)
    return {};
  }
};
class DoubleCustom {
public:
  DoubleCustom(DoubleCustom &&other) noexcept = default;
  DoubleCustom &operator=(DoubleCustom &&other) noexcept = default;

  void serialize(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {}
  static DoubleCustom deserialize(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    // TODO(kosak)
    return {};
  }
};
class FloatCustom {
public:
  FloatCustom(FloatCustom &&other) noexcept = default;
  FloatCustom &operator=(FloatCustom &&other) noexcept = default;

  void serialize(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {}
  static FloatCustom deserialize(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    // TODO(kosak)
    return {};
  }
};
class IntegerCustom {
public:
  IntegerCustom(IntegerCustom &&other) noexcept = default;
  IntegerCustom &operator=(IntegerCustom &&other) noexcept = default;

  void serialize(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {}
  static IntegerCustom deserialize(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    // TODO(kosak)
    return {};
  }
};
class LongCustom {
public:
  LongCustom(LongCustom &&other) noexcept = default;
  LongCustom &operator=(LongCustom &&other) noexcept = default;

  void serialize(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {}
  static LongCustom deserialize(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    // TODO(kosak)
    return {};
  }
};
class ShortCustom {
public:
  ShortCustom(ShortCustom &&other) noexcept = default;
  ShortCustom &operator=(ShortCustom &&other) noexcept = default;

  void serialize(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {}
  static ShortCustom deserialize(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    // TODO(kosak)
    return {};
  }
};
class StringCustom {
public:
  StringCustom(StringCustom &&other) noexcept = default;
  StringCustom &operator=(StringCustom &&other) noexcept = default;
  void serialize(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {}
  static StringCustom deserialize(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    // TODO(kosak)
    return {};
  }
};
class VoidCustom {
public:
  VoidCustom(VoidCustom &&other) noexcept = default;
  VoidCustom &operator=(VoidCustom &&other) noexcept = default;
  void serialize(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {}
  static VoidCustom deserialize(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    // TODO(kosak)
    return {};
  }
};
}  // namespace lang
namespace math {
class BigDecimalCustom {
public:
  BigDecimalCustom(BigDecimalCustom &&other) noexcept = default;
  BigDecimalCustom &operator=(BigDecimalCustom &&other) noexcept = default;
  void serialize(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {}
  static BigDecimalCustom deserialize(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    // TODO(kosak)
    return {};
  }

};
class BigIntegerCustom {
public:
  BigIntegerCustom(BigIntegerCustom &&other) noexcept = default;
  BigIntegerCustom &operator=(BigIntegerCustom &&other) noexcept = default;
  void serialize(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {}
  static BigIntegerCustom deserialize(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    // TODO(kosak)
    return {};
  }
};
}  // namespace math
namespace util {
class BitSetCustom {
public:
  BitSetCustom() = default;
  explicit BitSetCustom(std::vector<int32_t> items) : items_(std::move(items)) {}
  BitSetCustom(BitSetCustom &&other) noexcept = default;
  BitSetCustom &operator=(BitSetCustom &&other) noexcept = default;

  void serialize(deephaven::openAPI::core::remoting::util::Serializer *serializer) const;

  static BitSetCustom deserialize(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);

private:
  std::vector<int32_t> items_;
};
}  // namespace util
}  // namespace java
}  // namespace custom
}  // namespace remoting
}  // namespace lowlevel
}  // namespace openAPI
}  // namespace deephaven
