#pragma once
#include <array>
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <boost/utility/string_view.hpp>
#include "core/protocol_base_classes.h"
#include "core/deserializer.h"
#include "core/serializer.h"
#include "lowlevel/custom/custom_shared_objects.h"
#include "lowlevel/util/deserializer_adapter.h"
#include "lowlevel/util/protocol_container_classes.h"
#include "lowlevel/util/serializer_adapter.h"
#include "utility/utility.h"
namespace deephaven {
namespace openAPI {
namespace lowlevel {
namespace remoting {
namespace generated {
struct ServerSharedHash {
  static const boost::string_view hash;
};
struct WorkerSharedHash {
  static const boost::string_view hash;
};
namespace com {
namespace illumon {
namespace iris {
namespace web {
namespace shared {
namespace data {
namespace businessCalendarDescriptor {
enum class DayOfWeek { SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY };
}  // namespace businessCalendarDescriptor
namespace columnStatistics {
enum class ColumnType { NUMERIC, COMPARABLE, NON_COMPARABLE };
}  // namespace columnStatistics
namespace filterDescriptor {
enum class FilterOperation { AND, OR, NOT, LT, GT, LTE, GTE, EQ, EQ_ICASE, NEQ, NEQ_ICASE, IN, IN_ICASE, NOT_IN, NOT_IN_ICASE, IS_NULL, INVOKE, LITERAL, REFERENCE, CONTAINS, SEARCH };
enum class ValueType { String, Number, Boolean, Datetime, Long, Other };
}  // namespace filterDescriptor
namespace joinDescriptor {
enum class JoinType { Join, Natural, AJ, ReverseAJ, ExactJoin, LeftJoin };
}  // namespace joinDescriptor
namespace rollupDefinition {
enum class LeafType { Normal, Constituent };
}  // namespace rollupDefinition
namespace tableSnapshot {
enum class SnapshotType { INITIAL_SNAPSHOT, UPDATE_COLUMN_SNAPSHOT, UPDATE_ROW_SNAPSHOT, FORCED_SNAPSHOT };
}  // namespace tableSnapshot
namespace plot {
namespace axisDescriptor {
enum class AxisFormatType { CATEGORY, NUMBER };
enum class AxisPosition { TOP, BOTTOM, LEFT, RIGHT, NONE };
enum class AxisType { X, Y, Z, SHAPE, SIZE, LABEL, COLOR };
}  // namespace axisDescriptor
namespace chartDescriptor {
enum class ChartType { XY, PIE, OHLC, CATEGORY, XYZ, CATEGORY_3D };
}  // namespace chartDescriptor
enum class SeriesPlotStyle { BAR, STACKED_BAR, LINE, AREA, STACKED_AREA, PIE, HISTOGRAM, OHLC, SCATTER, STEP, ERROR_BAR };
enum class SourceType { X, Y, Z, X_LOW, X_HIGH, Y_LOW, Y_HIGH, TIME, OPEN, HIGH, LOW, CLOSE, SHAPE, SIZE, LABEL, COLOR };
}  // namespace plot
namespace treetable {
namespace treeTableRequest {
enum class TreeRequestOperation { Expand, Contract, FilterChanged, SortChanged, Close };
}  // namespace treeTableRequest
}  // namespace treetable
namespace workspace {
enum class ItemStatus { Active, Trashed, Deleted };
}  // namespace workspace
}  // namespace data
namespace ide {
enum class ConsoleSessionType { Python, Groovy };
}  // namespace ide
namespace batch {
class BatchTableRequest;
namespace batchTableRequest {
class SerializedTableOps;
}  // namespace batchTableRequest
class BatchTableResponse;
namespace aggregates {
class AggregateDescriptor;
class ComboAggregateDescriptor;
class PercentileDescriptor;
}  // namespace aggregates
}  // namespace batch
namespace cmd {
class ConnectionSuccess;
class ServerReplyHandle;
class RequestId;
}  // namespace cmd
namespace data {
class BusinessCalendarDescriptor;
class BusinessPeriod;
class Catalog;
namespace catalog {
class Table;
}  // namespace catalog
class ChallengeResponseData;
class ColumnDefinition;
class ColumnHolder;
class ColumnStatistics;
class ColumnValue;
class ConnectToken;
class CustomColumnDescriptor;
class DeltaUpdates;
namespace deltaUpdates {
class ColumnAdditions;
class ColumnModifications;
}  // namespace deltaUpdates
class FilterDescriptor;
class HandleMapping;
class HeadOrTailDescriptor;
class Holiday;
class InitialTableDefinition;
class InputTableDefinition;
class JoinDescriptor;
class LocalDate;
class LocalTime;
class LogItem;
class QueryConfig;
class QueryConstants;
class QuerySelectionPermissions;
class Range;
class RangeSet;
class RefreshToken;
class RollupDefinition;
class RowValues;
class ServerConfigValues;
class ShiftedRange;
class SortDescriptor;
class TableDefinition;
class TableHandle;
class TableMapDeclaration;
class TableMapHandle;
class TableSnapshot;
class TableSubscriptionRequest;
class TableValues;
class UserInfo;
namespace columns {
class ColumnData;
class BigDecimalArrayColumnData;
class BigIntegerArrayColumnData;
class ByteArrayColumnData;
class CharArrayColumnData;
class DoubleArrayColumnData;
class FloatArrayColumnData;
class IntArrayColumnData;
class LocalDateArrayColumnData;
class LocalTimeArrayColumnData;
class LongArrayColumnData;
class ShortArrayColumnData;
class StringArrayArrayColumnData;
class StringArrayColumnData;
}  // namespace columns
namespace plot {
class AxisDescriptor;
class ChartDescriptor;
class FigureDescriptor;
class MultiSeriesDescriptor;
class MultiSeriesSourceDescriptor;
class OneClickDescriptor;
class SeriesDescriptor;
class SourceDescriptor;
class ThemeDescriptor;
}  // namespace plot
namespace treetable {
class Key;
class TableDetails;
class TreeTableRequest;
class TreeTableResult;
}  // namespace treetable
namespace workspace {
class WorkspaceData;
}  // namespace workspace
}  // namespace data
namespace ide {
class CommandResult;
class ConsoleAddress;
class ConsoleConfig;
class ConsoleConnectionResult;
class ConsoleServerAddress;
class ExecutionHandle;
class ScriptHandle;
class VariableChanges;
class VariableDefinition;
namespace lsp {
class CompletionContext;
class CompletionItem;
class TextDocumentPositionParams;
class CompletionParams;
class DidChangeTextDocumentParams;
class DidCloseTextDocumentParams;
class DidOpenTextDocumentParams;
class DocumentRange;
class Position;
class TextDocumentContentChangeEvent;
class TextDocumentIdentifier;
class TextDocumentItem;
class TextEdit;
class VersionedTextDocumentIdentifier;
}  // namespace lsp
}  // namespace ide
namespace metrics {
class MetricsLog;
}  // namespace metrics
namespace requests {
class AddToInputTableRequest;
class AddToInputTableResponse;
}  // namespace requests
}  // namespace shared
}  // namespace web
}  // namespace iris
}  // namespace illumon
}  // namespace com
namespace java {
namespace lang {
class Boolean;
class Byte;
class Character;
class Double;
class Float;
class Integer;
class Long;
class Number;
class Short;
class String;
class Void;
}  // namespace lang
namespace math {
class BigDecimal;
class BigInteger;
}  // namespace math
namespace util {
class BitSet;
}  // namespace util
}  // namespace java
}  // namespace generated
template<>
struct AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::businessCalendarDescriptor::DayOfWeek> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columnStatistics::ColumnType> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::filterDescriptor::FilterOperation> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::filterDescriptor::ValueType> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::joinDescriptor::JoinType> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::rollupDefinition::LeafType> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::tableSnapshot::SnapshotType> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::axisDescriptor::AxisFormatType> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::axisDescriptor::AxisPosition> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::axisDescriptor::AxisType> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::chartDescriptor::ChartType> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SeriesPlotStyle> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SourceType> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::treeTableRequest::TreeRequestOperation> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::workspace::ItemStatus> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ConsoleSessionType> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<int8_t>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<char16_t>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::batchTableRequest::SerializedTableOps>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::AggregateDescriptor>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::businessCalendarDescriptor::DayOfWeek>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::BusinessPeriod>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::catalog::Table>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnDefinition>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnHolder>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnValue>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::CustomColumnDescriptor>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::deltaUpdates::ColumnAdditions>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::deltaUpdates::ColumnModifications>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::FilterDescriptor>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Holiday>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LocalDate>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LocalTime>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Range>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RowValues>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ShiftedRange>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::SortDescriptor>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableSubscriptionRequest>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::BigDecimalArrayColumnData>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::BigIntegerArrayColumnData>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ByteArrayColumnData>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::CharArrayColumnData>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::DoubleArrayColumnData>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::FloatArrayColumnData>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::IntArrayColumnData>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::LocalDateArrayColumnData>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::LocalTimeArrayColumnData>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::LongArrayColumnData>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ShortArrayColumnData>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::StringArrayArrayColumnData>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::StringArrayColumnData>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::AxisDescriptor>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::ChartDescriptor>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::MultiSeriesDescriptor>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::MultiSeriesSourceDescriptor>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SeriesDescriptor>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SourceDescriptor>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::Key>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::TableDetails>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::treeTableRequest::TreeRequestOperation>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ConsoleServerAddress>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::VariableDefinition>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::CompletionItem>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentContentChangeEvent>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextEdit>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::metrics::MetricsLog>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<double>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<float>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<int32_t>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<std::vector<int32_t>>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Double>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<std::string>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<std::vector<std::shared_ptr<std::string>>>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::math::BigDecimal>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::math::BigInteger>>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<int64_t>> {
  static const boost::string_view typeName;
};
template<>
struct AggregateTypeName<std::vector<int16_t>> {
  static const boost::string_view typeName;
};
namespace generated {
namespace com {
namespace illumon {
namespace iris {
namespace web {
namespace shared {
namespace cmd {
class ServerReplyHandleVisitor {
public:
  virtual ~ServerReplyHandleVisitor() = default;
  virtual void visit(const RequestId *self) = 0;
  virtual void visit(const ServerReplyHandle *self) = 0;
};
}  // namespace cmd
namespace data {
namespace columns {
class ColumnDataVisitor {
public:
  virtual ~ColumnDataVisitor() = default;
  virtual void visit(const BigDecimalArrayColumnData *self) = 0;
  virtual void visit(const BigIntegerArrayColumnData *self) = 0;
  virtual void visit(const ByteArrayColumnData *self) = 0;
  virtual void visit(const CharArrayColumnData *self) = 0;
  virtual void visit(const ColumnData *self) = 0;
  virtual void visit(const DoubleArrayColumnData *self) = 0;
  virtual void visit(const FloatArrayColumnData *self) = 0;
  virtual void visit(const IntArrayColumnData *self) = 0;
  virtual void visit(const LocalDateArrayColumnData *self) = 0;
  virtual void visit(const LocalTimeArrayColumnData *self) = 0;
  virtual void visit(const LongArrayColumnData *self) = 0;
  virtual void visit(const ShortArrayColumnData *self) = 0;
  virtual void visit(const StringArrayArrayColumnData *self) = 0;
  virtual void visit(const StringArrayColumnData *self) = 0;
};
}  // namespace columns
}  // namespace data
namespace ide {
namespace lsp {
class TextDocumentPositionParamsVisitor {
public:
  virtual ~TextDocumentPositionParamsVisitor() = default;
  virtual void visit(const CompletionParams *self) = 0;
  virtual void visit(const TextDocumentPositionParams *self) = 0;
};
class TextDocumentIdentifierVisitor {
public:
  virtual ~TextDocumentIdentifierVisitor() = default;
  virtual void visit(const TextDocumentIdentifier *self) = 0;
  virtual void visit(const VersionedTextDocumentIdentifier *self) = 0;
};
}  // namespace lsp
}  // namespace ide
namespace batch {
class BatchTableRequest final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<BatchTableRequest> create(std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::batchTableRequest::SerializedTableOps>>> ops);
  BatchTableRequest(Private, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::batchTableRequest::SerializedTableOps>>> ops);
  BatchTableRequest(const BatchTableRequest &other) = delete;
  BatchTableRequest &operator=(const BatchTableRequest &other) = delete;
  ~BatchTableRequest() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<BatchTableRequest> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<BatchTableRequest>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::batchTableRequest::SerializedTableOps>>> &ops() const { return ops_; }
private:
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::batchTableRequest::SerializedTableOps>>> ops_;
};
namespace batchTableRequest {
class SerializedTableOps final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<SerializedTableOps> create(std::shared_ptr<std::vector<std::shared_ptr<std::string>>> dropColumns, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> viewColumns, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::HandleMapping> handles, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::SortDescriptor>>> sorts, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> conditions, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::FilterDescriptor>>> filters, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::CustomColumnDescriptor>>> customColumns, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::HeadOrTailDescriptor> headOrTail, bool isFlat, int32_t updateIntervalMs);
  SerializedTableOps(Private, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> dropColumns, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> viewColumns, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::HandleMapping> handles, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::SortDescriptor>>> sorts, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> conditions, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::FilterDescriptor>>> filters, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::CustomColumnDescriptor>>> customColumns, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::HeadOrTailDescriptor> headOrTail, bool isFlat, int32_t updateIntervalMs);
  SerializedTableOps(const SerializedTableOps &other) = delete;
  SerializedTableOps &operator=(const SerializedTableOps &other) = delete;
  ~SerializedTableOps() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<SerializedTableOps> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<SerializedTableOps>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &dropColumns() const { return dropColumns_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &viewColumns() const { return viewColumns_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::HandleMapping> &handles() const { return handles_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::SortDescriptor>>> &sorts() const { return sorts_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &conditions() const { return conditions_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::FilterDescriptor>>> &filters() const { return filters_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::CustomColumnDescriptor>>> &customColumns() const { return customColumns_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::HeadOrTailDescriptor> &headOrTail() const { return headOrTail_; }
  bool isFlat() const { return isFlat_; }
  int32_t updateIntervalMs() const { return updateIntervalMs_; }
private:
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> dropColumns_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> viewColumns_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::HandleMapping> handles_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::SortDescriptor>>> sorts_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> conditions_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::FilterDescriptor>>> filters_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::CustomColumnDescriptor>>> customColumns_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::HeadOrTailDescriptor> headOrTail_;
  bool isFlat_;
  int32_t updateIntervalMs_;
};
}  // namespace batchTableRequest
class BatchTableResponse final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<BatchTableResponse> create(std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> success, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> failedTableHandles, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> failureMessages);
  BatchTableResponse(Private, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> success, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> failedTableHandles, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> failureMessages);
  BatchTableResponse(const BatchTableResponse &other) = delete;
  BatchTableResponse &operator=(const BatchTableResponse &other) = delete;
  ~BatchTableResponse() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<BatchTableResponse> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<BatchTableResponse>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> &success() const { return success_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> &failedTableHandles() const { return failedTableHandles_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &failureMessages() const { return failureMessages_; }
private:
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> success_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> failedTableHandles_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> failureMessages_;
};
namespace aggregates {
class AggregateDescriptor final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<AggregateDescriptor> create(std::shared_ptr<std::string> aggregateType, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> matchPairs, std::shared_ptr<std::string> columnName, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::PercentileDescriptor> percentile);
  AggregateDescriptor(Private, std::shared_ptr<std::string> aggregateType, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> matchPairs, std::shared_ptr<std::string> columnName, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::PercentileDescriptor> percentile);
  AggregateDescriptor(const AggregateDescriptor &other) = delete;
  AggregateDescriptor &operator=(const AggregateDescriptor &other) = delete;
  ~AggregateDescriptor() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<AggregateDescriptor> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<AggregateDescriptor>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::string> &aggregateType() const { return aggregateType_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &matchPairs() const { return matchPairs_; }
  const std::shared_ptr<std::string> &columnName() const { return columnName_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::PercentileDescriptor> &percentile() const { return percentile_; }
private:
  std::shared_ptr<std::string> aggregateType_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> matchPairs_;
  std::shared_ptr<std::string> columnName_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::PercentileDescriptor> percentile_;
};
class ComboAggregateDescriptor final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<ComboAggregateDescriptor> create(std::shared_ptr<std::string> aggregateStrategy, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::AggregateDescriptor>>> aggregates, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> groupByColumns, bool forceCombo);
  ComboAggregateDescriptor(Private, std::shared_ptr<std::string> aggregateStrategy, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::AggregateDescriptor>>> aggregates, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> groupByColumns, bool forceCombo);
  ComboAggregateDescriptor(const ComboAggregateDescriptor &other) = delete;
  ComboAggregateDescriptor &operator=(const ComboAggregateDescriptor &other) = delete;
  ~ComboAggregateDescriptor() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<ComboAggregateDescriptor> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<ComboAggregateDescriptor>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::string> &aggregateStrategy() const { return aggregateStrategy_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::AggregateDescriptor>>> &aggregates() const { return aggregates_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &groupByColumns() const { return groupByColumns_; }
  bool forceCombo() const { return forceCombo_; }
private:
  std::shared_ptr<std::string> aggregateStrategy_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::AggregateDescriptor>>> aggregates_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> groupByColumns_;
  bool forceCombo_;
};
class PercentileDescriptor final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<PercentileDescriptor> create(double percentile, bool avgMedian);
  PercentileDescriptor(Private, double percentile, bool avgMedian);
  PercentileDescriptor(const PercentileDescriptor &other) = delete;
  PercentileDescriptor &operator=(const PercentileDescriptor &other) = delete;
  ~PercentileDescriptor() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<PercentileDescriptor> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<PercentileDescriptor>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  double percentile() const { return percentile_; }
  bool avgMedian() const { return avgMedian_; }
private:
  double percentile_;
  bool avgMedian_;
};
}  // namespace aggregates
}  // namespace batch
namespace cmd {
class ConnectionSuccess final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<ConnectionSuccess> create(std::shared_ptr<std::string> token, int32_t connectionId);
  ConnectionSuccess(Private, std::shared_ptr<std::string> token, int32_t connectionId);
  ConnectionSuccess(const ConnectionSuccess &other) = delete;
  ConnectionSuccess &operator=(const ConnectionSuccess &other) = delete;
  ~ConnectionSuccess() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<ConnectionSuccess> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<ConnectionSuccess>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::string> &token() const { return token_; }
  int32_t connectionId() const { return connectionId_; }
private:
  std::shared_ptr<std::string> token_;
  int32_t connectionId_;
};
class ServerReplyHandle : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<ServerReplyHandle> create();
  explicit ServerReplyHandle(Private);
  ServerReplyHandle(const ServerReplyHandle &other) = delete;
  ServerReplyHandle &operator=(const ServerReplyHandle &other) = delete;
  ~ServerReplyHandle() override;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const override;
  static std::shared_ptr<ServerReplyHandle> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<ServerReplyHandle>(typeName, nullptr);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  virtual void acceptVisitor(ServerReplyHandleVisitor *visitor) const {
    visitor->visit(this);
  }
private:
};
class RequestId final : public deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::ServerReplyHandle {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<RequestId> create(int32_t clientId);
  RequestId(Private, int32_t clientId);
  RequestId(const RequestId &other) = delete;
  RequestId &operator=(const RequestId &other) = delete;
  ~RequestId() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<RequestId> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<RequestId>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(ServerReplyHandleVisitor *visitor) const final {
    visitor->visit(this);
  }
  int32_t clientId() const { return clientId_; }
private:
  int32_t clientId_;
};
}  // namespace cmd
namespace data {
class BusinessCalendarDescriptor final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<BusinessCalendarDescriptor> create(std::shared_ptr<std::string> name, std::shared_ptr<std::string> timeZone, std::shared_ptr<std::vector<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::businessCalendarDescriptor::DayOfWeek>> businessDays, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::BusinessPeriod>>> businessPeriods, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Holiday>>> holidays);
  BusinessCalendarDescriptor(Private, std::shared_ptr<std::string> name, std::shared_ptr<std::string> timeZone, std::shared_ptr<std::vector<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::businessCalendarDescriptor::DayOfWeek>> businessDays, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::BusinessPeriod>>> businessPeriods, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Holiday>>> holidays);
  BusinessCalendarDescriptor(const BusinessCalendarDescriptor &other) = delete;
  BusinessCalendarDescriptor &operator=(const BusinessCalendarDescriptor &other) = delete;
  ~BusinessCalendarDescriptor() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<BusinessCalendarDescriptor> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<BusinessCalendarDescriptor>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::string> &name() const { return name_; }
  const std::shared_ptr<std::string> &timeZone() const { return timeZone_; }
  const std::shared_ptr<std::vector<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::businessCalendarDescriptor::DayOfWeek>> &businessDays() const { return businessDays_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::BusinessPeriod>>> &businessPeriods() const { return businessPeriods_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Holiday>>> &holidays() const { return holidays_; }
private:
  std::shared_ptr<std::string> name_;
  std::shared_ptr<std::string> timeZone_;
  std::shared_ptr<std::vector<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::businessCalendarDescriptor::DayOfWeek>> businessDays_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::BusinessPeriod>>> businessPeriods_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Holiday>>> holidays_;
};
class BusinessPeriod final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<BusinessPeriod> create(std::shared_ptr<std::string> open, std::shared_ptr<std::string> close);
  BusinessPeriod(Private, std::shared_ptr<std::string> open, std::shared_ptr<std::string> close);
  BusinessPeriod(const BusinessPeriod &other) = delete;
  BusinessPeriod &operator=(const BusinessPeriod &other) = delete;
  ~BusinessPeriod() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<BusinessPeriod> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<BusinessPeriod>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::string> &open() const { return open_; }
  const std::shared_ptr<std::string> &close() const { return close_; }
private:
  std::shared_ptr<std::string> open_;
  std::shared_ptr<std::string> close_;
};
class Catalog final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<Catalog> create(std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::catalog::Table>>> tables);
  Catalog(Private, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::catalog::Table>>> tables);
  Catalog(const Catalog &other) = delete;
  Catalog &operator=(const Catalog &other) = delete;
  ~Catalog() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<Catalog> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<Catalog>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::catalog::Table>>> &tables() const { return tables_; }
private:
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::catalog::Table>>> tables_;
};
namespace catalog {
class Table final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<Table> create(std::shared_ptr<std::string> namespaceSet, std::shared_ptr<std::string> nameSpace, std::shared_ptr<std::string> tableName);
  Table(Private, std::shared_ptr<std::string> namespaceSet, std::shared_ptr<std::string> nameSpace, std::shared_ptr<std::string> tableName);
  Table(const Table &other) = delete;
  Table &operator=(const Table &other) = delete;
  ~Table() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<Table> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<Table>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::string> &namespaceSet() const { return namespaceSet_; }
  const std::shared_ptr<std::string> &nameSpace() const { return nameSpace_; }
  const std::shared_ptr<std::string> &tableName() const { return tableName_; }
private:
  std::shared_ptr<std::string> namespaceSet_;
  std::shared_ptr<std::string> nameSpace_;
  std::shared_ptr<std::string> tableName_;
};
}  // namespace catalog
class ChallengeResponseData final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<ChallengeResponseData> create(std::shared_ptr<std::vector<int8_t>> nonce, std::shared_ptr<std::string> algorithm);
  ChallengeResponseData(Private, std::shared_ptr<std::vector<int8_t>> nonce, std::shared_ptr<std::string> algorithm);
  ChallengeResponseData(const ChallengeResponseData &other) = delete;
  ChallengeResponseData &operator=(const ChallengeResponseData &other) = delete;
  ~ChallengeResponseData() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<ChallengeResponseData> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<ChallengeResponseData>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::vector<int8_t>> &nonce() const { return nonce_; }
  const std::shared_ptr<std::string> &algorithm() const { return algorithm_; }
private:
  std::shared_ptr<std::vector<int8_t>> nonce_;
  std::shared_ptr<std::string> algorithm_;
};
class ColumnDefinition final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<ColumnDefinition> create(int32_t columnIndex, std::shared_ptr<std::string> name, std::shared_ptr<std::string> type, bool isStyleColumn, bool isFormatColumn, bool isNumberFormatColumn, bool isPartitionColumn, bool isRollupHierarchicalColumn, bool forRow, std::shared_ptr<std::string> forColumn, std::shared_ptr<std::string> description);
  ColumnDefinition(Private, int32_t columnIndex, std::shared_ptr<std::string> name, std::shared_ptr<std::string> type, bool isStyleColumn, bool isFormatColumn, bool isNumberFormatColumn, bool isPartitionColumn, bool isRollupHierarchicalColumn, bool forRow, std::shared_ptr<std::string> forColumn, std::shared_ptr<std::string> description);
  ColumnDefinition(const ColumnDefinition &other) = delete;
  ColumnDefinition &operator=(const ColumnDefinition &other) = delete;
  ~ColumnDefinition() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<ColumnDefinition> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<ColumnDefinition>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  int32_t columnIndex() const { return columnIndex_; }
  const std::shared_ptr<std::string> &name() const { return name_; }
  const std::shared_ptr<std::string> &type() const { return type_; }
  bool isStyleColumn() const { return isStyleColumn_; }
  bool isFormatColumn() const { return isFormatColumn_; }
  bool isNumberFormatColumn() const { return isNumberFormatColumn_; }
  bool isPartitionColumn() const { return isPartitionColumn_; }
  bool isRollupHierarchicalColumn() const { return isRollupHierarchicalColumn_; }
  bool forRow() const { return forRow_; }
  const std::shared_ptr<std::string> &forColumn() const { return forColumn_; }
  const std::shared_ptr<std::string> &description() const { return description_; }
private:
  int32_t columnIndex_;
  std::shared_ptr<std::string> name_;
  std::shared_ptr<std::string> type_;
  bool isStyleColumn_;
  bool isFormatColumn_;
  bool isNumberFormatColumn_;
  bool isPartitionColumn_;
  bool isRollupHierarchicalColumn_;
  bool forRow_;
  std::shared_ptr<std::string> forColumn_;
  std::shared_ptr<std::string> description_;
};
class ColumnHolder final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<ColumnHolder> create(std::shared_ptr<std::string> name, std::shared_ptr<std::string> type, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData> columnData, bool grouped);
  ColumnHolder(Private, std::shared_ptr<std::string> name, std::shared_ptr<std::string> type, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData> columnData, bool grouped);
  ColumnHolder(const ColumnHolder &other) = delete;
  ColumnHolder &operator=(const ColumnHolder &other) = delete;
  ~ColumnHolder() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<ColumnHolder> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<ColumnHolder>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::string> &name() const { return name_; }
  const std::shared_ptr<std::string> &type() const { return type_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData> &columnData() const { return columnData_; }
  bool grouped() const { return grouped_; }
private:
  std::shared_ptr<std::string> name_;
  std::shared_ptr<std::string> type_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData> columnData_;
  bool grouped_;
};
class ColumnStatistics final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<ColumnStatistics> create(deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columnStatistics::ColumnType type, int64_t count, int32_t numUnique, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> uniqueKeys, std::shared_ptr<std::vector<int64_t>> uniqueValues, double sum, double absSum, double min, double max, double absMin, double absMax);
  ColumnStatistics(Private, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columnStatistics::ColumnType type, int64_t count, int32_t numUnique, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> uniqueKeys, std::shared_ptr<std::vector<int64_t>> uniqueValues, double sum, double absSum, double min, double max, double absMin, double absMax);
  ColumnStatistics(const ColumnStatistics &other) = delete;
  ColumnStatistics &operator=(const ColumnStatistics &other) = delete;
  ~ColumnStatistics() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<ColumnStatistics> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<ColumnStatistics>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columnStatistics::ColumnType type() const { return type_; }
  int64_t count() const { return count_; }
  int32_t numUnique() const { return numUnique_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &uniqueKeys() const { return uniqueKeys_; }
  const std::shared_ptr<std::vector<int64_t>> &uniqueValues() const { return uniqueValues_; }
  double sum() const { return sum_; }
  double absSum() const { return absSum_; }
  double min() const { return min_; }
  double max() const { return max_; }
  double absMin() const { return absMin_; }
  double absMax() const { return absMax_; }
private:
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columnStatistics::ColumnType type_;
  int64_t count_;
  int32_t numUnique_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> uniqueKeys_;
  std::shared_ptr<std::vector<int64_t>> uniqueValues_;
  double sum_;
  double absSum_;
  double min_;
  double max_;
  double absMin_;
  double absMax_;
};
class ColumnValue final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<ColumnValue> create(int32_t columnId, std::shared_ptr<std::string> value);
  ColumnValue(Private, int32_t columnId, std::shared_ptr<std::string> value);
  ColumnValue(const ColumnValue &other) = delete;
  ColumnValue &operator=(const ColumnValue &other) = delete;
  ~ColumnValue() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<ColumnValue> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<ColumnValue>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  int32_t columnId() const { return columnId_; }
  const std::shared_ptr<std::string> &value() const { return value_; }
private:
  int32_t columnId_;
  std::shared_ptr<std::string> value_;
};
class ConnectToken final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<ConnectToken> create(std::shared_ptr<std::vector<int8_t>> bytes);
  ConnectToken(Private, std::shared_ptr<std::vector<int8_t>> bytes);
  ConnectToken(const ConnectToken &other) = delete;
  ConnectToken &operator=(const ConnectToken &other) = delete;
  ~ConnectToken() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<ConnectToken> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<ConnectToken>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::vector<int8_t>> &bytes() const { return bytes_; }
private:
  std::shared_ptr<std::vector<int8_t>> bytes_;
};
class CustomColumnDescriptor final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<CustomColumnDescriptor> create(std::shared_ptr<std::string> expression);
  CustomColumnDescriptor(Private, std::shared_ptr<std::string> expression);
  CustomColumnDescriptor(const CustomColumnDescriptor &other) = delete;
  CustomColumnDescriptor &operator=(const CustomColumnDescriptor &other) = delete;
  ~CustomColumnDescriptor() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<CustomColumnDescriptor> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<CustomColumnDescriptor>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::string> &expression() const { return expression_; }
private:
  std::shared_ptr<std::string> expression_;
};
class DeltaUpdates final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<DeltaUpdates> create(int64_t deltaSequence, int64_t firstStep, int64_t lastStep, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> added, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> removed, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ShiftedRange>>> shiftedRanges, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> includedAdditions, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::deltaUpdates::ColumnAdditions>>> serializedAdditions, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::deltaUpdates::ColumnModifications>>> serializedModifications);
  DeltaUpdates(Private, int64_t deltaSequence, int64_t firstStep, int64_t lastStep, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> added, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> removed, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ShiftedRange>>> shiftedRanges, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> includedAdditions, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::deltaUpdates::ColumnAdditions>>> serializedAdditions, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::deltaUpdates::ColumnModifications>>> serializedModifications);
  DeltaUpdates(const DeltaUpdates &other) = delete;
  DeltaUpdates &operator=(const DeltaUpdates &other) = delete;
  ~DeltaUpdates() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<DeltaUpdates> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<DeltaUpdates>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  int64_t deltaSequence() const { return deltaSequence_; }
  int64_t firstStep() const { return firstStep_; }
  int64_t lastStep() const { return lastStep_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> &added() const { return added_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> &removed() const { return removed_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ShiftedRange>>> &shiftedRanges() const { return shiftedRanges_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> &includedAdditions() const { return includedAdditions_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::deltaUpdates::ColumnAdditions>>> &serializedAdditions() const { return serializedAdditions_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::deltaUpdates::ColumnModifications>>> &serializedModifications() const { return serializedModifications_; }
private:
  int64_t deltaSequence_;
  int64_t firstStep_;
  int64_t lastStep_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> added_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> removed_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ShiftedRange>>> shiftedRanges_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> includedAdditions_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::deltaUpdates::ColumnAdditions>>> serializedAdditions_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::deltaUpdates::ColumnModifications>>> serializedModifications_;
};
namespace deltaUpdates {
class ColumnAdditions final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<ColumnAdditions> create(int32_t columnIndex, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData> values);
  ColumnAdditions(Private, int32_t columnIndex, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData> values);
  ColumnAdditions(const ColumnAdditions &other) = delete;
  ColumnAdditions &operator=(const ColumnAdditions &other) = delete;
  ~ColumnAdditions() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<ColumnAdditions> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<ColumnAdditions>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  int32_t columnIndex() const { return columnIndex_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData> &values() const { return values_; }
private:
  int32_t columnIndex_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData> values_;
};
class ColumnModifications final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<ColumnModifications> create(int32_t columnIndex, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> rowsIncluded, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> rowsModified, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData> values);
  ColumnModifications(Private, int32_t columnIndex, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> rowsIncluded, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> rowsModified, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData> values);
  ColumnModifications(const ColumnModifications &other) = delete;
  ColumnModifications &operator=(const ColumnModifications &other) = delete;
  ~ColumnModifications() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<ColumnModifications> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<ColumnModifications>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  int32_t columnIndex() const { return columnIndex_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> &rowsIncluded() const { return rowsIncluded_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> &rowsModified() const { return rowsModified_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData> &values() const { return values_; }
private:
  int32_t columnIndex_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> rowsIncluded_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> rowsModified_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData> values_;
};
}  // namespace deltaUpdates
class FilterDescriptor final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<FilterDescriptor> create(deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::filterDescriptor::FilterOperation operation, std::shared_ptr<std::string> value, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::filterDescriptor::ValueType type, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::FilterDescriptor>>> children);
  FilterDescriptor(Private, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::filterDescriptor::FilterOperation operation, std::shared_ptr<std::string> value, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::filterDescriptor::ValueType type, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::FilterDescriptor>>> children);
  FilterDescriptor(const FilterDescriptor &other) = delete;
  FilterDescriptor &operator=(const FilterDescriptor &other) = delete;
  ~FilterDescriptor() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<FilterDescriptor> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<FilterDescriptor>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::filterDescriptor::FilterOperation operation() const { return operation_; }
  const std::shared_ptr<std::string> &value() const { return value_; }
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::filterDescriptor::ValueType type() const { return type_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::FilterDescriptor>>> &children() const { return children_; }
private:
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::filterDescriptor::FilterOperation operation_;
  std::shared_ptr<std::string> value_;
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::filterDescriptor::ValueType type_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::FilterDescriptor>>> children_;
};
class HandleMapping final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<HandleMapping> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> source, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> newId);
  HandleMapping(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> source, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> newId);
  HandleMapping(const HandleMapping &other) = delete;
  HandleMapping &operator=(const HandleMapping &other) = delete;
  ~HandleMapping() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<HandleMapping> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<HandleMapping>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &source() const { return source_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &newId() const { return newId_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> source_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> newId_;
};
class HeadOrTailDescriptor final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<HeadOrTailDescriptor> create(bool head, int64_t rows);
  HeadOrTailDescriptor(Private, bool head, int64_t rows);
  HeadOrTailDescriptor(const HeadOrTailDescriptor &other) = delete;
  HeadOrTailDescriptor &operator=(const HeadOrTailDescriptor &other) = delete;
  ~HeadOrTailDescriptor() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<HeadOrTailDescriptor> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<HeadOrTailDescriptor>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  bool head() const { return head_; }
  int64_t rows() const { return rows_; }
private:
  bool head_;
  int64_t rows_;
};
class Holiday final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<Holiday> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LocalDate> date, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::BusinessPeriod>>> businessPeriods);
  Holiday(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LocalDate> date, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::BusinessPeriod>>> businessPeriods);
  Holiday(const Holiday &other) = delete;
  Holiday &operator=(const Holiday &other) = delete;
  ~Holiday() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<Holiday> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<Holiday>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LocalDate> &date() const { return date_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::BusinessPeriod>>> &businessPeriods() const { return businessPeriods_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LocalDate> date_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::BusinessPeriod>>> businessPeriods_;
};
class InitialTableDefinition final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<InitialTableDefinition> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableDefinition> definition, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> id, int64_t size, bool inputTable, std::shared_ptr<std::string> totalsTableConfig, bool isFlat, bool isPreemptive, std::shared_ptr<std::string> treeHierarchicalColumnName, std::shared_ptr<std::string> description, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RollupDefinition> rollupDefinition, std::shared_ptr<std::string> pluginName);
  InitialTableDefinition(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableDefinition> definition, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> id, int64_t size, bool inputTable, std::shared_ptr<std::string> totalsTableConfig, bool isFlat, bool isPreemptive, std::shared_ptr<std::string> treeHierarchicalColumnName, std::shared_ptr<std::string> description, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RollupDefinition> rollupDefinition, std::shared_ptr<std::string> pluginName);
  InitialTableDefinition(const InitialTableDefinition &other) = delete;
  InitialTableDefinition &operator=(const InitialTableDefinition &other) = delete;
  ~InitialTableDefinition() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<InitialTableDefinition> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<InitialTableDefinition>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableDefinition> &definition() const { return definition_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &id() const { return id_; }
  int64_t size() const { return size_; }
  bool inputTable() const { return inputTable_; }
  const std::shared_ptr<std::string> &totalsTableConfig() const { return totalsTableConfig_; }
  bool isFlat() const { return isFlat_; }
  bool isPreemptive() const { return isPreemptive_; }
  const std::shared_ptr<std::string> &treeHierarchicalColumnName() const { return treeHierarchicalColumnName_; }
  const std::shared_ptr<std::string> &description() const { return description_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RollupDefinition> &rollupDefinition() const { return rollupDefinition_; }
  const std::shared_ptr<std::string> &pluginName() const { return pluginName_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableDefinition> definition_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> id_;
  int64_t size_;
  bool inputTable_;
  std::shared_ptr<std::string> totalsTableConfig_;
  bool isFlat_;
  bool isPreemptive_;
  std::shared_ptr<std::string> treeHierarchicalColumnName_;
  std::shared_ptr<std::string> description_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RollupDefinition> rollupDefinition_;
  std::shared_ptr<std::string> pluginName_;
};
class InputTableDefinition final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<InputTableDefinition> create(std::shared_ptr<std::vector<std::shared_ptr<std::string>>> keys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> values);
  InputTableDefinition(Private, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> keys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> values);
  InputTableDefinition(const InputTableDefinition &other) = delete;
  InputTableDefinition &operator=(const InputTableDefinition &other) = delete;
  ~InputTableDefinition() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<InputTableDefinition> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<InputTableDefinition>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &keys() const { return keys_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &values() const { return values_; }
private:
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> keys_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> values_;
};
class JoinDescriptor final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<JoinDescriptor> create(deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::joinDescriptor::JoinType joinType, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> leftTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> rightTableHandle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnsToMatch, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnsToAdd);
  JoinDescriptor(Private, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::joinDescriptor::JoinType joinType, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> leftTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> rightTableHandle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnsToMatch, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnsToAdd);
  JoinDescriptor(const JoinDescriptor &other) = delete;
  JoinDescriptor &operator=(const JoinDescriptor &other) = delete;
  ~JoinDescriptor() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<JoinDescriptor> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<JoinDescriptor>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::joinDescriptor::JoinType joinType() const { return joinType_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &leftTableHandle() const { return leftTableHandle_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &rightTableHandle() const { return rightTableHandle_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &columnsToMatch() const { return columnsToMatch_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &columnsToAdd() const { return columnsToAdd_; }
private:
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::joinDescriptor::JoinType joinType_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> leftTableHandle_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> rightTableHandle_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnsToMatch_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnsToAdd_;
};
class LocalDate final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<LocalDate> create(int32_t year, int8_t monthValue, int8_t dayOfMonth);
  LocalDate(Private, int32_t year, int8_t monthValue, int8_t dayOfMonth);
  LocalDate(const LocalDate &other) = delete;
  LocalDate &operator=(const LocalDate &other) = delete;
  ~LocalDate() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<LocalDate> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<LocalDate>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  int32_t year() const { return year_; }
  int8_t monthValue() const { return monthValue_; }
  int8_t dayOfMonth() const { return dayOfMonth_; }
private:
  int32_t year_;
  int8_t monthValue_;
  int8_t dayOfMonth_;
};
class LocalTime final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<LocalTime> create(int8_t hour, int8_t minute, int8_t second, int32_t nano);
  LocalTime(Private, int8_t hour, int8_t minute, int8_t second, int32_t nano);
  LocalTime(const LocalTime &other) = delete;
  LocalTime &operator=(const LocalTime &other) = delete;
  ~LocalTime() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<LocalTime> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<LocalTime>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  int8_t hour() const { return hour_; }
  int8_t minute() const { return minute_; }
  int8_t second() const { return second_; }
  int32_t nano() const { return nano_; }
private:
  int8_t hour_;
  int8_t minute_;
  int8_t second_;
  int32_t nano_;
};
class LogItem final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<LogItem> create(double micros, std::shared_ptr<std::string> logLevel, std::shared_ptr<std::string> message);
  LogItem(Private, double micros, std::shared_ptr<std::string> logLevel, std::shared_ptr<std::string> message);
  LogItem(const LogItem &other) = delete;
  LogItem &operator=(const LogItem &other) = delete;
  ~LogItem() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<LogItem> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<LogItem>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  double micros() const { return micros_; }
  const std::shared_ptr<std::string> &logLevel() const { return logLevel_; }
  const std::shared_ptr<std::string> &message() const { return message_; }
private:
  double micros_;
  std::shared_ptr<std::string> logLevel_;
  std::shared_ptr<std::string> message_;
};
class QueryConfig final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<QueryConfig> create(int64_t serial, std::shared_ptr<std::string> status, std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<std::string>>>>> objects, std::shared_ptr<std::string> fullStackTrace, bool isDisplayable, std::shared_ptr<std::string> name, std::shared_ptr<std::string> owner, std::shared_ptr<std::string> configurationType, bool enabled, double heapSize, std::shared_ptr<std::string> dbServerName, bool enableGcLogs, std::shared_ptr<std::string> envVars, double dataMemoryRatio, std::shared_ptr<std::string> jvmArgs, std::shared_ptr<std::string> extraClasspaths, std::shared_ptr<std::string> jvmProfile, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> adminGroups, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> viewerGroups, int32_t restartUsers, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> scheduling, int64_t timeout, std::shared_ptr<std::string> scriptLanguage, std::shared_ptr<std::string> scriptPath, std::shared_ptr<std::string> websocketUrl, std::shared_ptr<std::string> serviceId);
  QueryConfig(Private, int64_t serial, std::shared_ptr<std::string> status, std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<std::string>>>>> objects, std::shared_ptr<std::string> fullStackTrace, bool isDisplayable, std::shared_ptr<std::string> name, std::shared_ptr<std::string> owner, std::shared_ptr<std::string> configurationType, bool enabled, double heapSize, std::shared_ptr<std::string> dbServerName, bool enableGcLogs, std::shared_ptr<std::string> envVars, double dataMemoryRatio, std::shared_ptr<std::string> jvmArgs, std::shared_ptr<std::string> extraClasspaths, std::shared_ptr<std::string> jvmProfile, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> adminGroups, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> viewerGroups, int32_t restartUsers, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> scheduling, int64_t timeout, std::shared_ptr<std::string> scriptLanguage, std::shared_ptr<std::string> scriptPath, std::shared_ptr<std::string> websocketUrl, std::shared_ptr<std::string> serviceId);
  QueryConfig(const QueryConfig &other) = delete;
  QueryConfig &operator=(const QueryConfig &other) = delete;
  ~QueryConfig() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<QueryConfig> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<QueryConfig>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  int64_t serial() const { return serial_; }
  const std::shared_ptr<std::string> &status() const { return status_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<std::string>>>>> &objects() const { return objects_; }
  const std::shared_ptr<std::string> &fullStackTrace() const { return fullStackTrace_; }
  bool isDisplayable() const { return isDisplayable_; }
  const std::shared_ptr<std::string> &name() const { return name_; }
  const std::shared_ptr<std::string> &owner() const { return owner_; }
  const std::shared_ptr<std::string> &configurationType() const { return configurationType_; }
  bool enabled() const { return enabled_; }
  double heapSize() const { return heapSize_; }
  const std::shared_ptr<std::string> &dbServerName() const { return dbServerName_; }
  bool enableGcLogs() const { return enableGcLogs_; }
  const std::shared_ptr<std::string> &envVars() const { return envVars_; }
  double dataMemoryRatio() const { return dataMemoryRatio_; }
  const std::shared_ptr<std::string> &jvmArgs() const { return jvmArgs_; }
  const std::shared_ptr<std::string> &extraClasspaths() const { return extraClasspaths_; }
  const std::shared_ptr<std::string> &jvmProfile() const { return jvmProfile_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &adminGroups() const { return adminGroups_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &viewerGroups() const { return viewerGroups_; }
  int32_t restartUsers() const { return restartUsers_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &scheduling() const { return scheduling_; }
  int64_t timeout() const { return timeout_; }
  const std::shared_ptr<std::string> &scriptLanguage() const { return scriptLanguage_; }
  const std::shared_ptr<std::string> &scriptPath() const { return scriptPath_; }
  const std::shared_ptr<std::string> &websocketUrl() const { return websocketUrl_; }
  const std::shared_ptr<std::string> &serviceId() const { return serviceId_; }
private:
  int64_t serial_;
  std::shared_ptr<std::string> status_;
  std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<std::string>>>>> objects_;
  std::shared_ptr<std::string> fullStackTrace_;
  bool isDisplayable_;
  std::shared_ptr<std::string> name_;
  std::shared_ptr<std::string> owner_;
  std::shared_ptr<std::string> configurationType_;
  bool enabled_;
  double heapSize_;
  std::shared_ptr<std::string> dbServerName_;
  bool enableGcLogs_;
  std::shared_ptr<std::string> envVars_;
  double dataMemoryRatio_;
  std::shared_ptr<std::string> jvmArgs_;
  std::shared_ptr<std::string> extraClasspaths_;
  std::shared_ptr<std::string> jvmProfile_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> adminGroups_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> viewerGroups_;
  int32_t restartUsers_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> scheduling_;
  int64_t timeout_;
  std::shared_ptr<std::string> scriptLanguage_;
  std::shared_ptr<std::string> scriptPath_;
  std::shared_ptr<std::string> websocketUrl_;
  std::shared_ptr<std::string> serviceId_;
};
class QueryConstants final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<QueryConstants> create(double minHeapGb, double defaultMaxHeapGb, double minDataRatio, double maxDataRatio, double maxScriptCodeLength, double consoleDefaultHeap, double pqDefaultHeap, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> serverNames, std::shared_ptr<std::vector<double>> maxHeapServer);
  QueryConstants(Private, double minHeapGb, double defaultMaxHeapGb, double minDataRatio, double maxDataRatio, double maxScriptCodeLength, double consoleDefaultHeap, double pqDefaultHeap, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> serverNames, std::shared_ptr<std::vector<double>> maxHeapServer);
  QueryConstants(const QueryConstants &other) = delete;
  QueryConstants &operator=(const QueryConstants &other) = delete;
  ~QueryConstants() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<QueryConstants> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<QueryConstants>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  double minHeapGb() const { return minHeapGb_; }
  double defaultMaxHeapGb() const { return defaultMaxHeapGb_; }
  double minDataRatio() const { return minDataRatio_; }
  double maxDataRatio() const { return maxDataRatio_; }
  double maxScriptCodeLength() const { return maxScriptCodeLength_; }
  double consoleDefaultHeap() const { return consoleDefaultHeap_; }
  double pqDefaultHeap() const { return pqDefaultHeap_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &serverNames() const { return serverNames_; }
  const std::shared_ptr<std::vector<double>> &maxHeapServer() const { return maxHeapServer_; }
private:
  double minHeapGb_;
  double defaultMaxHeapGb_;
  double minDataRatio_;
  double maxDataRatio_;
  double maxScriptCodeLength_;
  double consoleDefaultHeap_;
  double pqDefaultHeap_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> serverNames_;
  std::shared_ptr<std::vector<double>> maxHeapServer_;
};
class QuerySelectionPermissions final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<QuerySelectionPermissions> create(bool allAdmin, bool allOwner, bool allRestartable, bool allStoppable, bool allStopped, bool allDisabled, bool allEnabled, bool allTemporary, bool allImportMerge, bool readOnlyUser);
  QuerySelectionPermissions(Private, bool allAdmin, bool allOwner, bool allRestartable, bool allStoppable, bool allStopped, bool allDisabled, bool allEnabled, bool allTemporary, bool allImportMerge, bool readOnlyUser);
  QuerySelectionPermissions(const QuerySelectionPermissions &other) = delete;
  QuerySelectionPermissions &operator=(const QuerySelectionPermissions &other) = delete;
  ~QuerySelectionPermissions() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<QuerySelectionPermissions> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<QuerySelectionPermissions>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  bool allAdmin() const { return allAdmin_; }
  bool allOwner() const { return allOwner_; }
  bool allRestartable() const { return allRestartable_; }
  bool allStoppable() const { return allStoppable_; }
  bool allStopped() const { return allStopped_; }
  bool allDisabled() const { return allDisabled_; }
  bool allEnabled() const { return allEnabled_; }
  bool allTemporary() const { return allTemporary_; }
  bool allImportMerge() const { return allImportMerge_; }
  bool readOnlyUser() const { return readOnlyUser_; }
private:
  bool allAdmin_;
  bool allOwner_;
  bool allRestartable_;
  bool allStoppable_;
  bool allStopped_;
  bool allDisabled_;
  bool allEnabled_;
  bool allTemporary_;
  bool allImportMerge_;
  bool readOnlyUser_;
};
class Range final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<Range> create(int64_t first, int64_t last);
  Range(Private, int64_t first, int64_t last);
  Range(const Range &other) = delete;
  Range &operator=(const Range &other) = delete;
  ~Range() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<Range> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<Range>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  int64_t first() const { return first_; }
  int64_t last() const { return last_; }
private:
  int64_t first_;
  int64_t last_;
};
class RangeSet final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<RangeSet> create(std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Range>>> sortedRanges);
  RangeSet(Private, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Range>>> sortedRanges);
  RangeSet(const RangeSet &other) = delete;
  RangeSet &operator=(const RangeSet &other) = delete;
  ~RangeSet() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<RangeSet> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<RangeSet>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Range>>> &sortedRanges() const { return sortedRanges_; }
private:
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Range>>> sortedRanges_;
};
class RefreshToken final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<RefreshToken> create(std::shared_ptr<std::vector<int8_t>> bytes, int64_t expiry);
  RefreshToken(Private, std::shared_ptr<std::vector<int8_t>> bytes, int64_t expiry);
  RefreshToken(const RefreshToken &other) = delete;
  RefreshToken &operator=(const RefreshToken &other) = delete;
  ~RefreshToken() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<RefreshToken> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<RefreshToken>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::vector<int8_t>> &bytes() const { return bytes_; }
  int64_t expiry() const { return expiry_; }
private:
  std::shared_ptr<std::vector<int8_t>> bytes_;
  int64_t expiry_;
};
class RollupDefinition final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<RollupDefinition> create(deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::rollupDefinition::LeafType leafType, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> byColumns, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> sourceColumnNames, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> rollupColumnNames);
  RollupDefinition(Private, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::rollupDefinition::LeafType leafType, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> byColumns, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> sourceColumnNames, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> rollupColumnNames);
  RollupDefinition(const RollupDefinition &other) = delete;
  RollupDefinition &operator=(const RollupDefinition &other) = delete;
  ~RollupDefinition() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<RollupDefinition> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<RollupDefinition>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::rollupDefinition::LeafType leafType() const { return leafType_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &byColumns() const { return byColumns_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &sourceColumnNames() const { return sourceColumnNames_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &rollupColumnNames() const { return rollupColumnNames_; }
private:
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::rollupDefinition::LeafType leafType_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> byColumns_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> sourceColumnNames_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> rollupColumnNames_;
};
class RowValues final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<RowValues> create(std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnValue>>> columns);
  RowValues(Private, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnValue>>> columns);
  RowValues(const RowValues &other) = delete;
  RowValues &operator=(const RowValues &other) = delete;
  ~RowValues() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<RowValues> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<RowValues>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnValue>>> &columns() const { return columns_; }
private:
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnValue>>> columns_;
};
class ServerConfigValues final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<ServerConfigValues> create(std::shared_ptr<std::string> gradleVersion, std::shared_ptr<std::string> vcsVersion, std::shared_ptr<std::string> javaVersion, std::shared_ptr<std::string> hostName, std::shared_ptr<std::string> systemName, std::shared_ptr<std::string> systemType, std::shared_ptr<std::string> supportContact, std::shared_ptr<std::string> supportDocs, bool isSettingsLogoConfigured);
  ServerConfigValues(Private, std::shared_ptr<std::string> gradleVersion, std::shared_ptr<std::string> vcsVersion, std::shared_ptr<std::string> javaVersion, std::shared_ptr<std::string> hostName, std::shared_ptr<std::string> systemName, std::shared_ptr<std::string> systemType, std::shared_ptr<std::string> supportContact, std::shared_ptr<std::string> supportDocs, bool isSettingsLogoConfigured);
  ServerConfigValues(const ServerConfigValues &other) = delete;
  ServerConfigValues &operator=(const ServerConfigValues &other) = delete;
  ~ServerConfigValues() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<ServerConfigValues> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<ServerConfigValues>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::string> &gradleVersion() const { return gradleVersion_; }
  const std::shared_ptr<std::string> &vcsVersion() const { return vcsVersion_; }
  const std::shared_ptr<std::string> &javaVersion() const { return javaVersion_; }
  const std::shared_ptr<std::string> &hostName() const { return hostName_; }
  const std::shared_ptr<std::string> &systemName() const { return systemName_; }
  const std::shared_ptr<std::string> &systemType() const { return systemType_; }
  const std::shared_ptr<std::string> &supportContact() const { return supportContact_; }
  const std::shared_ptr<std::string> &supportDocs() const { return supportDocs_; }
  bool isSettingsLogoConfigured() const { return isSettingsLogoConfigured_; }
private:
  std::shared_ptr<std::string> gradleVersion_;
  std::shared_ptr<std::string> vcsVersion_;
  std::shared_ptr<std::string> javaVersion_;
  std::shared_ptr<std::string> hostName_;
  std::shared_ptr<std::string> systemName_;
  std::shared_ptr<std::string> systemType_;
  std::shared_ptr<std::string> supportContact_;
  std::shared_ptr<std::string> supportDocs_;
  bool isSettingsLogoConfigured_;
};
class ShiftedRange final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<ShiftedRange> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Range> range, int64_t delta);
  ShiftedRange(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Range> range, int64_t delta);
  ShiftedRange(const ShiftedRange &other) = delete;
  ShiftedRange &operator=(const ShiftedRange &other) = delete;
  ~ShiftedRange() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<ShiftedRange> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<ShiftedRange>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Range> &range() const { return range_; }
  int64_t delta() const { return delta_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Range> range_;
  int64_t delta_;
};
class SortDescriptor final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<SortDescriptor> create(int32_t columnIndex, std::shared_ptr<std::string> dir, std::shared_ptr<std::string> columnName, bool abs);
  SortDescriptor(Private, int32_t columnIndex, std::shared_ptr<std::string> dir, std::shared_ptr<std::string> columnName, bool abs);
  SortDescriptor(const SortDescriptor &other) = delete;
  SortDescriptor &operator=(const SortDescriptor &other) = delete;
  ~SortDescriptor() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<SortDescriptor> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<SortDescriptor>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  int32_t columnIndex() const { return columnIndex_; }
  const std::shared_ptr<std::string> &dir() const { return dir_; }
  const std::shared_ptr<std::string> &columnName() const { return columnName_; }
  bool abs() const { return abs_; }
private:
  int32_t columnIndex_;
  std::shared_ptr<std::string> dir_;
  std::shared_ptr<std::string> columnName_;
  bool abs_;
};
class TableDefinition final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<TableDefinition> create(std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnDefinition>>> columns);
  TableDefinition(Private, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnDefinition>>> columns);
  TableDefinition(const TableDefinition &other) = delete;
  TableDefinition &operator=(const TableDefinition &other) = delete;
  ~TableDefinition() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<TableDefinition> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<TableDefinition>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnDefinition>>> &columns() const { return columns_; }
private:
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnDefinition>>> columns_;
};
class TableHandle final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  template<typename ...Args>
  static std::shared_ptr<TableHandle> create(Args &&...args) {
    deephaven::openAPI::lowlevel::remoting::custom::com::illumon::iris::web::shared::data::TableHandleCustom custom(std::forward<Args>(args)...);
    return std::make_shared<TableHandle>(Private(), std::move(custom));
  }
  TableHandle(Private, deephaven::openAPI::lowlevel::remoting::custom::com::illumon::iris::web::shared::data::TableHandleCustom custom);
  TableHandle(const TableHandle &other) = delete;
  TableHandle &operator=(const TableHandle &other) = delete;
  ~TableHandle() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<TableHandle> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<TableHandle>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const deephaven::openAPI::lowlevel::remoting::custom::com::illumon::iris::web::shared::data::TableHandleCustom &custom() const { return custom_; }
private:
  deephaven::openAPI::lowlevel::remoting::custom::com::illumon::iris::web::shared::data::TableHandleCustom custom_;
};
class TableMapDeclaration final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<TableMapDeclaration> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData> keys, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> handle);
  TableMapDeclaration(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData> keys, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> handle);
  TableMapDeclaration(const TableMapDeclaration &other) = delete;
  TableMapDeclaration &operator=(const TableMapDeclaration &other) = delete;
  ~TableMapDeclaration() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<TableMapDeclaration> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<TableMapDeclaration>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData> &keys() const { return keys_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> &handle() const { return handle_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData> keys_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> handle_;
};
class TableMapHandle final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<TableMapHandle> create(int32_t serverId);
  TableMapHandle(Private, int32_t serverId);
  TableMapHandle(const TableMapHandle &other) = delete;
  TableMapHandle &operator=(const TableMapHandle &other) = delete;
  ~TableMapHandle() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<TableMapHandle> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<TableMapHandle>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  int32_t serverId() const { return serverId_; }
private:
  int32_t serverId_;
};
class TableSnapshot final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<TableSnapshot> create(deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::tableSnapshot::SnapshotType snapshotType, int64_t deltaSequence, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData>>> dataColumns, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> includedRows, int64_t tableSize);
  TableSnapshot(Private, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::tableSnapshot::SnapshotType snapshotType, int64_t deltaSequence, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData>>> dataColumns, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> includedRows, int64_t tableSize);
  TableSnapshot(const TableSnapshot &other) = delete;
  TableSnapshot &operator=(const TableSnapshot &other) = delete;
  ~TableSnapshot() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<TableSnapshot> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<TableSnapshot>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::tableSnapshot::SnapshotType snapshotType() const { return snapshotType_; }
  int64_t deltaSequence() const { return deltaSequence_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData>>> &dataColumns() const { return dataColumns_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> &includedRows() const { return includedRows_; }
  int64_t tableSize() const { return tableSize_; }
private:
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::tableSnapshot::SnapshotType snapshotType_;
  int64_t deltaSequence_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData>>> dataColumns_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> includedRows_;
  int64_t tableSize_;
};
class TableSubscriptionRequest final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<TableSubscriptionRequest> create(int32_t subscriptionId, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> rows, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> columns);
  TableSubscriptionRequest(Private, int32_t subscriptionId, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> rows, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> columns);
  TableSubscriptionRequest(const TableSubscriptionRequest &other) = delete;
  TableSubscriptionRequest &operator=(const TableSubscriptionRequest &other) = delete;
  ~TableSubscriptionRequest() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<TableSubscriptionRequest> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<TableSubscriptionRequest>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  int32_t subscriptionId() const { return subscriptionId_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> &rows() const { return rows_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> &columns() const { return columns_; }
private:
  int32_t subscriptionId_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> rows_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> columns_;
};
class TableValues final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<TableValues> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RowValues>>> rows);
  TableValues(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RowValues>>> rows);
  TableValues(const TableValues &other) = delete;
  TableValues &operator=(const TableValues &other) = delete;
  ~TableValues() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<TableValues> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<TableValues>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &handle() const { return handle_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RowValues>>> &rows() const { return rows_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RowValues>>> rows_;
};
class UserInfo final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<UserInfo> create(std::shared_ptr<std::string> username, std::shared_ptr<std::string> operateAs);
  UserInfo(Private, std::shared_ptr<std::string> username, std::shared_ptr<std::string> operateAs);
  UserInfo(const UserInfo &other) = delete;
  UserInfo &operator=(const UserInfo &other) = delete;
  ~UserInfo() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<UserInfo> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<UserInfo>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::string> &username() const { return username_; }
  const std::shared_ptr<std::string> &operateAs() const { return operateAs_; }
private:
  std::shared_ptr<std::string> username_;
  std::shared_ptr<std::string> operateAs_;
};
namespace columns {
class ColumnData : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<ColumnData> create();
  explicit ColumnData(Private);
  ColumnData(const ColumnData &other) = delete;
  ColumnData &operator=(const ColumnData &other) = delete;
  ~ColumnData() override;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const override;
  static std::shared_ptr<ColumnData> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<ColumnData>(typeName, nullptr);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  virtual void acceptVisitor(ColumnDataVisitor *visitor) const {
    visitor->visit(this);
  }
private:
};
class BigDecimalArrayColumnData final : public deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<BigDecimalArrayColumnData> create(std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::math::BigDecimal>>> data);
  BigDecimalArrayColumnData(Private, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::math::BigDecimal>>> data);
  BigDecimalArrayColumnData(const BigDecimalArrayColumnData &other) = delete;
  BigDecimalArrayColumnData &operator=(const BigDecimalArrayColumnData &other) = delete;
  ~BigDecimalArrayColumnData() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<BigDecimalArrayColumnData> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<BigDecimalArrayColumnData>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(ColumnDataVisitor *visitor) const final {
    visitor->visit(this);
  }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::math::BigDecimal>>> &data() const { return data_; }
private:
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::math::BigDecimal>>> data_;
};
class BigIntegerArrayColumnData final : public deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<BigIntegerArrayColumnData> create(std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::math::BigInteger>>> data);
  BigIntegerArrayColumnData(Private, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::math::BigInteger>>> data);
  BigIntegerArrayColumnData(const BigIntegerArrayColumnData &other) = delete;
  BigIntegerArrayColumnData &operator=(const BigIntegerArrayColumnData &other) = delete;
  ~BigIntegerArrayColumnData() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<BigIntegerArrayColumnData> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<BigIntegerArrayColumnData>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(ColumnDataVisitor *visitor) const final {
    visitor->visit(this);
  }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::math::BigInteger>>> &data() const { return data_; }
private:
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::math::BigInteger>>> data_;
};
class ByteArrayColumnData final : public deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<ByteArrayColumnData> create(std::shared_ptr<std::vector<int8_t>> data);
  ByteArrayColumnData(Private, std::shared_ptr<std::vector<int8_t>> data);
  ByteArrayColumnData(const ByteArrayColumnData &other) = delete;
  ByteArrayColumnData &operator=(const ByteArrayColumnData &other) = delete;
  ~ByteArrayColumnData() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<ByteArrayColumnData> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<ByteArrayColumnData>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(ColumnDataVisitor *visitor) const final {
    visitor->visit(this);
  }
  const std::shared_ptr<std::vector<int8_t>> &data() const { return data_; }
private:
  std::shared_ptr<std::vector<int8_t>> data_;
};
class CharArrayColumnData final : public deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<CharArrayColumnData> create(std::shared_ptr<std::vector<char16_t>> data);
  CharArrayColumnData(Private, std::shared_ptr<std::vector<char16_t>> data);
  CharArrayColumnData(const CharArrayColumnData &other) = delete;
  CharArrayColumnData &operator=(const CharArrayColumnData &other) = delete;
  ~CharArrayColumnData() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<CharArrayColumnData> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<CharArrayColumnData>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(ColumnDataVisitor *visitor) const final {
    visitor->visit(this);
  }
  const std::shared_ptr<std::vector<char16_t>> &data() const { return data_; }
private:
  std::shared_ptr<std::vector<char16_t>> data_;
};
class DoubleArrayColumnData final : public deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<DoubleArrayColumnData> create(std::shared_ptr<std::vector<double>> data);
  DoubleArrayColumnData(Private, std::shared_ptr<std::vector<double>> data);
  DoubleArrayColumnData(const DoubleArrayColumnData &other) = delete;
  DoubleArrayColumnData &operator=(const DoubleArrayColumnData &other) = delete;
  ~DoubleArrayColumnData() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<DoubleArrayColumnData> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<DoubleArrayColumnData>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(ColumnDataVisitor *visitor) const final {
    visitor->visit(this);
  }
  const std::shared_ptr<std::vector<double>> &data() const { return data_; }
private:
  std::shared_ptr<std::vector<double>> data_;
};
class FloatArrayColumnData final : public deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<FloatArrayColumnData> create(std::shared_ptr<std::vector<float>> data);
  FloatArrayColumnData(Private, std::shared_ptr<std::vector<float>> data);
  FloatArrayColumnData(const FloatArrayColumnData &other) = delete;
  FloatArrayColumnData &operator=(const FloatArrayColumnData &other) = delete;
  ~FloatArrayColumnData() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<FloatArrayColumnData> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<FloatArrayColumnData>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(ColumnDataVisitor *visitor) const final {
    visitor->visit(this);
  }
  const std::shared_ptr<std::vector<float>> &data() const { return data_; }
private:
  std::shared_ptr<std::vector<float>> data_;
};
class IntArrayColumnData final : public deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<IntArrayColumnData> create(std::shared_ptr<std::vector<int32_t>> data);
  IntArrayColumnData(Private, std::shared_ptr<std::vector<int32_t>> data);
  IntArrayColumnData(const IntArrayColumnData &other) = delete;
  IntArrayColumnData &operator=(const IntArrayColumnData &other) = delete;
  ~IntArrayColumnData() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<IntArrayColumnData> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<IntArrayColumnData>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(ColumnDataVisitor *visitor) const final {
    visitor->visit(this);
  }
  const std::shared_ptr<std::vector<int32_t>> &data() const { return data_; }
private:
  std::shared_ptr<std::vector<int32_t>> data_;
};
class LocalDateArrayColumnData final : public deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<LocalDateArrayColumnData> create(std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LocalDate>>> data);
  LocalDateArrayColumnData(Private, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LocalDate>>> data);
  LocalDateArrayColumnData(const LocalDateArrayColumnData &other) = delete;
  LocalDateArrayColumnData &operator=(const LocalDateArrayColumnData &other) = delete;
  ~LocalDateArrayColumnData() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<LocalDateArrayColumnData> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<LocalDateArrayColumnData>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(ColumnDataVisitor *visitor) const final {
    visitor->visit(this);
  }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LocalDate>>> &data() const { return data_; }
private:
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LocalDate>>> data_;
};
class LocalTimeArrayColumnData final : public deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<LocalTimeArrayColumnData> create(std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LocalTime>>> data);
  LocalTimeArrayColumnData(Private, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LocalTime>>> data);
  LocalTimeArrayColumnData(const LocalTimeArrayColumnData &other) = delete;
  LocalTimeArrayColumnData &operator=(const LocalTimeArrayColumnData &other) = delete;
  ~LocalTimeArrayColumnData() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<LocalTimeArrayColumnData> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<LocalTimeArrayColumnData>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(ColumnDataVisitor *visitor) const final {
    visitor->visit(this);
  }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LocalTime>>> &data() const { return data_; }
private:
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LocalTime>>> data_;
};
class LongArrayColumnData final : public deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<LongArrayColumnData> create(std::shared_ptr<std::vector<int64_t>> data);
  LongArrayColumnData(Private, std::shared_ptr<std::vector<int64_t>> data);
  LongArrayColumnData(const LongArrayColumnData &other) = delete;
  LongArrayColumnData &operator=(const LongArrayColumnData &other) = delete;
  ~LongArrayColumnData() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<LongArrayColumnData> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<LongArrayColumnData>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(ColumnDataVisitor *visitor) const final {
    visitor->visit(this);
  }
  const std::shared_ptr<std::vector<int64_t>> &data() const { return data_; }
private:
  std::shared_ptr<std::vector<int64_t>> data_;
};
class ShortArrayColumnData final : public deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<ShortArrayColumnData> create(std::shared_ptr<std::vector<int16_t>> data);
  ShortArrayColumnData(Private, std::shared_ptr<std::vector<int16_t>> data);
  ShortArrayColumnData(const ShortArrayColumnData &other) = delete;
  ShortArrayColumnData &operator=(const ShortArrayColumnData &other) = delete;
  ~ShortArrayColumnData() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<ShortArrayColumnData> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<ShortArrayColumnData>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(ColumnDataVisitor *visitor) const final {
    visitor->visit(this);
  }
  const std::shared_ptr<std::vector<int16_t>> &data() const { return data_; }
private:
  std::shared_ptr<std::vector<int16_t>> data_;
};
class StringArrayArrayColumnData final : public deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<StringArrayArrayColumnData> create(std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<std::string>>>>> data);
  StringArrayArrayColumnData(Private, std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<std::string>>>>> data);
  StringArrayArrayColumnData(const StringArrayArrayColumnData &other) = delete;
  StringArrayArrayColumnData &operator=(const StringArrayArrayColumnData &other) = delete;
  ~StringArrayArrayColumnData() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<StringArrayArrayColumnData> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<StringArrayArrayColumnData>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(ColumnDataVisitor *visitor) const final {
    visitor->visit(this);
  }
  const std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<std::string>>>>> &data() const { return data_; }
