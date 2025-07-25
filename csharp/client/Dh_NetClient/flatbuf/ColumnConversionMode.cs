// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace io.deephaven.barrage.flatbuf
{

/// There will always be types that cannot be easily supported over IPC. These are the options:
///   Stringify (default) - Pretend the column is a string when sending over Arrow Flight (default)
///   JavaSerialization   - Use java serialization; the client is responsible for the deserialization
///   ThrowError          - Refuse to send the column and throw an internal error sharing as much detail as possible
public enum ColumnConversionMode : sbyte
{
  Stringify = 1,
  JavaSerialization = 2,
  ThrowError = 3,
};


}
