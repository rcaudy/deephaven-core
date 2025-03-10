//
// Copyright (c) 2016-2025 Deephaven Data Labs and Patent Pending
//
// ****** AUTO-GENERATED CLASS - DO NOT EDIT MANUALLY
// ****** Run ReplicateTypedHashers or ./gradlew replicateTypedHashers to regenerate
//
// @formatter:off
package io.deephaven.engine.table.impl.by.typed.incopenagg.gen;

import io.deephaven.chunk.ChunkType;
import io.deephaven.engine.table.ColumnSource;
import io.deephaven.engine.table.impl.by.IncrementalChunkedOperatorAggregationStateManagerOpenAddressedBase;
import java.util.Arrays;

/**
 * The TypedHashDispatcher returns a pre-generated and precompiled hasher instance suitable for the provided column sources, or null if there is not a precompiled hasher suitable for the specified sources.
 */
public class TypedHashDispatcher {
    private TypedHashDispatcher() {
        // static use only
    }

    public static IncrementalChunkedOperatorAggregationStateManagerOpenAddressedBase dispatch(
            ColumnSource[] tableKeySources, ColumnSource[] originalTableKeySources, int tableSize,
            double maximumLoadFactor, double targetLoadFactor) {
        final ChunkType[] chunkTypes = Arrays.stream(tableKeySources).map(ColumnSource::getChunkType).toArray(ChunkType[]::new);;
        if (chunkTypes.length == 1) {
            return dispatchSingle(chunkTypes[0], tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
        }
        if (chunkTypes.length == 2) {
            return dispatchDouble(chunkTypes[0], chunkTypes[1], tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
        }
        return null;
    }

    private static IncrementalChunkedOperatorAggregationStateManagerOpenAddressedBase dispatchSingle(
            ChunkType chunkType, ColumnSource[] tableKeySources,
            ColumnSource[] originalTableKeySources, int tableSize, double maximumLoadFactor,
            double targetLoadFactor) {
        switch (chunkType) {
            default: throw new UnsupportedOperationException("Invalid chunk type for typed hashers: " + chunkType);
            case Char: return new IncrementalAggOpenHasherChar(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
            case Byte: return new IncrementalAggOpenHasherByte(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
            case Short: return new IncrementalAggOpenHasherShort(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
            case Int: return new IncrementalAggOpenHasherInt(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
            case Long: return new IncrementalAggOpenHasherLong(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
            case Float: return new IncrementalAggOpenHasherFloat(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
            case Double: return new IncrementalAggOpenHasherDouble(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
            case Object: return new IncrementalAggOpenHasherObject(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
        }
    }

    private static IncrementalChunkedOperatorAggregationStateManagerOpenAddressedBase dispatchDouble(
            ChunkType chunkType0, ChunkType chunkType1, ColumnSource[] tableKeySources,
            ColumnSource[] originalTableKeySources, int tableSize, double maximumLoadFactor,
            double targetLoadFactor) {
        switch (chunkType0) {
            default: throw new UnsupportedOperationException("Invalid chunk type for typed hashers: " + chunkType0);
            case Char:switch (chunkType1) {
                default: throw new UnsupportedOperationException("Invalid chunk type for typed hashers: " + chunkType1);
                case Char: return new IncrementalAggOpenHasherCharChar(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Byte: return new IncrementalAggOpenHasherCharByte(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Short: return new IncrementalAggOpenHasherCharShort(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Int: return new IncrementalAggOpenHasherCharInt(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Long: return new IncrementalAggOpenHasherCharLong(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Float: return new IncrementalAggOpenHasherCharFloat(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Double: return new IncrementalAggOpenHasherCharDouble(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Object: return new IncrementalAggOpenHasherCharObject(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
            }
            case Byte:switch (chunkType1) {
                default: throw new UnsupportedOperationException("Invalid chunk type for typed hashers: " + chunkType1);
                case Char: return new IncrementalAggOpenHasherByteChar(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Byte: return new IncrementalAggOpenHasherByteByte(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Short: return new IncrementalAggOpenHasherByteShort(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Int: return new IncrementalAggOpenHasherByteInt(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Long: return new IncrementalAggOpenHasherByteLong(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Float: return new IncrementalAggOpenHasherByteFloat(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Double: return new IncrementalAggOpenHasherByteDouble(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Object: return new IncrementalAggOpenHasherByteObject(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
            }
            case Short:switch (chunkType1) {
                default: throw new UnsupportedOperationException("Invalid chunk type for typed hashers: " + chunkType1);
                case Char: return new IncrementalAggOpenHasherShortChar(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Byte: return new IncrementalAggOpenHasherShortByte(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Short: return new IncrementalAggOpenHasherShortShort(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Int: return new IncrementalAggOpenHasherShortInt(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Long: return new IncrementalAggOpenHasherShortLong(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Float: return new IncrementalAggOpenHasherShortFloat(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Double: return new IncrementalAggOpenHasherShortDouble(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Object: return new IncrementalAggOpenHasherShortObject(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
            }
            case Int:switch (chunkType1) {
                default: throw new UnsupportedOperationException("Invalid chunk type for typed hashers: " + chunkType1);
                case Char: return new IncrementalAggOpenHasherIntChar(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Byte: return new IncrementalAggOpenHasherIntByte(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Short: return new IncrementalAggOpenHasherIntShort(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Int: return new IncrementalAggOpenHasherIntInt(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Long: return new IncrementalAggOpenHasherIntLong(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Float: return new IncrementalAggOpenHasherIntFloat(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Double: return new IncrementalAggOpenHasherIntDouble(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Object: return new IncrementalAggOpenHasherIntObject(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
            }
            case Long:switch (chunkType1) {
                default: throw new UnsupportedOperationException("Invalid chunk type for typed hashers: " + chunkType1);
                case Char: return new IncrementalAggOpenHasherLongChar(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Byte: return new IncrementalAggOpenHasherLongByte(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Short: return new IncrementalAggOpenHasherLongShort(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Int: return new IncrementalAggOpenHasherLongInt(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Long: return new IncrementalAggOpenHasherLongLong(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Float: return new IncrementalAggOpenHasherLongFloat(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Double: return new IncrementalAggOpenHasherLongDouble(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Object: return new IncrementalAggOpenHasherLongObject(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
            }
            case Float:switch (chunkType1) {
                default: throw new UnsupportedOperationException("Invalid chunk type for typed hashers: " + chunkType1);
                case Char: return new IncrementalAggOpenHasherFloatChar(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Byte: return new IncrementalAggOpenHasherFloatByte(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Short: return new IncrementalAggOpenHasherFloatShort(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Int: return new IncrementalAggOpenHasherFloatInt(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Long: return new IncrementalAggOpenHasherFloatLong(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Float: return new IncrementalAggOpenHasherFloatFloat(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Double: return new IncrementalAggOpenHasherFloatDouble(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Object: return new IncrementalAggOpenHasherFloatObject(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
            }
            case Double:switch (chunkType1) {
                default: throw new UnsupportedOperationException("Invalid chunk type for typed hashers: " + chunkType1);
                case Char: return new IncrementalAggOpenHasherDoubleChar(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Byte: return new IncrementalAggOpenHasherDoubleByte(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Short: return new IncrementalAggOpenHasherDoubleShort(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Int: return new IncrementalAggOpenHasherDoubleInt(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Long: return new IncrementalAggOpenHasherDoubleLong(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Float: return new IncrementalAggOpenHasherDoubleFloat(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Double: return new IncrementalAggOpenHasherDoubleDouble(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Object: return new IncrementalAggOpenHasherDoubleObject(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
            }
            case Object:switch (chunkType1) {
                default: throw new UnsupportedOperationException("Invalid chunk type for typed hashers: " + chunkType1);
                case Char: return new IncrementalAggOpenHasherObjectChar(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Byte: return new IncrementalAggOpenHasherObjectByte(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Short: return new IncrementalAggOpenHasherObjectShort(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Int: return new IncrementalAggOpenHasherObjectInt(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Long: return new IncrementalAggOpenHasherObjectLong(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Float: return new IncrementalAggOpenHasherObjectFloat(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Double: return new IncrementalAggOpenHasherObjectDouble(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
                case Object: return new IncrementalAggOpenHasherObjectObject(tableKeySources, originalTableKeySources, tableSize, maximumLoadFactor, targetLoadFactor);
            }
        }
    }
}