private:
  std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<std::string>>>>> data_;
};
class StringArrayColumnData final : public deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<StringArrayColumnData> create(std::shared_ptr<std::vector<std::shared_ptr<std::string>>> data);
  StringArrayColumnData(Private, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> data);
  StringArrayColumnData(const StringArrayColumnData &other) = delete;
  StringArrayColumnData &operator=(const StringArrayColumnData &other) = delete;
  ~StringArrayColumnData() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<StringArrayColumnData> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<StringArrayColumnData>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(ColumnDataVisitor *visitor) const final {
    visitor->visit(this);
  }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &data() const { return data_; }
private:
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> data_;
};
}  // namespace columns
namespace plot {
class AxisDescriptor final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<AxisDescriptor> create(std::shared_ptr<std::string> id, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::axisDescriptor::AxisFormatType formatType, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::axisDescriptor::AxisType type, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::axisDescriptor::AxisPosition position, bool log, std::shared_ptr<std::string> label, std::shared_ptr<std::string> labelFont, std::shared_ptr<std::string> ticksFont, std::shared_ptr<std::string> formatPattern, std::shared_ptr<std::string> color, double minRange, double maxRange, bool minorTicksVisible, bool majorTicksVisible, int32_t minorTickCount, double gapBetweenMajorTicks, std::shared_ptr<std::vector<double>> majorTickLocations, double tickLabelAngle, bool invert, bool isTimeAxis, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::BusinessCalendarDescriptor> businessCalendarDescriptor);
  AxisDescriptor(Private, std::shared_ptr<std::string> id, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::axisDescriptor::AxisFormatType formatType, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::axisDescriptor::AxisType type, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::axisDescriptor::AxisPosition position, bool log, std::shared_ptr<std::string> label, std::shared_ptr<std::string> labelFont, std::shared_ptr<std::string> ticksFont, std::shared_ptr<std::string> formatPattern, std::shared_ptr<std::string> color, double minRange, double maxRange, bool minorTicksVisible, bool majorTicksVisible, int32_t minorTickCount, double gapBetweenMajorTicks, std::shared_ptr<std::vector<double>> majorTickLocations, double tickLabelAngle, bool invert, bool isTimeAxis, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::BusinessCalendarDescriptor> businessCalendarDescriptor);
  AxisDescriptor(const AxisDescriptor &other) = delete;
  AxisDescriptor &operator=(const AxisDescriptor &other) = delete;
  ~AxisDescriptor() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<AxisDescriptor> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<AxisDescriptor>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::string> &id() const { return id_; }
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::axisDescriptor::AxisFormatType formatType() const { return formatType_; }
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::axisDescriptor::AxisType type() const { return type_; }
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::axisDescriptor::AxisPosition position() const { return position_; }
  bool log() const { return log_; }
  const std::shared_ptr<std::string> &label() const { return label_; }
  const std::shared_ptr<std::string> &labelFont() const { return labelFont_; }
  const std::shared_ptr<std::string> &ticksFont() const { return ticksFont_; }
  const std::shared_ptr<std::string> &formatPattern() const { return formatPattern_; }
  const std::shared_ptr<std::string> &color() const { return color_; }
  double minRange() const { return minRange_; }
  double maxRange() const { return maxRange_; }
  bool minorTicksVisible() const { return minorTicksVisible_; }
  bool majorTicksVisible() const { return majorTicksVisible_; }
  int32_t minorTickCount() const { return minorTickCount_; }
  double gapBetweenMajorTicks() const { return gapBetweenMajorTicks_; }
  const std::shared_ptr<std::vector<double>> &majorTickLocations() const { return majorTickLocations_; }
  double tickLabelAngle() const { return tickLabelAngle_; }
  bool invert() const { return invert_; }
  bool isTimeAxis() const { return isTimeAxis_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::BusinessCalendarDescriptor> &businessCalendarDescriptor() const { return businessCalendarDescriptor_; }
private:
  std::shared_ptr<std::string> id_;
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::axisDescriptor::AxisFormatType formatType_;
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::axisDescriptor::AxisType type_;
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::axisDescriptor::AxisPosition position_;
  bool log_;
  std::shared_ptr<std::string> label_;
  std::shared_ptr<std::string> labelFont_;
  std::shared_ptr<std::string> ticksFont_;
  std::shared_ptr<std::string> formatPattern_;
  std::shared_ptr<std::string> color_;
  double minRange_;
  double maxRange_;
  bool minorTicksVisible_;
  bool majorTicksVisible_;
  int32_t minorTickCount_;
  double gapBetweenMajorTicks_;
  std::shared_ptr<std::vector<double>> majorTickLocations_;
  double tickLabelAngle_;
  bool invert_;
  bool isTimeAxis_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::BusinessCalendarDescriptor> businessCalendarDescriptor_;
};
class ChartDescriptor final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<ChartDescriptor> create(int32_t colspan, int32_t rowspan, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SeriesDescriptor>>> series, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::MultiSeriesDescriptor>>> multiSeries, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::AxisDescriptor>>> axes, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::chartDescriptor::ChartType chartType, std::shared_ptr<std::string> title, std::shared_ptr<std::string> titleFont, std::shared_ptr<std::string> titleColor, bool showLegend, std::shared_ptr<std::string> legendFont, std::shared_ptr<std::string> legendColor, bool is3d);
  ChartDescriptor(Private, int32_t colspan, int32_t rowspan, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SeriesDescriptor>>> series, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::MultiSeriesDescriptor>>> multiSeries, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::AxisDescriptor>>> axes, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::chartDescriptor::ChartType chartType, std::shared_ptr<std::string> title, std::shared_ptr<std::string> titleFont, std::shared_ptr<std::string> titleColor, bool showLegend, std::shared_ptr<std::string> legendFont, std::shared_ptr<std::string> legendColor, bool is3d);
  ChartDescriptor(const ChartDescriptor &other) = delete;
  ChartDescriptor &operator=(const ChartDescriptor &other) = delete;
  ~ChartDescriptor() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<ChartDescriptor> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<ChartDescriptor>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  int32_t colspan() const { return colspan_; }
  int32_t rowspan() const { return rowspan_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SeriesDescriptor>>> &series() const { return series_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::MultiSeriesDescriptor>>> &multiSeries() const { return multiSeries_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::AxisDescriptor>>> &axes() const { return axes_; }
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::chartDescriptor::ChartType chartType() const { return chartType_; }
  const std::shared_ptr<std::string> &title() const { return title_; }
  const std::shared_ptr<std::string> &titleFont() const { return titleFont_; }
  const std::shared_ptr<std::string> &titleColor() const { return titleColor_; }
  bool showLegend() const { return showLegend_; }
  const std::shared_ptr<std::string> &legendFont() const { return legendFont_; }
  const std::shared_ptr<std::string> &legendColor() const { return legendColor_; }
  bool is3d() const { return is3d_; }
private:
  int32_t colspan_;
  int32_t rowspan_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SeriesDescriptor>>> series_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::MultiSeriesDescriptor>>> multiSeries_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::AxisDescriptor>>> axes_;
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::chartDescriptor::ChartType chartType_;
  std::shared_ptr<std::string> title_;
  std::shared_ptr<std::string> titleFont_;
  std::shared_ptr<std::string> titleColor_;
  bool showLegend_;
  std::shared_ptr<std::string> legendFont_;
  std::shared_ptr<std::string> legendColor_;
  bool is3d_;
};
class FigureDescriptor final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<FigureDescriptor> create(std::shared_ptr<std::string> title, std::shared_ptr<std::string> titleFont, std::shared_ptr<std::string> titleColor, bool resizable, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::ThemeDescriptor> theme, bool isDefaultTheme, double updateInterval, int32_t cols, int32_t rows, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::ChartDescriptor>>> charts, std::shared_ptr<std::vector<int32_t>> tableIds, std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>> plotHandleIds, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle>>> tableMaps, std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>> tableMapIds, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> errors);
  FigureDescriptor(Private, std::shared_ptr<std::string> title, std::shared_ptr<std::string> titleFont, std::shared_ptr<std::string> titleColor, bool resizable, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::ThemeDescriptor> theme, bool isDefaultTheme, double updateInterval, int32_t cols, int32_t rows, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::ChartDescriptor>>> charts, std::shared_ptr<std::vector<int32_t>> tableIds, std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>> plotHandleIds, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle>>> tableMaps, std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>> tableMapIds, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> errors);
  FigureDescriptor(const FigureDescriptor &other) = delete;
  FigureDescriptor &operator=(const FigureDescriptor &other) = delete;
  ~FigureDescriptor() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<FigureDescriptor> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<FigureDescriptor>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::string> &title() const { return title_; }
  const std::shared_ptr<std::string> &titleFont() const { return titleFont_; }
  const std::shared_ptr<std::string> &titleColor() const { return titleColor_; }
  bool resizable() const { return resizable_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::ThemeDescriptor> &theme() const { return theme_; }
  bool isDefaultTheme() const { return isDefaultTheme_; }
  double updateInterval() const { return updateInterval_; }
  int32_t cols() const { return cols_; }
  int32_t rows() const { return rows_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::ChartDescriptor>>> &charts() const { return charts_; }
  const std::shared_ptr<std::vector<int32_t>> &tableIds() const { return tableIds_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>> &plotHandleIds() const { return plotHandleIds_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle>>> &tableMaps() const { return tableMaps_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>> &tableMapIds() const { return tableMapIds_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &errors() const { return errors_; }
private:
  std::shared_ptr<std::string> title_;
  std::shared_ptr<std::string> titleFont_;
  std::shared_ptr<std::string> titleColor_;
  bool resizable_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::ThemeDescriptor> theme_;
  bool isDefaultTheme_;
  double updateInterval_;
  int32_t cols_;
  int32_t rows_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::ChartDescriptor>>> charts_;
  std::shared_ptr<std::vector<int32_t>> tableIds_;
  std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>> plotHandleIds_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle>>> tableMaps_;
  std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>> tableMapIds_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> errors_;
};
class MultiSeriesDescriptor final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<MultiSeriesDescriptor> create(deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SeriesPlotStyle plotStyle, std::shared_ptr<std::string> name, std::shared_ptr<std::string> lineColorDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> lineColorKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> lineColorValues, std::shared_ptr<std::string> pointColorDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointColorKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointColorValues, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> linesVisibleDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> linesVisibleKeys, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean>>> linesVisibleValues, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> pointsVisibleDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointsVisibleKeys, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean>>> pointsVisibleValues, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> gradientVisibleDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> gradientVisibleKeys, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean>>> gradientVisibleValues, std::shared_ptr<std::string> pointLabelFormatDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointLabelFormatKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointLabelFormatValues, std::shared_ptr<std::string> xToolTipPatternDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> xToolTipPatternKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> xToolTipPatternValues, std::shared_ptr<std::string> yToolTipPatternDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> yToolTipPatternKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> yToolTipPatternValues, std::shared_ptr<std::string> pointLabelDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointLabelKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointLabelValues, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Double> pointSizeDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointSizeKeys, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Double>>> pointSizeValues, std::shared_ptr<std::string> pointShapeDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointShapeKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointShapeValues, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::MultiSeriesSourceDescriptor>>> dataSources);
  MultiSeriesDescriptor(Private, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SeriesPlotStyle plotStyle, std::shared_ptr<std::string> name, std::shared_ptr<std::string> lineColorDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> lineColorKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> lineColorValues, std::shared_ptr<std::string> pointColorDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointColorKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointColorValues, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> linesVisibleDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> linesVisibleKeys, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean>>> linesVisibleValues, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> pointsVisibleDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointsVisibleKeys, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean>>> pointsVisibleValues, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> gradientVisibleDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> gradientVisibleKeys, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean>>> gradientVisibleValues, std::shared_ptr<std::string> pointLabelFormatDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointLabelFormatKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointLabelFormatValues, std::shared_ptr<std::string> xToolTipPatternDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> xToolTipPatternKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> xToolTipPatternValues, std::shared_ptr<std::string> yToolTipPatternDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> yToolTipPatternKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> yToolTipPatternValues, std::shared_ptr<std::string> pointLabelDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointLabelKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointLabelValues, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Double> pointSizeDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointSizeKeys, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Double>>> pointSizeValues, std::shared_ptr<std::string> pointShapeDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointShapeKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointShapeValues, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::MultiSeriesSourceDescriptor>>> dataSources);
  MultiSeriesDescriptor(const MultiSeriesDescriptor &other) = delete;
  MultiSeriesDescriptor &operator=(const MultiSeriesDescriptor &other) = delete;
  ~MultiSeriesDescriptor() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<MultiSeriesDescriptor> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<MultiSeriesDescriptor>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SeriesPlotStyle plotStyle() const { return plotStyle_; }
  const std::shared_ptr<std::string> &name() const { return name_; }
  const std::shared_ptr<std::string> &lineColorDefault() const { return lineColorDefault_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &lineColorKeys() const { return lineColorKeys_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &lineColorValues() const { return lineColorValues_; }
  const std::shared_ptr<std::string> &pointColorDefault() const { return pointColorDefault_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &pointColorKeys() const { return pointColorKeys_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &pointColorValues() const { return pointColorValues_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> &linesVisibleDefault() const { return linesVisibleDefault_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &linesVisibleKeys() const { return linesVisibleKeys_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean>>> &linesVisibleValues() const { return linesVisibleValues_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> &pointsVisibleDefault() const { return pointsVisibleDefault_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &pointsVisibleKeys() const { return pointsVisibleKeys_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean>>> &pointsVisibleValues() const { return pointsVisibleValues_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> &gradientVisibleDefault() const { return gradientVisibleDefault_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &gradientVisibleKeys() const { return gradientVisibleKeys_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean>>> &gradientVisibleValues() const { return gradientVisibleValues_; }
  const std::shared_ptr<std::string> &pointLabelFormatDefault() const { return pointLabelFormatDefault_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &pointLabelFormatKeys() const { return pointLabelFormatKeys_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &pointLabelFormatValues() const { return pointLabelFormatValues_; }
  const std::shared_ptr<std::string> &xToolTipPatternDefault() const { return xToolTipPatternDefault_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &xToolTipPatternKeys() const { return xToolTipPatternKeys_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &xToolTipPatternValues() const { return xToolTipPatternValues_; }
  const std::shared_ptr<std::string> &yToolTipPatternDefault() const { return yToolTipPatternDefault_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &yToolTipPatternKeys() const { return yToolTipPatternKeys_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &yToolTipPatternValues() const { return yToolTipPatternValues_; }
  const std::shared_ptr<std::string> &pointLabelDefault() const { return pointLabelDefault_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &pointLabelKeys() const { return pointLabelKeys_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &pointLabelValues() const { return pointLabelValues_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Double> &pointSizeDefault() const { return pointSizeDefault_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &pointSizeKeys() const { return pointSizeKeys_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Double>>> &pointSizeValues() const { return pointSizeValues_; }
  const std::shared_ptr<std::string> &pointShapeDefault() const { return pointShapeDefault_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &pointShapeKeys() const { return pointShapeKeys_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &pointShapeValues() const { return pointShapeValues_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::MultiSeriesSourceDescriptor>>> &dataSources() const { return dataSources_; }
private:
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SeriesPlotStyle plotStyle_;
  std::shared_ptr<std::string> name_;
  std::shared_ptr<std::string> lineColorDefault_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> lineColorKeys_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> lineColorValues_;
  std::shared_ptr<std::string> pointColorDefault_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointColorKeys_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointColorValues_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> linesVisibleDefault_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> linesVisibleKeys_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean>>> linesVisibleValues_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> pointsVisibleDefault_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointsVisibleKeys_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean>>> pointsVisibleValues_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> gradientVisibleDefault_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> gradientVisibleKeys_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean>>> gradientVisibleValues_;
  std::shared_ptr<std::string> pointLabelFormatDefault_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointLabelFormatKeys_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointLabelFormatValues_;
  std::shared_ptr<std::string> xToolTipPatternDefault_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> xToolTipPatternKeys_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> xToolTipPatternValues_;
  std::shared_ptr<std::string> yToolTipPatternDefault_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> yToolTipPatternKeys_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> yToolTipPatternValues_;
  std::shared_ptr<std::string> pointLabelDefault_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointLabelKeys_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointLabelValues_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Double> pointSizeDefault_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointSizeKeys_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Double>>> pointSizeValues_;
  std::shared_ptr<std::string> pointShapeDefault_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointShapeKeys_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointShapeValues_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::MultiSeriesSourceDescriptor>>> dataSources_;
};
class MultiSeriesSourceDescriptor final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<MultiSeriesSourceDescriptor> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::AxisDescriptor> axis, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SourceType type, int32_t tableMapId, std::shared_ptr<std::string> columnName);
  MultiSeriesSourceDescriptor(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::AxisDescriptor> axis, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SourceType type, int32_t tableMapId, std::shared_ptr<std::string> columnName);
  MultiSeriesSourceDescriptor(const MultiSeriesSourceDescriptor &other) = delete;
  MultiSeriesSourceDescriptor &operator=(const MultiSeriesSourceDescriptor &other) = delete;
  ~MultiSeriesSourceDescriptor() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<MultiSeriesSourceDescriptor> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<MultiSeriesSourceDescriptor>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::AxisDescriptor> &axis() const { return axis_; }
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SourceType type() const { return type_; }
  int32_t tableMapId() const { return tableMapId_; }
  const std::shared_ptr<std::string> &columnName() const { return columnName_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::AxisDescriptor> axis_;
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SourceType type_;
  int32_t tableMapId_;
  std::shared_ptr<std::string> columnName_;
};
class OneClickDescriptor final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<OneClickDescriptor> create(std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columns, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnTypes, bool requireAllFiltersToDisplay);
  OneClickDescriptor(Private, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columns, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnTypes, bool requireAllFiltersToDisplay);
  OneClickDescriptor(const OneClickDescriptor &other) = delete;
  OneClickDescriptor &operator=(const OneClickDescriptor &other) = delete;
  ~OneClickDescriptor() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<OneClickDescriptor> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<OneClickDescriptor>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &columns() const { return columns_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &columnTypes() const { return columnTypes_; }
  bool requireAllFiltersToDisplay() const { return requireAllFiltersToDisplay_; }
private:
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columns_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnTypes_;
  bool requireAllFiltersToDisplay_;
};
class SeriesDescriptor final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<SeriesDescriptor> create(deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SeriesPlotStyle plotStyle, std::shared_ptr<std::string> name, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> linesVisible, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> shapesVisible, bool gradientVisible, std::shared_ptr<std::string> lineColor, std::shared_ptr<std::string> pointLabelFormat, std::shared_ptr<std::string> xToolTipPattern, std::shared_ptr<std::string> yToolTipPattern, std::shared_ptr<std::string> shapeLabel, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Double> shapeSize, std::shared_ptr<std::string> shapeColor, std::shared_ptr<std::string> shape, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SourceDescriptor>>> dataSources);
  SeriesDescriptor(Private, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SeriesPlotStyle plotStyle, std::shared_ptr<std::string> name, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> linesVisible, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> shapesVisible, bool gradientVisible, std::shared_ptr<std::string> lineColor, std::shared_ptr<std::string> pointLabelFormat, std::shared_ptr<std::string> xToolTipPattern, std::shared_ptr<std::string> yToolTipPattern, std::shared_ptr<std::string> shapeLabel, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Double> shapeSize, std::shared_ptr<std::string> shapeColor, std::shared_ptr<std::string> shape, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SourceDescriptor>>> dataSources);
  SeriesDescriptor(const SeriesDescriptor &other) = delete;
  SeriesDescriptor &operator=(const SeriesDescriptor &other) = delete;
  ~SeriesDescriptor() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<SeriesDescriptor> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<SeriesDescriptor>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SeriesPlotStyle plotStyle() const { return plotStyle_; }
  const std::shared_ptr<std::string> &name() const { return name_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> &linesVisible() const { return linesVisible_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> &shapesVisible() const { return shapesVisible_; }
  bool gradientVisible() const { return gradientVisible_; }
  const std::shared_ptr<std::string> &lineColor() const { return lineColor_; }
  const std::shared_ptr<std::string> &pointLabelFormat() const { return pointLabelFormat_; }
  const std::shared_ptr<std::string> &xToolTipPattern() const { return xToolTipPattern_; }
  const std::shared_ptr<std::string> &yToolTipPattern() const { return yToolTipPattern_; }
  const std::shared_ptr<std::string> &shapeLabel() const { return shapeLabel_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Double> &shapeSize() const { return shapeSize_; }
  const std::shared_ptr<std::string> &shapeColor() const { return shapeColor_; }
  const std::shared_ptr<std::string> &shape() const { return shape_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SourceDescriptor>>> &dataSources() const { return dataSources_; }
private:
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SeriesPlotStyle plotStyle_;
  std::shared_ptr<std::string> name_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> linesVisible_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> shapesVisible_;
  bool gradientVisible_;
  std::shared_ptr<std::string> lineColor_;
  std::shared_ptr<std::string> pointLabelFormat_;
  std::shared_ptr<std::string> xToolTipPattern_;
  std::shared_ptr<std::string> yToolTipPattern_;
  std::shared_ptr<std::string> shapeLabel_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Double> shapeSize_;
  std::shared_ptr<std::string> shapeColor_;
  std::shared_ptr<std::string> shape_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SourceDescriptor>>> dataSources_;
};
class SourceDescriptor final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<SourceDescriptor> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::AxisDescriptor> axis, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SourceType type, int32_t tableId, int32_t tableMapId, std::shared_ptr<std::string> columnName, std::shared_ptr<std::string> columnType, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::OneClickDescriptor> oneClick);
  SourceDescriptor(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::AxisDescriptor> axis, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SourceType type, int32_t tableId, int32_t tableMapId, std::shared_ptr<std::string> columnName, std::shared_ptr<std::string> columnType, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::OneClickDescriptor> oneClick);
  SourceDescriptor(const SourceDescriptor &other) = delete;
  SourceDescriptor &operator=(const SourceDescriptor &other) = delete;
  ~SourceDescriptor() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<SourceDescriptor> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<SourceDescriptor>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::AxisDescriptor> &axis() const { return axis_; }
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SourceType type() const { return type_; }
  int32_t tableId() const { return tableId_; }
  int32_t tableMapId() const { return tableMapId_; }
  const std::shared_ptr<std::string> &columnName() const { return columnName_; }
  const std::shared_ptr<std::string> &columnType() const { return columnType_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::OneClickDescriptor> &oneClick() const { return oneClick_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::AxisDescriptor> axis_;
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SourceType type_;
  int32_t tableId_;
  int32_t tableMapId_;
  std::shared_ptr<std::string> columnName_;
  std::shared_ptr<std::string> columnType_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::OneClickDescriptor> oneClick_;
};
class ThemeDescriptor final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<ThemeDescriptor> create();
  explicit ThemeDescriptor(Private);
  ThemeDescriptor(const ThemeDescriptor &other) = delete;
  ThemeDescriptor &operator=(const ThemeDescriptor &other) = delete;
  ~ThemeDescriptor() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<ThemeDescriptor> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<ThemeDescriptor>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
private:
};
}  // namespace plot
namespace treetable {
class Key final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  template<typename ...Args>
  static std::shared_ptr<Key> create(Args &&...args) {
    deephaven::openAPI::lowlevel::remoting::custom::com::illumon::iris::web::shared::data::treetable::KeyCustom custom(std::forward<Args>(args)...);
    return std::make_shared<Key>(Private(), std::move(custom));
  }
  Key(Private, deephaven::openAPI::lowlevel::remoting::custom::com::illumon::iris::web::shared::data::treetable::KeyCustom custom);
  Key(const Key &other) = delete;
  Key &operator=(const Key &other) = delete;
  ~Key() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<Key> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<Key>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const deephaven::openAPI::lowlevel::remoting::custom::com::illumon::iris::web::shared::data::treetable::KeyCustom &custom() const { return custom_; }
private:
  deephaven::openAPI::lowlevel::remoting::custom::com::illumon::iris::web::shared::data::treetable::KeyCustom custom_;
};
class TableDetails final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<TableDetails> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::Key> key, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::Key>>> children);
  TableDetails(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::Key> key, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::Key>>> children);
  TableDetails(const TableDetails &other) = delete;
  TableDetails &operator=(const TableDetails &other) = delete;
  ~TableDetails() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<TableDetails> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<TableDetails>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::Key> &key() const { return key_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::Key>>> &children() const { return children_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::Key> key_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::Key>>> children_;
};
class TreeTableRequest final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<TreeTableRequest> create(int64_t viewportStart, int64_t viewportEnd, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> columns, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::FilterDescriptor>>> filters, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::SortDescriptor>>> sorts, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::TableDetails>>> expandedNodes, int32_t keyColumn, std::shared_ptr<std::vector<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::treeTableRequest::TreeRequestOperation>> includedOps, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> sourceTable);
  TreeTableRequest(Private, int64_t viewportStart, int64_t viewportEnd, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> columns, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::FilterDescriptor>>> filters, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::SortDescriptor>>> sorts, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::TableDetails>>> expandedNodes, int32_t keyColumn, std::shared_ptr<std::vector<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::treeTableRequest::TreeRequestOperation>> includedOps, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> sourceTable);
  TreeTableRequest(const TreeTableRequest &other) = delete;
  TreeTableRequest &operator=(const TreeTableRequest &other) = delete;
  ~TreeTableRequest() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<TreeTableRequest> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<TreeTableRequest>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  int64_t viewportStart() const { return viewportStart_; }
  int64_t viewportEnd() const { return viewportEnd_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> &columns() const { return columns_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::FilterDescriptor>>> &filters() const { return filters_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::SortDescriptor>>> &sorts() const { return sorts_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::TableDetails>>> &expandedNodes() const { return expandedNodes_; }
  int32_t keyColumn() const { return keyColumn_; }
  const std::shared_ptr<std::vector<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::treeTableRequest::TreeRequestOperation>> &includedOps() const { return includedOps_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &sourceTable() const { return sourceTable_; }
private:
  int64_t viewportStart_;
  int64_t viewportEnd_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> columns_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::FilterDescriptor>>> filters_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::SortDescriptor>>> sorts_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::TableDetails>>> expandedNodes_;
  int32_t keyColumn_;
  std::shared_ptr<std::vector<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::treeTableRequest::TreeRequestOperation>> includedOps_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> sourceTable_;
};
class TreeTableResult final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<TreeTableResult> create(int64_t treeSize, int64_t snapshotStart, int64_t snapshotEnd, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData>>> snapshotData, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> constituentColumnNames, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData>>> constituentColumnData, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::TableDetails>>> tableDetails, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::Key>>> keyColumn, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::Key>>> parentKeyColumn, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> childPresence, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> sourceTable);
  TreeTableResult(Private, int64_t treeSize, int64_t snapshotStart, int64_t snapshotEnd, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData>>> snapshotData, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> constituentColumnNames, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData>>> constituentColumnData, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::TableDetails>>> tableDetails, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::Key>>> keyColumn, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::Key>>> parentKeyColumn, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> childPresence, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> sourceTable);
  TreeTableResult(const TreeTableResult &other) = delete;
  TreeTableResult &operator=(const TreeTableResult &other) = delete;
  ~TreeTableResult() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<TreeTableResult> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<TreeTableResult>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  int64_t treeSize() const { return treeSize_; }
  int64_t snapshotStart() const { return snapshotStart_; }
  int64_t snapshotEnd() const { return snapshotEnd_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData>>> &snapshotData() const { return snapshotData_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &constituentColumnNames() const { return constituentColumnNames_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData>>> &constituentColumnData() const { return constituentColumnData_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::TableDetails>>> &tableDetails() const { return tableDetails_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::Key>>> &keyColumn() const { return keyColumn_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::Key>>> &parentKeyColumn() const { return parentKeyColumn_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> &childPresence() const { return childPresence_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> &sourceTable() const { return sourceTable_; }
private:
  int64_t treeSize_;
  int64_t snapshotStart_;
  int64_t snapshotEnd_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData>>> snapshotData_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> constituentColumnNames_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData>>> constituentColumnData_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::TableDetails>>> tableDetails_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::Key>>> keyColumn_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::Key>>> parentKeyColumn_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> childPresence_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> sourceTable_;
};
}  // namespace treetable
namespace workspace {
class WorkspaceData final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<WorkspaceData> create(std::shared_ptr<std::string> id, int32_t version, std::shared_ptr<std::string> name, std::shared_ptr<std::string> owner, std::shared_ptr<std::string> dataType, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::workspace::ItemStatus status, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> adminGroups, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> viewerGroups, std::shared_ptr<std::string> data);
  WorkspaceData(Private, std::shared_ptr<std::string> id, int32_t version, std::shared_ptr<std::string> name, std::shared_ptr<std::string> owner, std::shared_ptr<std::string> dataType, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::workspace::ItemStatus status, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> adminGroups, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> viewerGroups, std::shared_ptr<std::string> data);
  WorkspaceData(const WorkspaceData &other) = delete;
  WorkspaceData &operator=(const WorkspaceData &other) = delete;
  ~WorkspaceData() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<WorkspaceData> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<WorkspaceData>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::string> &id() const { return id_; }
  int32_t version() const { return version_; }
  const std::shared_ptr<std::string> &name() const { return name_; }
  const std::shared_ptr<std::string> &owner() const { return owner_; }
  const std::shared_ptr<std::string> &dataType() const { return dataType_; }
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::workspace::ItemStatus status() const { return status_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &adminGroups() const { return adminGroups_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &viewerGroups() const { return viewerGroups_; }
  const std::shared_ptr<std::string> &data() const { return data_; }
private:
  std::shared_ptr<std::string> id_;
  int32_t version_;
  std::shared_ptr<std::string> name_;
  std::shared_ptr<std::string> owner_;
  std::shared_ptr<std::string> dataType_;
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::workspace::ItemStatus status_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> adminGroups_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> viewerGroups_;
  std::shared_ptr<std::string> data_;
};
}  // namespace workspace
}  // namespace data
namespace ide {
class CommandResult final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<CommandResult> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::VariableChanges> changes, std::shared_ptr<std::string> error);
  CommandResult(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::VariableChanges> changes, std::shared_ptr<std::string> error);
  CommandResult(const CommandResult &other) = delete;
  CommandResult &operator=(const CommandResult &other) = delete;
  ~CommandResult() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<CommandResult> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<CommandResult>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::VariableChanges> &changes() const { return changes_; }
  const std::shared_ptr<std::string> &error() const { return error_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::VariableChanges> changes_;
  std::shared_ptr<std::string> error_;
};
class ConsoleAddress final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<ConsoleAddress> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ConnectToken> token, std::shared_ptr<std::string> websocketUrl, std::shared_ptr<std::string> serviceId);
  ConsoleAddress(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ConnectToken> token, std::shared_ptr<std::string> websocketUrl, std::shared_ptr<std::string> serviceId);
  ConsoleAddress(const ConsoleAddress &other) = delete;
  ConsoleAddress &operator=(const ConsoleAddress &other) = delete;
  ~ConsoleAddress() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<ConsoleAddress> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<ConsoleAddress>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ConnectToken> &token() const { return token_; }
  const std::shared_ptr<std::string> &websocketUrl() const { return websocketUrl_; }
  const std::shared_ptr<std::string> &serviceId() const { return serviceId_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ConnectToken> token_;
  std::shared_ptr<std::string> websocketUrl_;
  std::shared_ptr<std::string> serviceId_;
};
class ConsoleConfig final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<ConsoleConfig> create(std::shared_ptr<std::string> dispatcherHost, int32_t dispatcherPort, std::shared_ptr<std::string> jvmProfile, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> classpath, int32_t maxHeapMb, std::shared_ptr<std::string> queryDescription, bool debug, bool detailedGCLogging, bool omitDefaultGcParameters, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> jvmArgs, std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<std::string>>>>> envVars);
  ConsoleConfig(Private, std::shared_ptr<std::string> dispatcherHost, int32_t dispatcherPort, std::shared_ptr<std::string> jvmProfile, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> classpath, int32_t maxHeapMb, std::shared_ptr<std::string> queryDescription, bool debug, bool detailedGCLogging, bool omitDefaultGcParameters, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> jvmArgs, std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<std::string>>>>> envVars);
  ConsoleConfig(const ConsoleConfig &other) = delete;
  ConsoleConfig &operator=(const ConsoleConfig &other) = delete;
  ~ConsoleConfig() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<ConsoleConfig> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<ConsoleConfig>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::string> &dispatcherHost() const { return dispatcherHost_; }
  int32_t dispatcherPort() const { return dispatcherPort_; }
  const std::shared_ptr<std::string> &jvmProfile() const { return jvmProfile_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &classpath() const { return classpath_; }
  int32_t maxHeapMb() const { return maxHeapMb_; }
  const std::shared_ptr<std::string> &queryDescription() const { return queryDescription_; }
  bool debug() const { return debug_; }
  bool detailedGCLogging() const { return detailedGCLogging_; }
  bool omitDefaultGcParameters() const { return omitDefaultGcParameters_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &jvmArgs() const { return jvmArgs_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<std::string>>>>> &envVars() const { return envVars_; }
private:
  std::shared_ptr<std::string> dispatcherHost_;
  int32_t dispatcherPort_;
  std::shared_ptr<std::string> jvmProfile_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> classpath_;
  int32_t maxHeapMb_;
  std::shared_ptr<std::string> queryDescription_;
  bool debug_;
  bool detailedGCLogging_;
  bool omitDefaultGcParameters_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> jvmArgs_;
  std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<std::string>>>>> envVars_;
};
class ConsoleConnectionResult final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<ConsoleConnectionResult> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> tables, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> widgets);
  ConsoleConnectionResult(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> tables, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> widgets);
  ConsoleConnectionResult(const ConsoleConnectionResult &other) = delete;
  ConsoleConnectionResult &operator=(const ConsoleConnectionResult &other) = delete;
  ~ConsoleConnectionResult() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<ConsoleConnectionResult> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<ConsoleConnectionResult>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> &handle() const { return handle_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &tables() const { return tables_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &widgets() const { return widgets_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> tables_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> widgets_;
};
class ConsoleServerAddress final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<ConsoleServerAddress> create(std::shared_ptr<std::string> host, std::shared_ptr<std::string> name, int32_t port);
  ConsoleServerAddress(Private, std::shared_ptr<std::string> host, std::shared_ptr<std::string> name, int32_t port);
  ConsoleServerAddress(const ConsoleServerAddress &other) = delete;
  ConsoleServerAddress &operator=(const ConsoleServerAddress &other) = delete;
  ~ConsoleServerAddress() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<ConsoleServerAddress> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<ConsoleServerAddress>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::string> &host() const { return host_; }
  const std::shared_ptr<std::string> &name() const { return name_; }
  int32_t port() const { return port_; }
private:
  std::shared_ptr<std::string> host_;
  std::shared_ptr<std::string> name_;
  int32_t port_;
};
class ExecutionHandle final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  template<typename ...Args>
  static std::shared_ptr<ExecutionHandle> create(Args &&...args) {
    deephaven::openAPI::lowlevel::remoting::custom::com::illumon::iris::web::shared::ide::ExecutionHandleCustom custom(std::forward<Args>(args)...);
    return std::make_shared<ExecutionHandle>(Private(), std::move(custom));
  }
  ExecutionHandle(Private, deephaven::openAPI::lowlevel::remoting::custom::com::illumon::iris::web::shared::ide::ExecutionHandleCustom custom);
  ExecutionHandle(const ExecutionHandle &other) = delete;
  ExecutionHandle &operator=(const ExecutionHandle &other) = delete;
  ~ExecutionHandle() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<ExecutionHandle> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<ExecutionHandle>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const deephaven::openAPI::lowlevel::remoting::custom::com::illumon::iris::web::shared::ide::ExecutionHandleCustom &custom() const { return custom_; }
private:
  deephaven::openAPI::lowlevel::remoting::custom::com::illumon::iris::web::shared::ide::ExecutionHandleCustom custom_;
};
class ScriptHandle final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  template<typename ...Args>
  static std::shared_ptr<ScriptHandle> create(Args &&...args) {
    deephaven::openAPI::lowlevel::remoting::custom::com::illumon::iris::web::shared::ide::ScriptHandleCustom custom(std::forward<Args>(args)...);
    return std::make_shared<ScriptHandle>(Private(), std::move(custom));
  }
  ScriptHandle(Private, deephaven::openAPI::lowlevel::remoting::custom::com::illumon::iris::web::shared::ide::ScriptHandleCustom custom);
  ScriptHandle(const ScriptHandle &other) = delete;
  ScriptHandle &operator=(const ScriptHandle &other) = delete;
  ~ScriptHandle() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<ScriptHandle> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<ScriptHandle>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const deephaven::openAPI::lowlevel::remoting::custom::com::illumon::iris::web::shared::ide::ScriptHandleCustom &custom() const { return custom_; }
private:
  deephaven::openAPI::lowlevel::remoting::custom::com::illumon::iris::web::shared::ide::ScriptHandleCustom custom_;
};
class VariableChanges final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<VariableChanges> create(std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::VariableDefinition>>> created, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::VariableDefinition>>> updated, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::VariableDefinition>>> removed);
  VariableChanges(Private, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::VariableDefinition>>> created, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::VariableDefinition>>> updated, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::VariableDefinition>>> removed);
  VariableChanges(const VariableChanges &other) = delete;
  VariableChanges &operator=(const VariableChanges &other) = delete;
  ~VariableChanges() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<VariableChanges> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<VariableChanges>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::VariableDefinition>>> &created() const { return created_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::VariableDefinition>>> &updated() const { return updated_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::VariableDefinition>>> &removed() const { return removed_; }
private:
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::VariableDefinition>>> created_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::VariableDefinition>>> updated_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::VariableDefinition>>> removed_;
};
class VariableDefinition final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<VariableDefinition> create(std::shared_ptr<std::string> name, std::shared_ptr<std::string> type);
  VariableDefinition(Private, std::shared_ptr<std::string> name, std::shared_ptr<std::string> type);
  VariableDefinition(const VariableDefinition &other) = delete;
  VariableDefinition &operator=(const VariableDefinition &other) = delete;
  ~VariableDefinition() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<VariableDefinition> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<VariableDefinition>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::string> &name() const { return name_; }
  const std::shared_ptr<std::string> &type() const { return type_; }
private:
  std::shared_ptr<std::string> name_;
  std::shared_ptr<std::string> type_;
};
namespace lsp {
class CompletionContext final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<CompletionContext> create(int32_t triggerKind, std::shared_ptr<std::string> triggerCharacter);
  CompletionContext(Private, int32_t triggerKind, std::shared_ptr<std::string> triggerCharacter);
  CompletionContext(const CompletionContext &other) = delete;
  CompletionContext &operator=(const CompletionContext &other) = delete;
  ~CompletionContext() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<CompletionContext> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<CompletionContext>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  int32_t triggerKind() const { return triggerKind_; }
  const std::shared_ptr<std::string> &triggerCharacter() const { return triggerCharacter_; }
private:
  int32_t triggerKind_;
  std::shared_ptr<std::string> triggerCharacter_;
};
class CompletionItem final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<CompletionItem> create(std::shared_ptr<std::string> label, int32_t kind, std::shared_ptr<std::string> detail, std::shared_ptr<std::string> documentation, bool deprecated, bool preselect, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextEdit> textEdit, std::shared_ptr<std::string> sortText, std::shared_ptr<std::string> filterText, int32_t insertTextFormat, int32_t start, int32_t length, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextEdit>>> additionalTextEdits, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> commitCharacters);
  CompletionItem(Private, std::shared_ptr<std::string> label, int32_t kind, std::shared_ptr<std::string> detail, std::shared_ptr<std::string> documentation, bool deprecated, bool preselect, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextEdit> textEdit, std::shared_ptr<std::string> sortText, std::shared_ptr<std::string> filterText, int32_t insertTextFormat, int32_t start, int32_t length, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextEdit>>> additionalTextEdits, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> commitCharacters);
  CompletionItem(const CompletionItem &other) = delete;
  CompletionItem &operator=(const CompletionItem &other) = delete;
  ~CompletionItem() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<CompletionItem> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<CompletionItem>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::string> &label() const { return label_; }
  int32_t kind() const { return kind_; }
  const std::shared_ptr<std::string> &detail() const { return detail_; }
  const std::shared_ptr<std::string> &documentation() const { return documentation_; }
  bool deprecated() const { return deprecated_; }
  bool preselect() const { return preselect_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextEdit> &textEdit() const { return textEdit_; }
  const std::shared_ptr<std::string> &sortText() const { return sortText_; }
  const std::shared_ptr<std::string> &filterText() const { return filterText_; }
  int32_t insertTextFormat() const { return insertTextFormat_; }
  int32_t start() const { return start_; }
  int32_t length() const { return length_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextEdit>>> &additionalTextEdits() const { return additionalTextEdits_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &commitCharacters() const { return commitCharacters_; }
private:
  std::shared_ptr<std::string> label_;
  int32_t kind_;
  std::shared_ptr<std::string> detail_;
  std::shared_ptr<std::string> documentation_;
  bool deprecated_;
  bool preselect_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextEdit> textEdit_;
  std::shared_ptr<std::string> sortText_;
  std::shared_ptr<std::string> filterText_;
  int32_t insertTextFormat_;
  int32_t start_;
  int32_t length_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextEdit>>> additionalTextEdits_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> commitCharacters_;
};
class TextDocumentPositionParams : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<TextDocumentPositionParams> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentIdentifier> textDocument, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::Position> position);
  TextDocumentPositionParams(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentIdentifier> textDocument, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::Position> position);
  TextDocumentPositionParams(const TextDocumentPositionParams &other) = delete;
  TextDocumentPositionParams &operator=(const TextDocumentPositionParams &other) = delete;
  ~TextDocumentPositionParams() override;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const override;
  static std::shared_ptr<TextDocumentPositionParams> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<TextDocumentPositionParams>(typeName, nullptr);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  virtual void acceptVisitor(TextDocumentPositionParamsVisitor *visitor) const {
    visitor->visit(this);
  }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentIdentifier> &textDocument() const { return textDocument_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::Position> &position() const { return position_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentIdentifier> textDocument_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::Position> position_;
};
class CompletionParams final : public deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentPositionParams {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<CompletionParams> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentIdentifier> textDocument, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::Position> position, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::CompletionContext> context);
  CompletionParams(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentIdentifier> textDocument, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::Position> position, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::CompletionContext> context);
  CompletionParams(const CompletionParams &other) = delete;
  CompletionParams &operator=(const CompletionParams &other) = delete;
  ~CompletionParams() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<CompletionParams> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<CompletionParams>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(TextDocumentPositionParamsVisitor *visitor) const final {
    visitor->visit(this);
  }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::CompletionContext> &context() const { return context_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::CompletionContext> context_;
};
class DidChangeTextDocumentParams final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<DidChangeTextDocumentParams> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::VersionedTextDocumentIdentifier> textDocument, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentContentChangeEvent>>> contentChanges);
  DidChangeTextDocumentParams(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::VersionedTextDocumentIdentifier> textDocument, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentContentChangeEvent>>> contentChanges);
  DidChangeTextDocumentParams(const DidChangeTextDocumentParams &other) = delete;
  DidChangeTextDocumentParams &operator=(const DidChangeTextDocumentParams &other) = delete;
  ~DidChangeTextDocumentParams() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<DidChangeTextDocumentParams> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<DidChangeTextDocumentParams>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::VersionedTextDocumentIdentifier> &textDocument() const { return textDocument_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentContentChangeEvent>>> &contentChanges() const { return contentChanges_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::VersionedTextDocumentIdentifier> textDocument_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentContentChangeEvent>>> contentChanges_;
};
class DidCloseTextDocumentParams final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<DidCloseTextDocumentParams> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentIdentifier> textDocument);
  DidCloseTextDocumentParams(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentIdentifier> textDocument);
  DidCloseTextDocumentParams(const DidCloseTextDocumentParams &other) = delete;
  DidCloseTextDocumentParams &operator=(const DidCloseTextDocumentParams &other) = delete;
  ~DidCloseTextDocumentParams() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<DidCloseTextDocumentParams> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<DidCloseTextDocumentParams>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentIdentifier> &textDocument() const { return textDocument_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentIdentifier> textDocument_;
};
class DidOpenTextDocumentParams final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<DidOpenTextDocumentParams> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentItem> textDocument);
  DidOpenTextDocumentParams(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentItem> textDocument);
  DidOpenTextDocumentParams(const DidOpenTextDocumentParams &other) = delete;
  DidOpenTextDocumentParams &operator=(const DidOpenTextDocumentParams &other) = delete;
  ~DidOpenTextDocumentParams() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<DidOpenTextDocumentParams> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<DidOpenTextDocumentParams>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentItem> &textDocument() const { return textDocument_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentItem> textDocument_;
};
class DocumentRange final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<DocumentRange> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::Position> start, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::Position> end);
  DocumentRange(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::Position> start, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::Position> end);
  DocumentRange(const DocumentRange &other) = delete;
  DocumentRange &operator=(const DocumentRange &other) = delete;
  ~DocumentRange() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<DocumentRange> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<DocumentRange>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::Position> &start() const { return start_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::Position> &end() const { return end_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::Position> start_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::Position> end_;
};
class Position final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<Position> create(int32_t line, int32_t character);
  Position(Private, int32_t line, int32_t character);
  Position(const Position &other) = delete;
  Position &operator=(const Position &other) = delete;
  ~Position() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<Position> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<Position>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  int32_t line() const { return line_; }
  int32_t character() const { return character_; }
private:
  int32_t line_;
  int32_t character_;
};
class TextDocumentContentChangeEvent final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<TextDocumentContentChangeEvent> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DocumentRange> range, int32_t rangeLength, std::shared_ptr<std::string> text);
  TextDocumentContentChangeEvent(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DocumentRange> range, int32_t rangeLength, std::shared_ptr<std::string> text);
  TextDocumentContentChangeEvent(const TextDocumentContentChangeEvent &other) = delete;
  TextDocumentContentChangeEvent &operator=(const TextDocumentContentChangeEvent &other) = delete;
  ~TextDocumentContentChangeEvent() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<TextDocumentContentChangeEvent> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<TextDocumentContentChangeEvent>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DocumentRange> &range() const { return range_; }
  int32_t rangeLength() const { return rangeLength_; }
  const std::shared_ptr<std::string> &text() const { return text_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DocumentRange> range_;
  int32_t rangeLength_;
  std::shared_ptr<std::string> text_;
};
class TextDocumentIdentifier : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<TextDocumentIdentifier> create(std::shared_ptr<std::string> uri);
  TextDocumentIdentifier(Private, std::shared_ptr<std::string> uri);
  TextDocumentIdentifier(const TextDocumentIdentifier &other) = delete;
  TextDocumentIdentifier &operator=(const TextDocumentIdentifier &other) = delete;
  ~TextDocumentIdentifier() override;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const override;
  static std::shared_ptr<TextDocumentIdentifier> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<TextDocumentIdentifier>(typeName, nullptr);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  virtual void acceptVisitor(TextDocumentIdentifierVisitor *visitor) const {
    visitor->visit(this);
  }
  const std::shared_ptr<std::string> &uri() const { return uri_; }
private:
  std::shared_ptr<std::string> uri_;
};
class TextDocumentItem final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<TextDocumentItem> create(std::shared_ptr<std::string> uri, std::shared_ptr<std::string> languageId, std::shared_ptr<std::string> text, int32_t version);
  TextDocumentItem(Private, std::shared_ptr<std::string> uri, std::shared_ptr<std::string> languageId, std::shared_ptr<std::string> text, int32_t version);
  TextDocumentItem(const TextDocumentItem &other) = delete;
  TextDocumentItem &operator=(const TextDocumentItem &other) = delete;
  ~TextDocumentItem() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<TextDocumentItem> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<TextDocumentItem>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::string> &uri() const { return uri_; }
  const std::shared_ptr<std::string> &languageId() const { return languageId_; }
  const std::shared_ptr<std::string> &text() const { return text_; }
  int32_t version() const { return version_; }
private:
  std::shared_ptr<std::string> uri_;
  std::shared_ptr<std::string> languageId_;
  std::shared_ptr<std::string> text_;
  int32_t version_;
};
class TextEdit final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<TextEdit> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DocumentRange> range, std::shared_ptr<std::string> text);
  TextEdit(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DocumentRange> range, std::shared_ptr<std::string> text);
  TextEdit(const TextEdit &other) = delete;
  TextEdit &operator=(const TextEdit &other) = delete;
  ~TextEdit() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<TextEdit> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<TextEdit>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DocumentRange> &range() const { return range_; }
  const std::shared_ptr<std::string> &text() const { return text_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DocumentRange> range_;
  std::shared_ptr<std::string> text_;
};
class VersionedTextDocumentIdentifier final : public deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentIdentifier {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<VersionedTextDocumentIdentifier> create(std::shared_ptr<std::string> uri, int32_t version);
  VersionedTextDocumentIdentifier(Private, std::shared_ptr<std::string> uri, int32_t version);
  VersionedTextDocumentIdentifier(const VersionedTextDocumentIdentifier &other) = delete;
  VersionedTextDocumentIdentifier &operator=(const VersionedTextDocumentIdentifier &other) = delete;
  ~VersionedTextDocumentIdentifier() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<VersionedTextDocumentIdentifier> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<VersionedTextDocumentIdentifier>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  void acceptVisitor(TextDocumentIdentifierVisitor *visitor) const final {
    visitor->visit(this);
  }
  int32_t version() const { return version_; }
private:
  int32_t version_;
};
}  // namespace lsp
}  // namespace ide
namespace metrics {
class MetricsLog final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<MetricsLog> create(std::shared_ptr<std::string> type, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::ServerReplyHandle> clientId, int64_t nano);
  MetricsLog(Private, std::shared_ptr<std::string> type, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::ServerReplyHandle> clientId, int64_t nano);
  MetricsLog(const MetricsLog &other) = delete;
  MetricsLog &operator=(const MetricsLog &other) = delete;
  ~MetricsLog() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<MetricsLog> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<MetricsLog>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<std::string> &type() const { return type_; }
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::ServerReplyHandle> &clientId() const { return clientId_; }
  int64_t nano() const { return nano_; }
private:
  std::shared_ptr<std::string> type_;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::ServerReplyHandle> clientId_;
  int64_t nano_;
};
}  // namespace metrics
namespace requests {
class AddToInputTableRequest final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<AddToInputTableRequest> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableValues> rowsToAdd, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> tablesToAdd);
  AddToInputTableRequest(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableValues> rowsToAdd, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> tablesToAdd);
  AddToInputTableRequest(const AddToInputTableRequest &other) = delete;
  AddToInputTableRequest &operator=(const AddToInputTableRequest &other) = delete;
  ~AddToInputTableRequest() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<AddToInputTableRequest> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<AddToInputTableRequest>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableValues> &rowsToAdd() const { return rowsToAdd_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> &tablesToAdd() const { return tablesToAdd_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableValues> rowsToAdd_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> tablesToAdd_;
};
class AddToInputTableResponse final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<AddToInputTableResponse> create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableValues> failedRows, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> failedTables, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> failureMessages);
  AddToInputTableResponse(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableValues> failedRows, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> failedTables, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> failureMessages);
  AddToInputTableResponse(const AddToInputTableResponse &other) = delete;
  AddToInputTableResponse &operator=(const AddToInputTableResponse &other) = delete;
  ~AddToInputTableResponse() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<AddToInputTableResponse> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<AddToInputTableResponse>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableValues> &failedRows() const { return failedRows_; }
  const std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> &failedTables() const { return failedTables_; }
  const std::shared_ptr<std::vector<std::shared_ptr<std::string>>> &failureMessages() const { return failureMessages_; }
private:
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableValues> failedRows_;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> failedTables_;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> failureMessages_;
};
}  // namespace requests
}  // namespace shared
}  // namespace web
}  // namespace iris
}  // namespace illumon
}  // namespace com
namespace java {
namespace lang {
class Boolean final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  template<typename ...Args>
  static std::shared_ptr<Boolean> create(Args &&...args) {
    deephaven::openAPI::lowlevel::remoting::custom::java::lang::BooleanCustom custom(std::forward<Args>(args)...);
    return std::make_shared<Boolean>(Private(), std::move(custom));
  }
  Boolean(Private, deephaven::openAPI::lowlevel::remoting::custom::java::lang::BooleanCustom custom);
  Boolean(const Boolean &other) = delete;
  Boolean &operator=(const Boolean &other) = delete;
  ~Boolean() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<Boolean> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<Boolean>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const deephaven::openAPI::lowlevel::remoting::custom::java::lang::BooleanCustom &custom() const { return custom_; }
private:
  deephaven::openAPI::lowlevel::remoting::custom::java::lang::BooleanCustom custom_;
};
class Byte final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  template<typename ...Args>
  static std::shared_ptr<Byte> create(Args &&...args) {
    deephaven::openAPI::lowlevel::remoting::custom::java::lang::ByteCustom custom(std::forward<Args>(args)...);
    return std::make_shared<Byte>(Private(), std::move(custom));
  }
  Byte(Private, deephaven::openAPI::lowlevel::remoting::custom::java::lang::ByteCustom custom);
  Byte(const Byte &other) = delete;
  Byte &operator=(const Byte &other) = delete;
  ~Byte() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<Byte> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<Byte>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const deephaven::openAPI::lowlevel::remoting::custom::java::lang::ByteCustom &custom() const { return custom_; }
private:
  deephaven::openAPI::lowlevel::remoting::custom::java::lang::ByteCustom custom_;
};
class Character final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  template<typename ...Args>
  static std::shared_ptr<Character> create(Args &&...args) {
    deephaven::openAPI::lowlevel::remoting::custom::java::lang::CharacterCustom custom(std::forward<Args>(args)...);
    return std::make_shared<Character>(Private(), std::move(custom));
  }
  Character(Private, deephaven::openAPI::lowlevel::remoting::custom::java::lang::CharacterCustom custom);
  Character(const Character &other) = delete;
  Character &operator=(const Character &other) = delete;
  ~Character() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<Character> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<Character>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const deephaven::openAPI::lowlevel::remoting::custom::java::lang::CharacterCustom &custom() const { return custom_; }
private:
  deephaven::openAPI::lowlevel::remoting::custom::java::lang::CharacterCustom custom_;
};
class Double final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  template<typename ...Args>
  static std::shared_ptr<Double> create(Args &&...args) {
    deephaven::openAPI::lowlevel::remoting::custom::java::lang::DoubleCustom custom(std::forward<Args>(args)...);
    return std::make_shared<Double>(Private(), std::move(custom));
  }
  Double(Private, deephaven::openAPI::lowlevel::remoting::custom::java::lang::DoubleCustom custom);
  Double(const Double &other) = delete;
  Double &operator=(const Double &other) = delete;
  ~Double() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<Double> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<Double>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const deephaven::openAPI::lowlevel::remoting::custom::java::lang::DoubleCustom &custom() const { return custom_; }
private:
  deephaven::openAPI::lowlevel::remoting::custom::java::lang::DoubleCustom custom_;
};
class Float final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  template<typename ...Args>
  static std::shared_ptr<Float> create(Args &&...args) {
    deephaven::openAPI::lowlevel::remoting::custom::java::lang::FloatCustom custom(std::forward<Args>(args)...);
    return std::make_shared<Float>(Private(), std::move(custom));
  }
  Float(Private, deephaven::openAPI::lowlevel::remoting::custom::java::lang::FloatCustom custom);
  Float(const Float &other) = delete;
  Float &operator=(const Float &other) = delete;
  ~Float() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<Float> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<Float>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const deephaven::openAPI::lowlevel::remoting::custom::java::lang::FloatCustom &custom() const { return custom_; }
private:
  deephaven::openAPI::lowlevel::remoting::custom::java::lang::FloatCustom custom_;
};
class Integer final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  template<typename ...Args>
  static std::shared_ptr<Integer> create(Args &&...args) {
    deephaven::openAPI::lowlevel::remoting::custom::java::lang::IntegerCustom custom(std::forward<Args>(args)...);
    return std::make_shared<Integer>(Private(), std::move(custom));
  }
  Integer(Private, deephaven::openAPI::lowlevel::remoting::custom::java::lang::IntegerCustom custom);
  Integer(const Integer &other) = delete;
  Integer &operator=(const Integer &other) = delete;
  ~Integer() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<Integer> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<Integer>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const deephaven::openAPI::lowlevel::remoting::custom::java::lang::IntegerCustom &custom() const { return custom_; }
private:
  deephaven::openAPI::lowlevel::remoting::custom::java::lang::IntegerCustom custom_;
};
class Long final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  template<typename ...Args>
  static std::shared_ptr<Long> create(Args &&...args) {
    deephaven::openAPI::lowlevel::remoting::custom::java::lang::LongCustom custom(std::forward<Args>(args)...);
    return std::make_shared<Long>(Private(), std::move(custom));
  }
  Long(Private, deephaven::openAPI::lowlevel::remoting::custom::java::lang::LongCustom custom);
  Long(const Long &other) = delete;
  Long &operator=(const Long &other) = delete;
  ~Long() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<Long> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<Long>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const deephaven::openAPI::lowlevel::remoting::custom::java::lang::LongCustom &custom() const { return custom_; }
private:
  deephaven::openAPI::lowlevel::remoting::custom::java::lang::LongCustom custom_;
};
class Number final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  static std::shared_ptr<Number> create();
  explicit Number(Private);
  Number(const Number &other) = delete;
  Number &operator=(const Number &other) = delete;
  ~Number() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<Number> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<Number>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
private:
};
class Short final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  template<typename ...Args>
  static std::shared_ptr<Short> create(Args &&...args) {
    deephaven::openAPI::lowlevel::remoting::custom::java::lang::ShortCustom custom(std::forward<Args>(args)...);
    return std::make_shared<Short>(Private(), std::move(custom));
  }
  Short(Private, deephaven::openAPI::lowlevel::remoting::custom::java::lang::ShortCustom custom);
  Short(const Short &other) = delete;
  Short &operator=(const Short &other) = delete;
  ~Short() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<Short> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<Short>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const deephaven::openAPI::lowlevel::remoting::custom::java::lang::ShortCustom &custom() const { return custom_; }
private:
  deephaven::openAPI::lowlevel::remoting::custom::java::lang::ShortCustom custom_;
};
class String final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  template<typename ...Args>
  static std::shared_ptr<String> create(Args &&...args) {
    deephaven::openAPI::lowlevel::remoting::custom::java::lang::StringCustom custom(std::forward<Args>(args)...);
    return std::make_shared<String>(Private(), std::move(custom));
  }
  String(Private, deephaven::openAPI::lowlevel::remoting::custom::java::lang::StringCustom custom);
  String(const String &other) = delete;
  String &operator=(const String &other) = delete;
  ~String() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<String> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<String>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const deephaven::openAPI::lowlevel::remoting::custom::java::lang::StringCustom &custom() const { return custom_; }
private:
  deephaven::openAPI::lowlevel::remoting::custom::java::lang::StringCustom custom_;
};
class Void final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  template<typename ...Args>
  static std::shared_ptr<Void> create(Args &&...args) {
    deephaven::openAPI::lowlevel::remoting::custom::java::lang::VoidCustom custom(std::forward<Args>(args)...);
    return std::make_shared<Void>(Private(), std::move(custom));
  }
  Void(Private, deephaven::openAPI::lowlevel::remoting::custom::java::lang::VoidCustom custom);
  Void(const Void &other) = delete;
  Void &operator=(const Void &other) = delete;
  ~Void() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<Void> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<Void>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const deephaven::openAPI::lowlevel::remoting::custom::java::lang::VoidCustom &custom() const { return custom_; }
private:
  deephaven::openAPI::lowlevel::remoting::custom::java::lang::VoidCustom custom_;
};
}  // namespace lang
namespace math {
class BigDecimal final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  template<typename ...Args>
  static std::shared_ptr<BigDecimal> create(Args &&...args) {
    deephaven::openAPI::lowlevel::remoting::custom::java::math::BigDecimalCustom custom(std::forward<Args>(args)...);
    return std::make_shared<BigDecimal>(Private(), std::move(custom));
  }
  BigDecimal(Private, deephaven::openAPI::lowlevel::remoting::custom::java::math::BigDecimalCustom custom);
  BigDecimal(const BigDecimal &other) = delete;
  BigDecimal &operator=(const BigDecimal &other) = delete;
  ~BigDecimal() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<BigDecimal> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<BigDecimal>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const deephaven::openAPI::lowlevel::remoting::custom::java::math::BigDecimalCustom &custom() const { return custom_; }
private:
  deephaven::openAPI::lowlevel::remoting::custom::java::math::BigDecimalCustom custom_;
};
class BigInteger final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  template<typename ...Args>
  static std::shared_ptr<BigInteger> create(Args &&...args) {
    deephaven::openAPI::lowlevel::remoting::custom::java::math::BigIntegerCustom custom(std::forward<Args>(args)...);
    return std::make_shared<BigInteger>(Private(), std::move(custom));
  }
  BigInteger(Private, deephaven::openAPI::lowlevel::remoting::custom::java::math::BigIntegerCustom custom);
  BigInteger(const BigInteger &other) = delete;
  BigInteger &operator=(const BigInteger &other) = delete;
  ~BigInteger() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<BigInteger> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<BigInteger>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const deephaven::openAPI::lowlevel::remoting::custom::java::math::BigIntegerCustom &custom() const { return custom_; }
private:
  deephaven::openAPI::lowlevel::remoting::custom::java::math::BigIntegerCustom custom_;
};
}  // namespace math
namespace util {
class BitSet final : public deephaven::openAPI::core::remoting::Object {
public:
  static const boost::string_view typeName;
  template<typename ...Args>
  static std::shared_ptr<BitSet> create(Args &&...args) {
    deephaven::openAPI::lowlevel::remoting::custom::java::util::BitSetCustom custom(std::forward<Args>(args)...);
    return std::make_shared<BitSet>(Private(), std::move(custom));
  }
  BitSet(Private, deephaven::openAPI::lowlevel::remoting::custom::java::util::BitSetCustom custom);
  BitSet(const BitSet &other) = delete;
  BitSet &operator=(const BitSet &other) = delete;
  ~BitSet() final;
  void serializeObject(deephaven::openAPI::core::remoting::util::Serializer *s) const final;
  static std::shared_ptr<BitSet> deserializeObject(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
    return deserializer->lookupOrDeserialize<BitSet>(typeName, &deserializeObjectHelper);
  }
  static std::shared_ptr<deephaven::openAPI::core::remoting::Object> deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer);
  const deephaven::openAPI::lowlevel::remoting::custom::java::util::BitSetCustom &custom() const { return custom_; }
private:
  deephaven::openAPI::lowlevel::remoting::custom::java::util::BitSetCustom custom_;
};
}  // namespace util
}  // namespace java
extern std::array<const char *, 20> dynamicDeserializerNames;
extern std::array<deephaven::openAPI::core::remoting::util::Deserializer::objectFactory_t, 20> dynamicDeserializerMethods;
}  // namespace generated
}  // namespace remoting
}  // namespace lowlevel
}  // namespace openAPI
}  // namespace deephaven
