#include "lowlevel/generated/shared_objects.h"
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
const boost::string_view ServerSharedHash::hash = "-34ad0ff8fab6747111f40a6b35f5422a9e88cccf";
const boost::string_view WorkerSharedHash::hash = "-2708f1559a3905ea3ee33cb7619ed25816c7f65d";
}  // namespace generated
const boost::string_view AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::businessCalendarDescriptor::DayOfWeek>::typeName = "com.illumon.iris.web.shared.data.BusinessCalendarDescriptor.DayOfWeek";
const boost::string_view AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columnStatistics::ColumnType>::typeName = "com.illumon.iris.web.shared.data.ColumnStatistics.ColumnType";
const boost::string_view AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::filterDescriptor::FilterOperation>::typeName = "com.illumon.iris.web.shared.data.FilterDescriptor.FilterOperation";
const boost::string_view AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::filterDescriptor::ValueType>::typeName = "com.illumon.iris.web.shared.data.FilterDescriptor.ValueType";
const boost::string_view AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::joinDescriptor::JoinType>::typeName = "com.illumon.iris.web.shared.data.JoinDescriptor.JoinType";
const boost::string_view AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::rollupDefinition::LeafType>::typeName = "com.illumon.iris.web.shared.data.RollupDefinition.LeafType";
const boost::string_view AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::tableSnapshot::SnapshotType>::typeName = "com.illumon.iris.web.shared.data.TableSnapshot.SnapshotType";
const boost::string_view AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::axisDescriptor::AxisFormatType>::typeName = "com.illumon.iris.web.shared.data.plot.AxisDescriptor.AxisFormatType";
const boost::string_view AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::axisDescriptor::AxisPosition>::typeName = "com.illumon.iris.web.shared.data.plot.AxisDescriptor.AxisPosition";
const boost::string_view AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::axisDescriptor::AxisType>::typeName = "com.illumon.iris.web.shared.data.plot.AxisDescriptor.AxisType";
const boost::string_view AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::chartDescriptor::ChartType>::typeName = "com.illumon.iris.web.shared.data.plot.ChartDescriptor.ChartType";
const boost::string_view AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SeriesPlotStyle>::typeName = "com.illumon.iris.web.shared.data.plot.SeriesPlotStyle";
const boost::string_view AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SourceType>::typeName = "com.illumon.iris.web.shared.data.plot.SourceType";
const boost::string_view AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::treeTableRequest::TreeRequestOperation>::typeName = "com.illumon.iris.web.shared.data.treetable.TreeTableRequest.TreeRequestOperation";
const boost::string_view AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::workspace::ItemStatus>::typeName = "com.illumon.iris.web.shared.data.workspace.ItemStatus";
const boost::string_view AggregateTypeName<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ConsoleSessionType>::typeName = "com.illumon.iris.web.shared.ide.ConsoleSessionType";
const boost::string_view AggregateTypeName<std::vector<int8_t>>::typeName = "byte[]";
const boost::string_view AggregateTypeName<std::vector<char16_t>>::typeName = "char[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::batchTableRequest::SerializedTableOps>>>::typeName = "com.illumon.iris.web.shared.batch.BatchTableRequest.SerializedTableOps[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::AggregateDescriptor>>>::typeName = "com.illumon.iris.web.shared.batch.aggregates.AggregateDescriptor[]";
const boost::string_view AggregateTypeName<std::vector<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::businessCalendarDescriptor::DayOfWeek>>::typeName = "com.illumon.iris.web.shared.data.BusinessCalendarDescriptor.DayOfWeek[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::BusinessPeriod>>>::typeName = "com.illumon.iris.web.shared.data.BusinessPeriod[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::catalog::Table>>>::typeName = "com.illumon.iris.web.shared.data.Catalog.Table[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnDefinition>>>::typeName = "com.illumon.iris.web.shared.data.ColumnDefinition[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnHolder>>>::typeName = "com.illumon.iris.web.shared.data.ColumnHolder[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnValue>>>::typeName = "com.illumon.iris.web.shared.data.ColumnValue[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::CustomColumnDescriptor>>>::typeName = "com.illumon.iris.web.shared.data.CustomColumnDescriptor[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::deltaUpdates::ColumnAdditions>>>::typeName = "com.illumon.iris.web.shared.data.DeltaUpdates.ColumnAdditions[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::deltaUpdates::ColumnModifications>>>::typeName = "com.illumon.iris.web.shared.data.DeltaUpdates.ColumnModifications[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::FilterDescriptor>>>::typeName = "com.illumon.iris.web.shared.data.FilterDescriptor[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Holiday>>>::typeName = "com.illumon.iris.web.shared.data.Holiday[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::InitialTableDefinition>>>::typeName = "com.illumon.iris.web.shared.data.InitialTableDefinition[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LocalDate>>>::typeName = "com.illumon.iris.web.shared.data.LocalDate[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LocalTime>>>::typeName = "com.illumon.iris.web.shared.data.LocalTime[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Range>>>::typeName = "com.illumon.iris.web.shared.data.Range[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RowValues>>>::typeName = "com.illumon.iris.web.shared.data.RowValues[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ShiftedRange>>>::typeName = "com.illumon.iris.web.shared.data.ShiftedRange[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::SortDescriptor>>>::typeName = "com.illumon.iris.web.shared.data.SortDescriptor[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>>::typeName = "com.illumon.iris.web.shared.data.TableHandle[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle>>>::typeName = "com.illumon.iris.web.shared.data.TableMapHandle[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableSubscriptionRequest>>>::typeName = "com.illumon.iris.web.shared.data.TableSubscriptionRequest[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::BigDecimalArrayColumnData>>>::typeName = "com.illumon.iris.web.shared.data.columns.BigDecimalArrayColumnData[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::BigIntegerArrayColumnData>>>::typeName = "com.illumon.iris.web.shared.data.columns.BigIntegerArrayColumnData[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ByteArrayColumnData>>>::typeName = "com.illumon.iris.web.shared.data.columns.ByteArrayColumnData[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::CharArrayColumnData>>>::typeName = "com.illumon.iris.web.shared.data.columns.CharArrayColumnData[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData>>>::typeName = "com.illumon.iris.web.shared.data.columns.ColumnData[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::DoubleArrayColumnData>>>::typeName = "com.illumon.iris.web.shared.data.columns.DoubleArrayColumnData[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::FloatArrayColumnData>>>::typeName = "com.illumon.iris.web.shared.data.columns.FloatArrayColumnData[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::IntArrayColumnData>>>::typeName = "com.illumon.iris.web.shared.data.columns.IntArrayColumnData[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::LocalDateArrayColumnData>>>::typeName = "com.illumon.iris.web.shared.data.columns.LocalDateArrayColumnData[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::LocalTimeArrayColumnData>>>::typeName = "com.illumon.iris.web.shared.data.columns.LocalTimeArrayColumnData[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::LongArrayColumnData>>>::typeName = "com.illumon.iris.web.shared.data.columns.LongArrayColumnData[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ShortArrayColumnData>>>::typeName = "com.illumon.iris.web.shared.data.columns.ShortArrayColumnData[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::StringArrayArrayColumnData>>>::typeName = "com.illumon.iris.web.shared.data.columns.StringArrayArrayColumnData[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::StringArrayColumnData>>>::typeName = "com.illumon.iris.web.shared.data.columns.StringArrayColumnData[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::AxisDescriptor>>>::typeName = "com.illumon.iris.web.shared.data.plot.AxisDescriptor[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::ChartDescriptor>>>::typeName = "com.illumon.iris.web.shared.data.plot.ChartDescriptor[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::MultiSeriesDescriptor>>>::typeName = "com.illumon.iris.web.shared.data.plot.MultiSeriesDescriptor[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::MultiSeriesSourceDescriptor>>>::typeName = "com.illumon.iris.web.shared.data.plot.MultiSeriesSourceDescriptor[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SeriesDescriptor>>>::typeName = "com.illumon.iris.web.shared.data.plot.SeriesDescriptor[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SourceDescriptor>>>::typeName = "com.illumon.iris.web.shared.data.plot.SourceDescriptor[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::Key>>>::typeName = "com.illumon.iris.web.shared.data.treetable.Key[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::TableDetails>>>::typeName = "com.illumon.iris.web.shared.data.treetable.TableDetails[]";
const boost::string_view AggregateTypeName<std::vector<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::treeTableRequest::TreeRequestOperation>>::typeName = "com.illumon.iris.web.shared.data.treetable.TreeTableRequest.TreeRequestOperation[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ConsoleServerAddress>>>::typeName = "com.illumon.iris.web.shared.ide.ConsoleServerAddress[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::VariableDefinition>>>::typeName = "com.illumon.iris.web.shared.ide.VariableDefinition[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::CompletionItem>>>::typeName = "com.illumon.iris.web.shared.ide.lsp.CompletionItem[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentContentChangeEvent>>>::typeName = "com.illumon.iris.web.shared.ide.lsp.TextDocumentContentChangeEvent[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextEdit>>>::typeName = "com.illumon.iris.web.shared.ide.lsp.TextEdit[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::metrics::MetricsLog>>>::typeName = "com.illumon.iris.web.shared.metrics.MetricsLog[]";
const boost::string_view AggregateTypeName<std::vector<double>>::typeName = "double[]";
const boost::string_view AggregateTypeName<std::vector<float>>::typeName = "float[]";
const boost::string_view AggregateTypeName<std::vector<int32_t>>::typeName = "int[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<std::vector<int32_t>>>>::typeName = "int[][]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean>>>::typeName = "java.lang.Boolean[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Double>>>::typeName = "java.lang.Double[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<std::string>>>::typeName = "java.lang.String[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<std::vector<std::shared_ptr<std::string>>>>>::typeName = "java.lang.String[][]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::math::BigDecimal>>>::typeName = "java.math.BigDecimal[]";
const boost::string_view AggregateTypeName<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::math::BigInteger>>>::typeName = "java.math.BigInteger[]";
const boost::string_view AggregateTypeName<std::vector<int64_t>>::typeName = "long[]";
const boost::string_view AggregateTypeName<std::vector<int16_t>>::typeName = "short[]";
namespace generated {
namespace com {
namespace illumon {
namespace iris {
namespace web {
namespace shared {
namespace batch {
const boost::string_view BatchTableRequest::typeName("com.illumon.iris.web.shared.batch.BatchTableRequest");
std::shared_ptr<BatchTableRequest> BatchTableRequest::create(std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::batchTableRequest::SerializedTableOps>>> ops) {
  return std::make_shared<BatchTableRequest>(Private(), std::move(ops));
}
BatchTableRequest::BatchTableRequest(Private, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::batchTableRequest::SerializedTableOps>>> ops)
  : ops_(std::move(ops))
  {
}
BatchTableRequest::~BatchTableRequest() = default;
void BatchTableRequest::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&ops_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> BatchTableRequest::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::batchTableRequest::SerializedTableOps>>> ops;
  da.read(&ops);
  return BatchTableRequest::create(std::move(ops));
}
namespace batchTableRequest {
const boost::string_view SerializedTableOps::typeName("com.illumon.iris.web.shared.batch.BatchTableRequest.SerializedTableOps");
std::shared_ptr<SerializedTableOps> SerializedTableOps::create(std::shared_ptr<std::vector<std::shared_ptr<std::string>>> dropColumns, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> viewColumns, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::HandleMapping> handles, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::SortDescriptor>>> sorts, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> conditions, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::FilterDescriptor>>> filters, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::CustomColumnDescriptor>>> customColumns, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::HeadOrTailDescriptor> headOrTail, bool isFlat, int32_t updateIntervalMs) {
  return std::make_shared<SerializedTableOps>(Private(), std::move(dropColumns), std::move(viewColumns), std::move(handles), std::move(sorts), std::move(conditions), std::move(filters), std::move(customColumns), std::move(headOrTail), isFlat, updateIntervalMs);
}
SerializedTableOps::SerializedTableOps(Private, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> dropColumns, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> viewColumns, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::HandleMapping> handles, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::SortDescriptor>>> sorts, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> conditions, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::FilterDescriptor>>> filters, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::CustomColumnDescriptor>>> customColumns, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::HeadOrTailDescriptor> headOrTail, bool isFlat, int32_t updateIntervalMs)
  : dropColumns_(std::move(dropColumns)), viewColumns_(std::move(viewColumns)), handles_(std::move(handles)), sorts_(std::move(sorts)), conditions_(std::move(conditions)), filters_(std::move(filters)), customColumns_(std::move(customColumns)), headOrTail_(std::move(headOrTail)), isFlat_(isFlat), updateIntervalMs_(updateIntervalMs)
  {
}
SerializedTableOps::~SerializedTableOps() = default;
void SerializedTableOps::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&dropColumns_);
  sa.write(&viewColumns_);
  sa.write(&handles_);
  sa.write(&sorts_);
  sa.write(&conditions_);
  sa.write(&filters_);
  sa.write(&customColumns_);
  sa.write(&headOrTail_);
  sa.write(&isFlat_);
  sa.write(&updateIntervalMs_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> SerializedTableOps::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> dropColumns;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> viewColumns;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::HandleMapping> handles;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::SortDescriptor>>> sorts;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> conditions;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::FilterDescriptor>>> filters;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::CustomColumnDescriptor>>> customColumns;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::HeadOrTailDescriptor> headOrTail;
  bool isFlat;
  int32_t updateIntervalMs;
  da.read(&dropColumns);
  da.read(&viewColumns);
  da.read(&handles);
  da.read(&sorts);
  da.read(&conditions);
  da.read(&filters);
  da.read(&customColumns);
  da.read(&headOrTail);
  da.read(&isFlat);
  da.read(&updateIntervalMs);
  return SerializedTableOps::create(std::move(dropColumns), std::move(viewColumns), std::move(handles), std::move(sorts), std::move(conditions), std::move(filters), std::move(customColumns), std::move(headOrTail), isFlat, updateIntervalMs);
}
}  // namespace batchTableRequest
const boost::string_view BatchTableResponse::typeName("com.illumon.iris.web.shared.batch.BatchTableResponse");
std::shared_ptr<BatchTableResponse> BatchTableResponse::create(std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> success, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> failedTableHandles, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> failureMessages) {
  return std::make_shared<BatchTableResponse>(Private(), std::move(success), std::move(failedTableHandles), std::move(failureMessages));
}
BatchTableResponse::BatchTableResponse(Private, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> success, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> failedTableHandles, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> failureMessages)
  : success_(std::move(success)), failedTableHandles_(std::move(failedTableHandles)), failureMessages_(std::move(failureMessages))
  {
}
BatchTableResponse::~BatchTableResponse() = default;
void BatchTableResponse::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&success_);
  sa.write(&failedTableHandles_);
  sa.write(&failureMessages_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> BatchTableResponse::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> success;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> failedTableHandles;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> failureMessages;
  da.read(&success);
  da.read(&failedTableHandles);
  da.read(&failureMessages);
  return BatchTableResponse::create(std::move(success), std::move(failedTableHandles), std::move(failureMessages));
}
namespace aggregates {
const boost::string_view AggregateDescriptor::typeName("com.illumon.iris.web.shared.batch.aggregates.AggregateDescriptor");
std::shared_ptr<AggregateDescriptor> AggregateDescriptor::create(std::shared_ptr<std::string> aggregateType, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> matchPairs, std::shared_ptr<std::string> columnName, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::PercentileDescriptor> percentile) {
  return std::make_shared<AggregateDescriptor>(Private(), std::move(aggregateType), std::move(matchPairs), std::move(columnName), std::move(percentile));
}
AggregateDescriptor::AggregateDescriptor(Private, std::shared_ptr<std::string> aggregateType, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> matchPairs, std::shared_ptr<std::string> columnName, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::PercentileDescriptor> percentile)
  : aggregateType_(std::move(aggregateType)), matchPairs_(std::move(matchPairs)), columnName_(std::move(columnName)), percentile_(std::move(percentile))
  {
}
AggregateDescriptor::~AggregateDescriptor() = default;
void AggregateDescriptor::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&aggregateType_);
  sa.write(&matchPairs_);
  sa.write(&columnName_);
  sa.write(&percentile_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> AggregateDescriptor::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::string> aggregateType;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> matchPairs;
  std::shared_ptr<std::string> columnName;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::PercentileDescriptor> percentile;
  da.read(&aggregateType);
  da.read(&matchPairs);
  da.read(&columnName);
  da.read(&percentile);
  return AggregateDescriptor::create(std::move(aggregateType), std::move(matchPairs), std::move(columnName), std::move(percentile));
}
const boost::string_view ComboAggregateDescriptor::typeName("com.illumon.iris.web.shared.batch.aggregates.ComboAggregateDescriptor");
std::shared_ptr<ComboAggregateDescriptor> ComboAggregateDescriptor::create(std::shared_ptr<std::string> aggregateStrategy, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::AggregateDescriptor>>> aggregates, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> groupByColumns, bool forceCombo) {
  return std::make_shared<ComboAggregateDescriptor>(Private(), std::move(aggregateStrategy), std::move(aggregates), std::move(groupByColumns), forceCombo);
}
ComboAggregateDescriptor::ComboAggregateDescriptor(Private, std::shared_ptr<std::string> aggregateStrategy, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::AggregateDescriptor>>> aggregates, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> groupByColumns, bool forceCombo)
  : aggregateStrategy_(std::move(aggregateStrategy)), aggregates_(std::move(aggregates)), groupByColumns_(std::move(groupByColumns)), forceCombo_(forceCombo)
  {
}
ComboAggregateDescriptor::~ComboAggregateDescriptor() = default;
void ComboAggregateDescriptor::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&aggregateStrategy_);
  sa.write(&aggregates_);
  sa.write(&groupByColumns_);
  sa.write(&forceCombo_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> ComboAggregateDescriptor::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::string> aggregateStrategy;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::batch::aggregates::AggregateDescriptor>>> aggregates;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> groupByColumns;
  bool forceCombo;
  da.read(&aggregateStrategy);
  da.read(&aggregates);
  da.read(&groupByColumns);
  da.read(&forceCombo);
  return ComboAggregateDescriptor::create(std::move(aggregateStrategy), std::move(aggregates), std::move(groupByColumns), forceCombo);
}
const boost::string_view PercentileDescriptor::typeName("com.illumon.iris.web.shared.batch.aggregates.PercentileDescriptor");
std::shared_ptr<PercentileDescriptor> PercentileDescriptor::create(double percentile, bool avgMedian) {
  return std::make_shared<PercentileDescriptor>(Private(), percentile, avgMedian);
}
PercentileDescriptor::PercentileDescriptor(Private, double percentile, bool avgMedian)
  : percentile_(percentile), avgMedian_(avgMedian)
  {
}
PercentileDescriptor::~PercentileDescriptor() = default;
void PercentileDescriptor::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&percentile_);
  sa.write(&avgMedian_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> PercentileDescriptor::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  double percentile;
  bool avgMedian;
  da.read(&percentile);
  da.read(&avgMedian);
  return PercentileDescriptor::create(percentile, avgMedian);
}
}  // namespace aggregates
}  // namespace batch
namespace cmd {
const boost::string_view ConnectionSuccess::typeName("com.illumon.iris.web.shared.cmd.ConnectionSuccess");
std::shared_ptr<ConnectionSuccess> ConnectionSuccess::create(std::shared_ptr<std::string> token, int32_t connectionId) {
  return std::make_shared<ConnectionSuccess>(Private(), std::move(token), connectionId);
}
ConnectionSuccess::ConnectionSuccess(Private, std::shared_ptr<std::string> token, int32_t connectionId)
  : token_(std::move(token)), connectionId_(connectionId)
  {
}
ConnectionSuccess::~ConnectionSuccess() = default;
void ConnectionSuccess::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&token_);
  sa.write(&connectionId_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> ConnectionSuccess::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::string> token;
  int32_t connectionId;
  da.read(&token);
  da.read(&connectionId);
  return ConnectionSuccess::create(std::move(token), connectionId);
}
const boost::string_view ServerReplyHandle::typeName("com.illumon.iris.web.shared.cmd.ServerReplyHandle");
std::shared_ptr<ServerReplyHandle> ServerReplyHandle::create() {
  return std::make_shared<ServerReplyHandle>(Private());
}
ServerReplyHandle::ServerReplyHandle(Private)
  
  {
}
ServerReplyHandle::~ServerReplyHandle() = default;
void ServerReplyHandle::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> ServerReplyHandle::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  return ServerReplyHandle::create();
}
const boost::string_view RequestId::typeName("com.illumon.iris.web.shared.cmd.RequestId");
std::shared_ptr<RequestId> RequestId::create(int32_t clientId) {
  return std::make_shared<RequestId>(Private(), clientId);
}
RequestId::RequestId(Private, int32_t clientId)
  : deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::ServerReplyHandle(Private()), clientId_(clientId)
  {
}
RequestId::~RequestId() = default;
void RequestId::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&clientId_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> RequestId::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  int32_t clientId;
  da.read(&clientId);
  return RequestId::create(clientId);
}
}  // namespace cmd
namespace data {
const boost::string_view BusinessCalendarDescriptor::typeName("com.illumon.iris.web.shared.data.BusinessCalendarDescriptor");
std::shared_ptr<BusinessCalendarDescriptor> BusinessCalendarDescriptor::create(std::shared_ptr<std::string> name, std::shared_ptr<std::string> timeZone, std::shared_ptr<std::vector<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::businessCalendarDescriptor::DayOfWeek>> businessDays, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::BusinessPeriod>>> businessPeriods, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Holiday>>> holidays) {
  return std::make_shared<BusinessCalendarDescriptor>(Private(), std::move(name), std::move(timeZone), std::move(businessDays), std::move(businessPeriods), std::move(holidays));
}
BusinessCalendarDescriptor::BusinessCalendarDescriptor(Private, std::shared_ptr<std::string> name, std::shared_ptr<std::string> timeZone, std::shared_ptr<std::vector<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::businessCalendarDescriptor::DayOfWeek>> businessDays, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::BusinessPeriod>>> businessPeriods, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Holiday>>> holidays)
  : name_(std::move(name)), timeZone_(std::move(timeZone)), businessDays_(std::move(businessDays)), businessPeriods_(std::move(businessPeriods)), holidays_(std::move(holidays))
  {
}
BusinessCalendarDescriptor::~BusinessCalendarDescriptor() = default;
void BusinessCalendarDescriptor::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&name_);
  sa.write(&timeZone_);
  sa.write(&businessDays_);
  sa.write(&businessPeriods_);
  sa.write(&holidays_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> BusinessCalendarDescriptor::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::string> name;
  std::shared_ptr<std::string> timeZone;
  std::shared_ptr<std::vector<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::businessCalendarDescriptor::DayOfWeek>> businessDays;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::BusinessPeriod>>> businessPeriods;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Holiday>>> holidays;
  da.read(&name);
  da.read(&timeZone);
  da.read(&businessDays);
  da.read(&businessPeriods);
  da.read(&holidays);
  return BusinessCalendarDescriptor::create(std::move(name), std::move(timeZone), std::move(businessDays), std::move(businessPeriods), std::move(holidays));
}
const boost::string_view BusinessPeriod::typeName("com.illumon.iris.web.shared.data.BusinessPeriod");
std::shared_ptr<BusinessPeriod> BusinessPeriod::create(std::shared_ptr<std::string> open, std::shared_ptr<std::string> close) {
  return std::make_shared<BusinessPeriod>(Private(), std::move(open), std::move(close));
}
BusinessPeriod::BusinessPeriod(Private, std::shared_ptr<std::string> open, std::shared_ptr<std::string> close)
  : open_(std::move(open)), close_(std::move(close))
  {
}
BusinessPeriod::~BusinessPeriod() = default;
void BusinessPeriod::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&open_);
  sa.write(&close_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> BusinessPeriod::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::string> open;
  std::shared_ptr<std::string> close;
  da.read(&open);
  da.read(&close);
  return BusinessPeriod::create(std::move(open), std::move(close));
}
const boost::string_view Catalog::typeName("com.illumon.iris.web.shared.data.Catalog");
std::shared_ptr<Catalog> Catalog::create(std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::catalog::Table>>> tables) {
  return std::make_shared<Catalog>(Private(), std::move(tables));
}
Catalog::Catalog(Private, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::catalog::Table>>> tables)
  : tables_(std::move(tables))
  {
}
Catalog::~Catalog() = default;
void Catalog::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&tables_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> Catalog::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::catalog::Table>>> tables;
  da.read(&tables);
  return Catalog::create(std::move(tables));
}
namespace catalog {
const boost::string_view Table::typeName("com.illumon.iris.web.shared.data.Catalog.Table");
std::shared_ptr<Table> Table::create(std::shared_ptr<std::string> namespaceSet, std::shared_ptr<std::string> nameSpace, std::shared_ptr<std::string> tableName) {
  return std::make_shared<Table>(Private(), std::move(namespaceSet), std::move(nameSpace), std::move(tableName));
}
Table::Table(Private, std::shared_ptr<std::string> namespaceSet, std::shared_ptr<std::string> nameSpace, std::shared_ptr<std::string> tableName)
  : namespaceSet_(std::move(namespaceSet)), nameSpace_(std::move(nameSpace)), tableName_(std::move(tableName))
  {
}
Table::~Table() = default;
void Table::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&namespaceSet_);
  sa.write(&nameSpace_);
  sa.write(&tableName_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> Table::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::string> namespaceSet;
  std::shared_ptr<std::string> nameSpace;
  std::shared_ptr<std::string> tableName;
  da.read(&namespaceSet);
  da.read(&nameSpace);
  da.read(&tableName);
  return Table::create(std::move(namespaceSet), std::move(nameSpace), std::move(tableName));
}
}  // namespace catalog
const boost::string_view ChallengeResponseData::typeName("com.illumon.iris.web.shared.data.ChallengeResponseData");
std::shared_ptr<ChallengeResponseData> ChallengeResponseData::create(std::shared_ptr<std::vector<int8_t>> nonce, std::shared_ptr<std::string> algorithm) {
  return std::make_shared<ChallengeResponseData>(Private(), std::move(nonce), std::move(algorithm));
}
ChallengeResponseData::ChallengeResponseData(Private, std::shared_ptr<std::vector<int8_t>> nonce, std::shared_ptr<std::string> algorithm)
  : nonce_(std::move(nonce)), algorithm_(std::move(algorithm))
  {
}
ChallengeResponseData::~ChallengeResponseData() = default;
void ChallengeResponseData::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&nonce_);
  sa.write(&algorithm_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> ChallengeResponseData::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::vector<int8_t>> nonce;
  std::shared_ptr<std::string> algorithm;
  da.read(&nonce);
  da.read(&algorithm);
  return ChallengeResponseData::create(std::move(nonce), std::move(algorithm));
}
const boost::string_view ColumnDefinition::typeName("com.illumon.iris.web.shared.data.ColumnDefinition");
std::shared_ptr<ColumnDefinition> ColumnDefinition::create(int32_t columnIndex, std::shared_ptr<std::string> name, std::shared_ptr<std::string> type, bool isStyleColumn, bool isFormatColumn, bool isNumberFormatColumn, bool isPartitionColumn, bool isRollupHierarchicalColumn, bool forRow, std::shared_ptr<std::string> forColumn, std::shared_ptr<std::string> description) {
  return std::make_shared<ColumnDefinition>(Private(), columnIndex, std::move(name), std::move(type), isStyleColumn, isFormatColumn, isNumberFormatColumn, isPartitionColumn, isRollupHierarchicalColumn, forRow, std::move(forColumn), std::move(description));
}
ColumnDefinition::ColumnDefinition(Private, int32_t columnIndex, std::shared_ptr<std::string> name, std::shared_ptr<std::string> type, bool isStyleColumn, bool isFormatColumn, bool isNumberFormatColumn, bool isPartitionColumn, bool isRollupHierarchicalColumn, bool forRow, std::shared_ptr<std::string> forColumn, std::shared_ptr<std::string> description)
  : columnIndex_(columnIndex), name_(std::move(name)), type_(std::move(type)), isStyleColumn_(isStyleColumn), isFormatColumn_(isFormatColumn), isNumberFormatColumn_(isNumberFormatColumn), isPartitionColumn_(isPartitionColumn), isRollupHierarchicalColumn_(isRollupHierarchicalColumn), forRow_(forRow), forColumn_(std::move(forColumn)), description_(std::move(description))
  {
}
ColumnDefinition::~ColumnDefinition() = default;
void ColumnDefinition::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&columnIndex_);
  sa.write(&name_);
  sa.write(&type_);
  sa.write(&isStyleColumn_);
  sa.write(&isFormatColumn_);
  sa.write(&isNumberFormatColumn_);
  sa.write(&isPartitionColumn_);
  sa.write(&isRollupHierarchicalColumn_);
  sa.write(&forRow_);
  sa.write(&forColumn_);
  sa.write(&description_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> ColumnDefinition::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  int32_t columnIndex;
  std::shared_ptr<std::string> name;
  std::shared_ptr<std::string> type;
  bool isStyleColumn;
  bool isFormatColumn;
  bool isNumberFormatColumn;
  bool isPartitionColumn;
  bool isRollupHierarchicalColumn;
  bool forRow;
  std::shared_ptr<std::string> forColumn;
  std::shared_ptr<std::string> description;
  da.read(&columnIndex);
  da.read(&name);
  da.read(&type);
  da.read(&isStyleColumn);
  da.read(&isFormatColumn);
  da.read(&isNumberFormatColumn);
  da.read(&isPartitionColumn);
  da.read(&isRollupHierarchicalColumn);
  da.read(&forRow);
  da.read(&forColumn);
  da.read(&description);
  return ColumnDefinition::create(columnIndex, std::move(name), std::move(type), isStyleColumn, isFormatColumn, isNumberFormatColumn, isPartitionColumn, isRollupHierarchicalColumn, forRow, std::move(forColumn), std::move(description));
}
const boost::string_view ColumnHolder::typeName("com.illumon.iris.web.shared.data.ColumnHolder");
std::shared_ptr<ColumnHolder> ColumnHolder::create(std::shared_ptr<std::string> name, std::shared_ptr<std::string> type, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData> columnData, bool grouped) {
  return std::make_shared<ColumnHolder>(Private(), std::move(name), std::move(type), std::move(columnData), grouped);
}
ColumnHolder::ColumnHolder(Private, std::shared_ptr<std::string> name, std::shared_ptr<std::string> type, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData> columnData, bool grouped)
  : name_(std::move(name)), type_(std::move(type)), columnData_(std::move(columnData)), grouped_(grouped)
  {
}
ColumnHolder::~ColumnHolder() = default;
void ColumnHolder::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&name_);
  sa.write(&type_);
  sa.write(&columnData_);
  sa.write(&grouped_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> ColumnHolder::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::string> name;
  std::shared_ptr<std::string> type;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData> columnData;
  bool grouped;
  da.read(&name);
  da.read(&type);
  da.read(&columnData);
  da.read(&grouped);
  return ColumnHolder::create(std::move(name), std::move(type), std::move(columnData), grouped);
}
const boost::string_view ColumnStatistics::typeName("com.illumon.iris.web.shared.data.ColumnStatistics");
std::shared_ptr<ColumnStatistics> ColumnStatistics::create(deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columnStatistics::ColumnType type, int64_t count, int32_t numUnique, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> uniqueKeys, std::shared_ptr<std::vector<int64_t>> uniqueValues, double sum, double absSum, double min, double max, double absMin, double absMax) {
  return std::make_shared<ColumnStatistics>(Private(), type, count, numUnique, std::move(uniqueKeys), std::move(uniqueValues), sum, absSum, min, max, absMin, absMax);
}
ColumnStatistics::ColumnStatistics(Private, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columnStatistics::ColumnType type, int64_t count, int32_t numUnique, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> uniqueKeys, std::shared_ptr<std::vector<int64_t>> uniqueValues, double sum, double absSum, double min, double max, double absMin, double absMax)
  : type_(type), count_(count), numUnique_(numUnique), uniqueKeys_(std::move(uniqueKeys)), uniqueValues_(std::move(uniqueValues)), sum_(sum), absSum_(absSum), min_(min), max_(max), absMin_(absMin), absMax_(absMax)
  {
}
ColumnStatistics::~ColumnStatistics() = default;
void ColumnStatistics::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&type_);
  sa.write(&count_);
  sa.write(&numUnique_);
  sa.write(&uniqueKeys_);
  sa.write(&uniqueValues_);
  sa.write(&sum_);
  sa.write(&absSum_);
  sa.write(&min_);
  sa.write(&max_);
  sa.write(&absMin_);
  sa.write(&absMax_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> ColumnStatistics::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columnStatistics::ColumnType type;
  int64_t count;
  int32_t numUnique;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> uniqueKeys;
  std::shared_ptr<std::vector<int64_t>> uniqueValues;
  double sum;
  double absSum;
  double min;
  double max;
  double absMin;
  double absMax;
  da.read(&type);
  da.read(&count);
  da.read(&numUnique);
  da.read(&uniqueKeys);
  da.read(&uniqueValues);
  da.read(&sum);
  da.read(&absSum);
  da.read(&min);
  da.read(&max);
  da.read(&absMin);
  da.read(&absMax);
  return ColumnStatistics::create(type, count, numUnique, std::move(uniqueKeys), std::move(uniqueValues), sum, absSum, min, max, absMin, absMax);
}
const boost::string_view ColumnValue::typeName("com.illumon.iris.web.shared.data.ColumnValue");
std::shared_ptr<ColumnValue> ColumnValue::create(int32_t columnId, std::shared_ptr<std::string> value) {
  return std::make_shared<ColumnValue>(Private(), columnId, std::move(value));
}
ColumnValue::ColumnValue(Private, int32_t columnId, std::shared_ptr<std::string> value)
  : columnId_(columnId), value_(std::move(value))
  {
}
ColumnValue::~ColumnValue() = default;
void ColumnValue::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&columnId_);
  sa.write(&value_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> ColumnValue::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  int32_t columnId;
  std::shared_ptr<std::string> value;
  da.read(&columnId);
  da.read(&value);
  return ColumnValue::create(columnId, std::move(value));
}
const boost::string_view ConnectToken::typeName("com.illumon.iris.web.shared.data.ConnectToken");
std::shared_ptr<ConnectToken> ConnectToken::create(std::shared_ptr<std::vector<int8_t>> bytes) {
  return std::make_shared<ConnectToken>(Private(), std::move(bytes));
}
ConnectToken::ConnectToken(Private, std::shared_ptr<std::vector<int8_t>> bytes)
  : bytes_(std::move(bytes))
  {
}
ConnectToken::~ConnectToken() = default;
void ConnectToken::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&bytes_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> ConnectToken::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::vector<int8_t>> bytes;
  da.read(&bytes);
  return ConnectToken::create(std::move(bytes));
}
const boost::string_view CustomColumnDescriptor::typeName("com.illumon.iris.web.shared.data.CustomColumnDescriptor");
std::shared_ptr<CustomColumnDescriptor> CustomColumnDescriptor::create(std::shared_ptr<std::string> expression) {
  return std::make_shared<CustomColumnDescriptor>(Private(), std::move(expression));
}
CustomColumnDescriptor::CustomColumnDescriptor(Private, std::shared_ptr<std::string> expression)
  : expression_(std::move(expression))
  {
}
CustomColumnDescriptor::~CustomColumnDescriptor() = default;
void CustomColumnDescriptor::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&expression_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> CustomColumnDescriptor::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::string> expression;
  da.read(&expression);
  return CustomColumnDescriptor::create(std::move(expression));
}
const boost::string_view DeltaUpdates::typeName("com.illumon.iris.web.shared.data.DeltaUpdates");
std::shared_ptr<DeltaUpdates> DeltaUpdates::create(int64_t deltaSequence, int64_t firstStep, int64_t lastStep, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> added, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> removed, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ShiftedRange>>> shiftedRanges, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> includedAdditions, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::deltaUpdates::ColumnAdditions>>> serializedAdditions, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::deltaUpdates::ColumnModifications>>> serializedModifications) {
  return std::make_shared<DeltaUpdates>(Private(), deltaSequence, firstStep, lastStep, std::move(added), std::move(removed), std::move(shiftedRanges), std::move(includedAdditions), std::move(serializedAdditions), std::move(serializedModifications));
}
DeltaUpdates::DeltaUpdates(Private, int64_t deltaSequence, int64_t firstStep, int64_t lastStep, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> added, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> removed, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ShiftedRange>>> shiftedRanges, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> includedAdditions, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::deltaUpdates::ColumnAdditions>>> serializedAdditions, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::deltaUpdates::ColumnModifications>>> serializedModifications)
  : deltaSequence_(deltaSequence), firstStep_(firstStep), lastStep_(lastStep), added_(std::move(added)), removed_(std::move(removed)), shiftedRanges_(std::move(shiftedRanges)), includedAdditions_(std::move(includedAdditions)), serializedAdditions_(std::move(serializedAdditions)), serializedModifications_(std::move(serializedModifications))
  {
}
DeltaUpdates::~DeltaUpdates() = default;
void DeltaUpdates::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&deltaSequence_);
  sa.write(&firstStep_);
  sa.write(&lastStep_);
  sa.write(&added_);
  sa.write(&removed_);
  sa.write(&shiftedRanges_);
  sa.write(&includedAdditions_);
  sa.write(&serializedAdditions_);
  sa.write(&serializedModifications_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> DeltaUpdates::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  int64_t deltaSequence;
  int64_t firstStep;
  int64_t lastStep;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> added;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> removed;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ShiftedRange>>> shiftedRanges;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> includedAdditions;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::deltaUpdates::ColumnAdditions>>> serializedAdditions;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::deltaUpdates::ColumnModifications>>> serializedModifications;
  da.read(&deltaSequence);
  da.read(&firstStep);
  da.read(&lastStep);
  da.read(&added);
  da.read(&removed);
  da.read(&shiftedRanges);
  da.read(&includedAdditions);
  da.read(&serializedAdditions);
  da.read(&serializedModifications);
  return DeltaUpdates::create(deltaSequence, firstStep, lastStep, std::move(added), std::move(removed), std::move(shiftedRanges), std::move(includedAdditions), std::move(serializedAdditions), std::move(serializedModifications));
}
namespace deltaUpdates {
const boost::string_view ColumnAdditions::typeName("com.illumon.iris.web.shared.data.DeltaUpdates.ColumnAdditions");
std::shared_ptr<ColumnAdditions> ColumnAdditions::create(int32_t columnIndex, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData> values) {
  return std::make_shared<ColumnAdditions>(Private(), columnIndex, std::move(values));
}
ColumnAdditions::ColumnAdditions(Private, int32_t columnIndex, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData> values)
  : columnIndex_(columnIndex), values_(std::move(values))
  {
}
ColumnAdditions::~ColumnAdditions() = default;
void ColumnAdditions::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&columnIndex_);
  sa.write(&values_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> ColumnAdditions::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  int32_t columnIndex;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData> values;
  da.read(&columnIndex);
  da.read(&values);
  return ColumnAdditions::create(columnIndex, std::move(values));
}
const boost::string_view ColumnModifications::typeName("com.illumon.iris.web.shared.data.DeltaUpdates.ColumnModifications");
std::shared_ptr<ColumnModifications> ColumnModifications::create(int32_t columnIndex, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> rowsIncluded, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> rowsModified, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData> values) {
  return std::make_shared<ColumnModifications>(Private(), columnIndex, std::move(rowsIncluded), std::move(rowsModified), std::move(values));
}
ColumnModifications::ColumnModifications(Private, int32_t columnIndex, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> rowsIncluded, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> rowsModified, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData> values)
  : columnIndex_(columnIndex), rowsIncluded_(std::move(rowsIncluded)), rowsModified_(std::move(rowsModified)), values_(std::move(values))
  {
}
ColumnModifications::~ColumnModifications() = default;
void ColumnModifications::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&columnIndex_);
  sa.write(&rowsIncluded_);
  sa.write(&rowsModified_);
  sa.write(&values_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> ColumnModifications::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  int32_t columnIndex;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> rowsIncluded;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> rowsModified;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData> values;
  da.read(&columnIndex);
  da.read(&rowsIncluded);
  da.read(&rowsModified);
  da.read(&values);
  return ColumnModifications::create(columnIndex, std::move(rowsIncluded), std::move(rowsModified), std::move(values));
}
}  // namespace deltaUpdates
const boost::string_view FilterDescriptor::typeName("com.illumon.iris.web.shared.data.FilterDescriptor");
std::shared_ptr<FilterDescriptor> FilterDescriptor::create(deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::filterDescriptor::FilterOperation operation, std::shared_ptr<std::string> value, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::filterDescriptor::ValueType type, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::FilterDescriptor>>> children) {
  return std::make_shared<FilterDescriptor>(Private(), operation, std::move(value), type, std::move(children));
}
FilterDescriptor::FilterDescriptor(Private, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::filterDescriptor::FilterOperation operation, std::shared_ptr<std::string> value, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::filterDescriptor::ValueType type, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::FilterDescriptor>>> children)
  : operation_(operation), value_(std::move(value)), type_(type), children_(std::move(children))
  {
}
FilterDescriptor::~FilterDescriptor() = default;
void FilterDescriptor::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&operation_);
  sa.write(&value_);
  sa.write(&type_);
  sa.write(&children_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> FilterDescriptor::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::filterDescriptor::FilterOperation operation;
  std::shared_ptr<std::string> value;
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::filterDescriptor::ValueType type;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::FilterDescriptor>>> children;
  da.read(&operation);
  da.read(&value);
  da.read(&type);
  da.read(&children);
  return FilterDescriptor::create(operation, std::move(value), type, std::move(children));
}
const boost::string_view HandleMapping::typeName("com.illumon.iris.web.shared.data.HandleMapping");
std::shared_ptr<HandleMapping> HandleMapping::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> source, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> newId) {
  return std::make_shared<HandleMapping>(Private(), std::move(source), std::move(newId));
}
HandleMapping::HandleMapping(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> source, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> newId)
  : source_(std::move(source)), newId_(std::move(newId))
  {
}
HandleMapping::~HandleMapping() = default;
void HandleMapping::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&source_);
  sa.write(&newId_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> HandleMapping::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> source;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> newId;
  da.read(&source);
  da.read(&newId);
  return HandleMapping::create(std::move(source), std::move(newId));
}
const boost::string_view HeadOrTailDescriptor::typeName("com.illumon.iris.web.shared.data.HeadOrTailDescriptor");
std::shared_ptr<HeadOrTailDescriptor> HeadOrTailDescriptor::create(bool head, int64_t rows) {
  return std::make_shared<HeadOrTailDescriptor>(Private(), head, rows);
}
HeadOrTailDescriptor::HeadOrTailDescriptor(Private, bool head, int64_t rows)
  : head_(head), rows_(rows)
  {
}
HeadOrTailDescriptor::~HeadOrTailDescriptor() = default;
void HeadOrTailDescriptor::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&head_);
  sa.write(&rows_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> HeadOrTailDescriptor::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  bool head;
  int64_t rows;
  da.read(&head);
  da.read(&rows);
  return HeadOrTailDescriptor::create(head, rows);
}
const boost::string_view Holiday::typeName("com.illumon.iris.web.shared.data.Holiday");
std::shared_ptr<Holiday> Holiday::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LocalDate> date, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::BusinessPeriod>>> businessPeriods) {
  return std::make_shared<Holiday>(Private(), std::move(date), std::move(businessPeriods));
}
Holiday::Holiday(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LocalDate> date, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::BusinessPeriod>>> businessPeriods)
  : date_(std::move(date)), businessPeriods_(std::move(businessPeriods))
  {
}
Holiday::~Holiday() = default;
void Holiday::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&date_);
  sa.write(&businessPeriods_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> Holiday::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LocalDate> date;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::BusinessPeriod>>> businessPeriods;
  da.read(&date);
  da.read(&businessPeriods);
  return Holiday::create(std::move(date), std::move(businessPeriods));
}
const boost::string_view InitialTableDefinition::typeName("com.illumon.iris.web.shared.data.InitialTableDefinition");
std::shared_ptr<InitialTableDefinition> InitialTableDefinition::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableDefinition> definition, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> id, int64_t size, bool inputTable, std::shared_ptr<std::string> totalsTableConfig, bool isFlat, bool isPreemptive, std::shared_ptr<std::string> treeHierarchicalColumnName, std::shared_ptr<std::string> description, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RollupDefinition> rollupDefinition, std::shared_ptr<std::string> pluginName) {
  return std::make_shared<InitialTableDefinition>(Private(), std::move(definition), std::move(id), size, inputTable, std::move(totalsTableConfig), isFlat, isPreemptive, std::move(treeHierarchicalColumnName), std::move(description), std::move(rollupDefinition), std::move(pluginName));
}
InitialTableDefinition::InitialTableDefinition(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableDefinition> definition, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> id, int64_t size, bool inputTable, std::shared_ptr<std::string> totalsTableConfig, bool isFlat, bool isPreemptive, std::shared_ptr<std::string> treeHierarchicalColumnName, std::shared_ptr<std::string> description, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RollupDefinition> rollupDefinition, std::shared_ptr<std::string> pluginName)
  : definition_(std::move(definition)), id_(std::move(id)), size_(size), inputTable_(inputTable), totalsTableConfig_(std::move(totalsTableConfig)), isFlat_(isFlat), isPreemptive_(isPreemptive), treeHierarchicalColumnName_(std::move(treeHierarchicalColumnName)), description_(std::move(description)), rollupDefinition_(std::move(rollupDefinition)), pluginName_(std::move(pluginName))
  {
}
InitialTableDefinition::~InitialTableDefinition() = default;
void InitialTableDefinition::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&definition_);
  sa.write(&id_);
  sa.write(&size_);
  sa.write(&inputTable_);
  sa.write(&totalsTableConfig_);
  sa.write(&isFlat_);
  sa.write(&isPreemptive_);
  sa.write(&treeHierarchicalColumnName_);
  sa.write(&description_);
  sa.write(&rollupDefinition_);
  sa.write(&pluginName_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> InitialTableDefinition::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableDefinition> definition;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> id;
  int64_t size;
  bool inputTable;
  std::shared_ptr<std::string> totalsTableConfig;
  bool isFlat;
  bool isPreemptive;
  std::shared_ptr<std::string> treeHierarchicalColumnName;
  std::shared_ptr<std::string> description;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RollupDefinition> rollupDefinition;
  std::shared_ptr<std::string> pluginName;
  da.read(&definition);
  da.read(&id);
  da.read(&size);
  da.read(&inputTable);
  da.read(&totalsTableConfig);
  da.read(&isFlat);
  da.read(&isPreemptive);
  da.read(&treeHierarchicalColumnName);
  da.read(&description);
  da.read(&rollupDefinition);
  da.read(&pluginName);
  return InitialTableDefinition::create(std::move(definition), std::move(id), size, inputTable, std::move(totalsTableConfig), isFlat, isPreemptive, std::move(treeHierarchicalColumnName), std::move(description), std::move(rollupDefinition), std::move(pluginName));
}
const boost::string_view InputTableDefinition::typeName("com.illumon.iris.web.shared.data.InputTableDefinition");
std::shared_ptr<InputTableDefinition> InputTableDefinition::create(std::shared_ptr<std::vector<std::shared_ptr<std::string>>> keys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> values) {
  return std::make_shared<InputTableDefinition>(Private(), std::move(keys), std::move(values));
}
InputTableDefinition::InputTableDefinition(Private, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> keys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> values)
  : keys_(std::move(keys)), values_(std::move(values))
  {
}
InputTableDefinition::~InputTableDefinition() = default;
void InputTableDefinition::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&keys_);
  sa.write(&values_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> InputTableDefinition::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> keys;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> values;
  da.read(&keys);
  da.read(&values);
  return InputTableDefinition::create(std::move(keys), std::move(values));
}
const boost::string_view JoinDescriptor::typeName("com.illumon.iris.web.shared.data.JoinDescriptor");
std::shared_ptr<JoinDescriptor> JoinDescriptor::create(deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::joinDescriptor::JoinType joinType, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> leftTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> rightTableHandle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnsToMatch, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnsToAdd) {
  return std::make_shared<JoinDescriptor>(Private(), joinType, std::move(leftTableHandle), std::move(rightTableHandle), std::move(columnsToMatch), std::move(columnsToAdd));
}
JoinDescriptor::JoinDescriptor(Private, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::joinDescriptor::JoinType joinType, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> leftTableHandle, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> rightTableHandle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnsToMatch, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnsToAdd)
  : joinType_(joinType), leftTableHandle_(std::move(leftTableHandle)), rightTableHandle_(std::move(rightTableHandle)), columnsToMatch_(std::move(columnsToMatch)), columnsToAdd_(std::move(columnsToAdd))
  {
}
JoinDescriptor::~JoinDescriptor() = default;
void JoinDescriptor::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&joinType_);
  sa.write(&leftTableHandle_);
  sa.write(&rightTableHandle_);
  sa.write(&columnsToMatch_);
  sa.write(&columnsToAdd_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> JoinDescriptor::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::joinDescriptor::JoinType joinType;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> leftTableHandle;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> rightTableHandle;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnsToMatch;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnsToAdd;
  da.read(&joinType);
  da.read(&leftTableHandle);
  da.read(&rightTableHandle);
  da.read(&columnsToMatch);
  da.read(&columnsToAdd);
  return JoinDescriptor::create(joinType, std::move(leftTableHandle), std::move(rightTableHandle), std::move(columnsToMatch), std::move(columnsToAdd));
}
const boost::string_view LocalDate::typeName("com.illumon.iris.web.shared.data.LocalDate");
std::shared_ptr<LocalDate> LocalDate::create(int32_t year, int8_t monthValue, int8_t dayOfMonth) {
  return std::make_shared<LocalDate>(Private(), year, monthValue, dayOfMonth);
}
LocalDate::LocalDate(Private, int32_t year, int8_t monthValue, int8_t dayOfMonth)
  : year_(year), monthValue_(monthValue), dayOfMonth_(dayOfMonth)
  {
}
LocalDate::~LocalDate() = default;
void LocalDate::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&year_);
  sa.write(&monthValue_);
  sa.write(&dayOfMonth_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> LocalDate::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  int32_t year;
  int8_t monthValue;
  int8_t dayOfMonth;
  da.read(&year);
  da.read(&monthValue);
  da.read(&dayOfMonth);
  return LocalDate::create(year, monthValue, dayOfMonth);
}
const boost::string_view LocalTime::typeName("com.illumon.iris.web.shared.data.LocalTime");
std::shared_ptr<LocalTime> LocalTime::create(int8_t hour, int8_t minute, int8_t second, int32_t nano) {
  return std::make_shared<LocalTime>(Private(), hour, minute, second, nano);
}
LocalTime::LocalTime(Private, int8_t hour, int8_t minute, int8_t second, int32_t nano)
  : hour_(hour), minute_(minute), second_(second), nano_(nano)
  {
}
LocalTime::~LocalTime() = default;
void LocalTime::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&hour_);
  sa.write(&minute_);
  sa.write(&second_);
  sa.write(&nano_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> LocalTime::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  int8_t hour;
  int8_t minute;
  int8_t second;
  int32_t nano;
  da.read(&hour);
  da.read(&minute);
  da.read(&second);
  da.read(&nano);
  return LocalTime::create(hour, minute, second, nano);
}
const boost::string_view LogItem::typeName("com.illumon.iris.web.shared.data.LogItem");
std::shared_ptr<LogItem> LogItem::create(double micros, std::shared_ptr<std::string> logLevel, std::shared_ptr<std::string> message) {
  return std::make_shared<LogItem>(Private(), micros, std::move(logLevel), std::move(message));
}
LogItem::LogItem(Private, double micros, std::shared_ptr<std::string> logLevel, std::shared_ptr<std::string> message)
  : micros_(micros), logLevel_(std::move(logLevel)), message_(std::move(message))
  {
}
LogItem::~LogItem() = default;
void LogItem::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&micros_);
  sa.write(&logLevel_);
  sa.write(&message_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> LogItem::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  double micros;
  std::shared_ptr<std::string> logLevel;
  std::shared_ptr<std::string> message;
  da.read(&micros);
  da.read(&logLevel);
  da.read(&message);
  return LogItem::create(micros, std::move(logLevel), std::move(message));
}
const boost::string_view QueryConfig::typeName("com.illumon.iris.web.shared.data.QueryConfig");
std::shared_ptr<QueryConfig> QueryConfig::create(int64_t serial, std::shared_ptr<std::string> status, std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<std::string>>>>> objects, std::shared_ptr<std::string> fullStackTrace, bool isDisplayable, std::shared_ptr<std::string> name, std::shared_ptr<std::string> owner, std::shared_ptr<std::string> configurationType, bool enabled, double heapSize, std::shared_ptr<std::string> dbServerName, bool enableGcLogs, std::shared_ptr<std::string> envVars, double dataMemoryRatio, std::shared_ptr<std::string> jvmArgs, std::shared_ptr<std::string> extraClasspaths, std::shared_ptr<std::string> jvmProfile, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> adminGroups, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> viewerGroups, int32_t restartUsers, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> scheduling, int64_t timeout, std::shared_ptr<std::string> scriptLanguage, std::shared_ptr<std::string> scriptPath, std::shared_ptr<std::string> websocketUrl, std::shared_ptr<std::string> serviceId) {
  return std::make_shared<QueryConfig>(Private(), serial, std::move(status), std::move(objects), std::move(fullStackTrace), isDisplayable, std::move(name), std::move(owner), std::move(configurationType), enabled, heapSize, std::move(dbServerName), enableGcLogs, std::move(envVars), dataMemoryRatio, std::move(jvmArgs), std::move(extraClasspaths), std::move(jvmProfile), std::move(adminGroups), std::move(viewerGroups), restartUsers, std::move(scheduling), timeout, std::move(scriptLanguage), std::move(scriptPath), std::move(websocketUrl), std::move(serviceId));
}
QueryConfig::QueryConfig(Private, int64_t serial, std::shared_ptr<std::string> status, std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<std::string>>>>> objects, std::shared_ptr<std::string> fullStackTrace, bool isDisplayable, std::shared_ptr<std::string> name, std::shared_ptr<std::string> owner, std::shared_ptr<std::string> configurationType, bool enabled, double heapSize, std::shared_ptr<std::string> dbServerName, bool enableGcLogs, std::shared_ptr<std::string> envVars, double dataMemoryRatio, std::shared_ptr<std::string> jvmArgs, std::shared_ptr<std::string> extraClasspaths, std::shared_ptr<std::string> jvmProfile, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> adminGroups, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> viewerGroups, int32_t restartUsers, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> scheduling, int64_t timeout, std::shared_ptr<std::string> scriptLanguage, std::shared_ptr<std::string> scriptPath, std::shared_ptr<std::string> websocketUrl, std::shared_ptr<std::string> serviceId)
  : serial_(serial), status_(std::move(status)), objects_(std::move(objects)), fullStackTrace_(std::move(fullStackTrace)), isDisplayable_(isDisplayable), name_(std::move(name)), owner_(std::move(owner)), configurationType_(std::move(configurationType)), enabled_(enabled), heapSize_(heapSize), dbServerName_(std::move(dbServerName)), enableGcLogs_(enableGcLogs), envVars_(std::move(envVars)), dataMemoryRatio_(dataMemoryRatio), jvmArgs_(std::move(jvmArgs)), extraClasspaths_(std::move(extraClasspaths)), jvmProfile_(std::move(jvmProfile)), adminGroups_(std::move(adminGroups)), viewerGroups_(std::move(viewerGroups)), restartUsers_(restartUsers), scheduling_(std::move(scheduling)), timeout_(timeout), scriptLanguage_(std::move(scriptLanguage)), scriptPath_(std::move(scriptPath)), websocketUrl_(std::move(websocketUrl)), serviceId_(std::move(serviceId))
  {
}
QueryConfig::~QueryConfig() = default;
void QueryConfig::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&serial_);
  sa.write(&status_);
  sa.write(&objects_);
  sa.write(&fullStackTrace_);
  sa.write(&isDisplayable_);
  sa.write(&name_);
  sa.write(&owner_);
  sa.write(&configurationType_);
  sa.write(&enabled_);
  sa.write(&heapSize_);
  sa.write(&dbServerName_);
  sa.write(&enableGcLogs_);
  sa.write(&envVars_);
  sa.write(&dataMemoryRatio_);
  sa.write(&jvmArgs_);
  sa.write(&extraClasspaths_);
  sa.write(&jvmProfile_);
  sa.write(&adminGroups_);
  sa.write(&viewerGroups_);
  sa.write(&restartUsers_);
  sa.write(&scheduling_);
  sa.write(&timeout_);
  sa.write(&scriptLanguage_);
  sa.write(&scriptPath_);
  sa.write(&websocketUrl_);
  sa.write(&serviceId_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> QueryConfig::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  int64_t serial;
  std::shared_ptr<std::string> status;
  std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<std::string>>>>> objects;
  std::shared_ptr<std::string> fullStackTrace;
  bool isDisplayable;
  std::shared_ptr<std::string> name;
  std::shared_ptr<std::string> owner;
  std::shared_ptr<std::string> configurationType;
  bool enabled;
  double heapSize;
  std::shared_ptr<std::string> dbServerName;
  bool enableGcLogs;
  std::shared_ptr<std::string> envVars;
  double dataMemoryRatio;
  std::shared_ptr<std::string> jvmArgs;
  std::shared_ptr<std::string> extraClasspaths;
  std::shared_ptr<std::string> jvmProfile;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> adminGroups;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> viewerGroups;
  int32_t restartUsers;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> scheduling;
  int64_t timeout;
  std::shared_ptr<std::string> scriptLanguage;
  std::shared_ptr<std::string> scriptPath;
  std::shared_ptr<std::string> websocketUrl;
  std::shared_ptr<std::string> serviceId;
  da.read(&serial);
  da.read(&status);
  da.read(&objects);
  da.read(&fullStackTrace);
  da.read(&isDisplayable);
  da.read(&name);
  da.read(&owner);
  da.read(&configurationType);
  da.read(&enabled);
  da.read(&heapSize);
  da.read(&dbServerName);
  da.read(&enableGcLogs);
  da.read(&envVars);
  da.read(&dataMemoryRatio);
  da.read(&jvmArgs);
  da.read(&extraClasspaths);
  da.read(&jvmProfile);
  da.read(&adminGroups);
  da.read(&viewerGroups);
  da.read(&restartUsers);
  da.read(&scheduling);
  da.read(&timeout);
  da.read(&scriptLanguage);
  da.read(&scriptPath);
  da.read(&websocketUrl);
  da.read(&serviceId);
  return QueryConfig::create(serial, std::move(status), std::move(objects), std::move(fullStackTrace), isDisplayable, std::move(name), std::move(owner), std::move(configurationType), enabled, heapSize, std::move(dbServerName), enableGcLogs, std::move(envVars), dataMemoryRatio, std::move(jvmArgs), std::move(extraClasspaths), std::move(jvmProfile), std::move(adminGroups), std::move(viewerGroups), restartUsers, std::move(scheduling), timeout, std::move(scriptLanguage), std::move(scriptPath), std::move(websocketUrl), std::move(serviceId));
}
const boost::string_view QueryConstants::typeName("com.illumon.iris.web.shared.data.QueryConstants");
std::shared_ptr<QueryConstants> QueryConstants::create(double minHeapGb, double defaultMaxHeapGb, double minDataRatio, double maxDataRatio, double maxScriptCodeLength, double consoleDefaultHeap, double pqDefaultHeap, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> serverNames, std::shared_ptr<std::vector<double>> maxHeapServer) {
  return std::make_shared<QueryConstants>(Private(), minHeapGb, defaultMaxHeapGb, minDataRatio, maxDataRatio, maxScriptCodeLength, consoleDefaultHeap, pqDefaultHeap, std::move(serverNames), std::move(maxHeapServer));
}
QueryConstants::QueryConstants(Private, double minHeapGb, double defaultMaxHeapGb, double minDataRatio, double maxDataRatio, double maxScriptCodeLength, double consoleDefaultHeap, double pqDefaultHeap, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> serverNames, std::shared_ptr<std::vector<double>> maxHeapServer)
  : minHeapGb_(minHeapGb), defaultMaxHeapGb_(defaultMaxHeapGb), minDataRatio_(minDataRatio), maxDataRatio_(maxDataRatio), maxScriptCodeLength_(maxScriptCodeLength), consoleDefaultHeap_(consoleDefaultHeap), pqDefaultHeap_(pqDefaultHeap), serverNames_(std::move(serverNames)), maxHeapServer_(std::move(maxHeapServer))
  {
}
QueryConstants::~QueryConstants() = default;
void QueryConstants::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&minHeapGb_);
  sa.write(&defaultMaxHeapGb_);
  sa.write(&minDataRatio_);
  sa.write(&maxDataRatio_);
  sa.write(&maxScriptCodeLength_);
  sa.write(&consoleDefaultHeap_);
  sa.write(&pqDefaultHeap_);
  sa.write(&serverNames_);
  sa.write(&maxHeapServer_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> QueryConstants::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  double minHeapGb;
  double defaultMaxHeapGb;
  double minDataRatio;
  double maxDataRatio;
  double maxScriptCodeLength;
  double consoleDefaultHeap;
  double pqDefaultHeap;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> serverNames;
  std::shared_ptr<std::vector<double>> maxHeapServer;
  da.read(&minHeapGb);
  da.read(&defaultMaxHeapGb);
  da.read(&minDataRatio);
  da.read(&maxDataRatio);
  da.read(&maxScriptCodeLength);
  da.read(&consoleDefaultHeap);
  da.read(&pqDefaultHeap);
  da.read(&serverNames);
  da.read(&maxHeapServer);
  return QueryConstants::create(minHeapGb, defaultMaxHeapGb, minDataRatio, maxDataRatio, maxScriptCodeLength, consoleDefaultHeap, pqDefaultHeap, std::move(serverNames), std::move(maxHeapServer));
}
const boost::string_view QuerySelectionPermissions::typeName("com.illumon.iris.web.shared.data.QuerySelectionPermissions");
std::shared_ptr<QuerySelectionPermissions> QuerySelectionPermissions::create(bool allAdmin, bool allOwner, bool allRestartable, bool allStoppable, bool allStopped, bool allDisabled, bool allEnabled, bool allTemporary, bool allImportMerge, bool readOnlyUser) {
  return std::make_shared<QuerySelectionPermissions>(Private(), allAdmin, allOwner, allRestartable, allStoppable, allStopped, allDisabled, allEnabled, allTemporary, allImportMerge, readOnlyUser);
}
QuerySelectionPermissions::QuerySelectionPermissions(Private, bool allAdmin, bool allOwner, bool allRestartable, bool allStoppable, bool allStopped, bool allDisabled, bool allEnabled, bool allTemporary, bool allImportMerge, bool readOnlyUser)
  : allAdmin_(allAdmin), allOwner_(allOwner), allRestartable_(allRestartable), allStoppable_(allStoppable), allStopped_(allStopped), allDisabled_(allDisabled), allEnabled_(allEnabled), allTemporary_(allTemporary), allImportMerge_(allImportMerge), readOnlyUser_(readOnlyUser)
  {
}
QuerySelectionPermissions::~QuerySelectionPermissions() = default;
void QuerySelectionPermissions::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&allAdmin_);
  sa.write(&allOwner_);
  sa.write(&allRestartable_);
  sa.write(&allStoppable_);
  sa.write(&allStopped_);
  sa.write(&allDisabled_);
  sa.write(&allEnabled_);
  sa.write(&allTemporary_);
  sa.write(&allImportMerge_);
  sa.write(&readOnlyUser_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> QuerySelectionPermissions::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  bool allAdmin;
  bool allOwner;
  bool allRestartable;
  bool allStoppable;
  bool allStopped;
  bool allDisabled;
  bool allEnabled;
  bool allTemporary;
  bool allImportMerge;
  bool readOnlyUser;
  da.read(&allAdmin);
  da.read(&allOwner);
  da.read(&allRestartable);
  da.read(&allStoppable);
  da.read(&allStopped);
  da.read(&allDisabled);
  da.read(&allEnabled);
  da.read(&allTemporary);
  da.read(&allImportMerge);
  da.read(&readOnlyUser);
  return QuerySelectionPermissions::create(allAdmin, allOwner, allRestartable, allStoppable, allStopped, allDisabled, allEnabled, allTemporary, allImportMerge, readOnlyUser);
}
const boost::string_view Range::typeName("com.illumon.iris.web.shared.data.Range");
std::shared_ptr<Range> Range::create(int64_t first, int64_t last) {
  return std::make_shared<Range>(Private(), first, last);
}
Range::Range(Private, int64_t first, int64_t last)
  : first_(first), last_(last)
  {
}
Range::~Range() = default;
void Range::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&first_);
  sa.write(&last_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> Range::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  int64_t first;
  int64_t last;
  da.read(&first);
  da.read(&last);
  return Range::create(first, last);
}
const boost::string_view RangeSet::typeName("com.illumon.iris.web.shared.data.RangeSet");
std::shared_ptr<RangeSet> RangeSet::create(std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Range>>> sortedRanges) {
  return std::make_shared<RangeSet>(Private(), std::move(sortedRanges));
}
RangeSet::RangeSet(Private, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Range>>> sortedRanges)
  : sortedRanges_(std::move(sortedRanges))
  {
}
RangeSet::~RangeSet() = default;
void RangeSet::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&sortedRanges_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> RangeSet::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Range>>> sortedRanges;
  da.read(&sortedRanges);
  return RangeSet::create(std::move(sortedRanges));
}
const boost::string_view RefreshToken::typeName("com.illumon.iris.web.shared.data.RefreshToken");
std::shared_ptr<RefreshToken> RefreshToken::create(std::shared_ptr<std::vector<int8_t>> bytes, int64_t expiry) {
  return std::make_shared<RefreshToken>(Private(), std::move(bytes), expiry);
}
RefreshToken::RefreshToken(Private, std::shared_ptr<std::vector<int8_t>> bytes, int64_t expiry)
  : bytes_(std::move(bytes)), expiry_(expiry)
  {
}
RefreshToken::~RefreshToken() = default;
void RefreshToken::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&bytes_);
  sa.write(&expiry_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> RefreshToken::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::vector<int8_t>> bytes;
  int64_t expiry;
  da.read(&bytes);
  da.read(&expiry);
  return RefreshToken::create(std::move(bytes), expiry);
}
const boost::string_view RollupDefinition::typeName("com.illumon.iris.web.shared.data.RollupDefinition");
std::shared_ptr<RollupDefinition> RollupDefinition::create(deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::rollupDefinition::LeafType leafType, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> byColumns, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> sourceColumnNames, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> rollupColumnNames) {
  return std::make_shared<RollupDefinition>(Private(), leafType, std::move(byColumns), std::move(sourceColumnNames), std::move(rollupColumnNames));
}
RollupDefinition::RollupDefinition(Private, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::rollupDefinition::LeafType leafType, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> byColumns, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> sourceColumnNames, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> rollupColumnNames)
  : leafType_(leafType), byColumns_(std::move(byColumns)), sourceColumnNames_(std::move(sourceColumnNames)), rollupColumnNames_(std::move(rollupColumnNames))
  {
}
RollupDefinition::~RollupDefinition() = default;
void RollupDefinition::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&leafType_);
  sa.write(&byColumns_);
  sa.write(&sourceColumnNames_);
  sa.write(&rollupColumnNames_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> RollupDefinition::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::rollupDefinition::LeafType leafType;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> byColumns;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> sourceColumnNames;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> rollupColumnNames;
  da.read(&leafType);
  da.read(&byColumns);
  da.read(&sourceColumnNames);
  da.read(&rollupColumnNames);
  return RollupDefinition::create(leafType, std::move(byColumns), std::move(sourceColumnNames), std::move(rollupColumnNames));
}
const boost::string_view RowValues::typeName("com.illumon.iris.web.shared.data.RowValues");
std::shared_ptr<RowValues> RowValues::create(std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnValue>>> columns) {
  return std::make_shared<RowValues>(Private(), std::move(columns));
}
RowValues::RowValues(Private, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnValue>>> columns)
  : columns_(std::move(columns))
  {
}
RowValues::~RowValues() = default;
void RowValues::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&columns_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> RowValues::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnValue>>> columns;
  da.read(&columns);
  return RowValues::create(std::move(columns));
}
const boost::string_view ServerConfigValues::typeName("com.illumon.iris.web.shared.data.ServerConfigValues");
std::shared_ptr<ServerConfigValues> ServerConfigValues::create(std::shared_ptr<std::string> gradleVersion, std::shared_ptr<std::string> vcsVersion, std::shared_ptr<std::string> javaVersion, std::shared_ptr<std::string> hostName, std::shared_ptr<std::string> systemName, std::shared_ptr<std::string> systemType, std::shared_ptr<std::string> supportContact, std::shared_ptr<std::string> supportDocs, bool isSettingsLogoConfigured) {
  return std::make_shared<ServerConfigValues>(Private(), std::move(gradleVersion), std::move(vcsVersion), std::move(javaVersion), std::move(hostName), std::move(systemName), std::move(systemType), std::move(supportContact), std::move(supportDocs), isSettingsLogoConfigured);
}
ServerConfigValues::ServerConfigValues(Private, std::shared_ptr<std::string> gradleVersion, std::shared_ptr<std::string> vcsVersion, std::shared_ptr<std::string> javaVersion, std::shared_ptr<std::string> hostName, std::shared_ptr<std::string> systemName, std::shared_ptr<std::string> systemType, std::shared_ptr<std::string> supportContact, std::shared_ptr<std::string> supportDocs, bool isSettingsLogoConfigured)
  : gradleVersion_(std::move(gradleVersion)), vcsVersion_(std::move(vcsVersion)), javaVersion_(std::move(javaVersion)), hostName_(std::move(hostName)), systemName_(std::move(systemName)), systemType_(std::move(systemType)), supportContact_(std::move(supportContact)), supportDocs_(std::move(supportDocs)), isSettingsLogoConfigured_(isSettingsLogoConfigured)
  {
}
ServerConfigValues::~ServerConfigValues() = default;
void ServerConfigValues::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&gradleVersion_);
  sa.write(&vcsVersion_);
  sa.write(&javaVersion_);
  sa.write(&hostName_);
  sa.write(&systemName_);
  sa.write(&systemType_);
  sa.write(&supportContact_);
  sa.write(&supportDocs_);
  sa.write(&isSettingsLogoConfigured_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> ServerConfigValues::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::string> gradleVersion;
  std::shared_ptr<std::string> vcsVersion;
  std::shared_ptr<std::string> javaVersion;
  std::shared_ptr<std::string> hostName;
  std::shared_ptr<std::string> systemName;
  std::shared_ptr<std::string> systemType;
  std::shared_ptr<std::string> supportContact;
  std::shared_ptr<std::string> supportDocs;
  bool isSettingsLogoConfigured;
  da.read(&gradleVersion);
  da.read(&vcsVersion);
  da.read(&javaVersion);
  da.read(&hostName);
  da.read(&systemName);
  da.read(&systemType);
  da.read(&supportContact);
  da.read(&supportDocs);
  da.read(&isSettingsLogoConfigured);
  return ServerConfigValues::create(std::move(gradleVersion), std::move(vcsVersion), std::move(javaVersion), std::move(hostName), std::move(systemName), std::move(systemType), std::move(supportContact), std::move(supportDocs), isSettingsLogoConfigured);
}
const boost::string_view ShiftedRange::typeName("com.illumon.iris.web.shared.data.ShiftedRange");
std::shared_ptr<ShiftedRange> ShiftedRange::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Range> range, int64_t delta) {
  return std::make_shared<ShiftedRange>(Private(), std::move(range), delta);
}
ShiftedRange::ShiftedRange(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Range> range, int64_t delta)
  : range_(std::move(range)), delta_(delta)
  {
}
ShiftedRange::~ShiftedRange() = default;
void ShiftedRange::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&range_);
  sa.write(&delta_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> ShiftedRange::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::Range> range;
  int64_t delta;
  da.read(&range);
  da.read(&delta);
  return ShiftedRange::create(std::move(range), delta);
}
const boost::string_view SortDescriptor::typeName("com.illumon.iris.web.shared.data.SortDescriptor");
std::shared_ptr<SortDescriptor> SortDescriptor::create(int32_t columnIndex, std::shared_ptr<std::string> dir, std::shared_ptr<std::string> columnName, bool abs) {
  return std::make_shared<SortDescriptor>(Private(), columnIndex, std::move(dir), std::move(columnName), abs);
}
SortDescriptor::SortDescriptor(Private, int32_t columnIndex, std::shared_ptr<std::string> dir, std::shared_ptr<std::string> columnName, bool abs)
  : columnIndex_(columnIndex), dir_(std::move(dir)), columnName_(std::move(columnName)), abs_(abs)
  {
}
SortDescriptor::~SortDescriptor() = default;
void SortDescriptor::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&columnIndex_);
  sa.write(&dir_);
  sa.write(&columnName_);
  sa.write(&abs_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> SortDescriptor::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  int32_t columnIndex;
  std::shared_ptr<std::string> dir;
  std::shared_ptr<std::string> columnName;
  bool abs;
  da.read(&columnIndex);
  da.read(&dir);
  da.read(&columnName);
  da.read(&abs);
  return SortDescriptor::create(columnIndex, std::move(dir), std::move(columnName), abs);
}
const boost::string_view TableDefinition::typeName("com.illumon.iris.web.shared.data.TableDefinition");
std::shared_ptr<TableDefinition> TableDefinition::create(std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnDefinition>>> columns) {
  return std::make_shared<TableDefinition>(Private(), std::move(columns));
}
TableDefinition::TableDefinition(Private, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnDefinition>>> columns)
  : columns_(std::move(columns))
  {
}
TableDefinition::~TableDefinition() = default;
void TableDefinition::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&columns_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> TableDefinition::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ColumnDefinition>>> columns;
  da.read(&columns);
  return TableDefinition::create(std::move(columns));
}
const boost::string_view TableHandle::typeName("com.illumon.iris.web.shared.data.TableHandle");
TableHandle::TableHandle(Private, deephaven::openAPI::lowlevel::remoting::custom::com::illumon::iris::web::shared::data::TableHandleCustom custom)
  : custom_(std::move(custom))
  {
}
TableHandle::~TableHandle() = default;
void TableHandle::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  custom_.serialize(serializer);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> TableHandle::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  auto custom = deephaven::openAPI::lowlevel::remoting::custom::com::illumon::iris::web::shared::data::TableHandleCustom::deserialize(deserializer);
  return TableHandle::create(std::move(custom));
}
const boost::string_view TableMapDeclaration::typeName("com.illumon.iris.web.shared.data.TableMapDeclaration");
std::shared_ptr<TableMapDeclaration> TableMapDeclaration::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData> keys, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> handle) {
  return std::make_shared<TableMapDeclaration>(Private(), std::move(keys), std::move(handle));
}
TableMapDeclaration::TableMapDeclaration(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData> keys, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> handle)
  : keys_(std::move(keys)), handle_(std::move(handle))
  {
}
TableMapDeclaration::~TableMapDeclaration() = default;
void TableMapDeclaration::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&keys_);
  sa.write(&handle_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> TableMapDeclaration::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData> keys;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle> handle;
  da.read(&keys);
  da.read(&handle);
  return TableMapDeclaration::create(std::move(keys), std::move(handle));
}
const boost::string_view TableMapHandle::typeName("com.illumon.iris.web.shared.data.TableMapHandle");
std::shared_ptr<TableMapHandle> TableMapHandle::create(int32_t serverId) {
  return std::make_shared<TableMapHandle>(Private(), serverId);
}
TableMapHandle::TableMapHandle(Private, int32_t serverId)
  : serverId_(serverId)
  {
}
TableMapHandle::~TableMapHandle() = default;
void TableMapHandle::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&serverId_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> TableMapHandle::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  int32_t serverId;
  da.read(&serverId);
  return TableMapHandle::create(serverId);
}
const boost::string_view TableSnapshot::typeName("com.illumon.iris.web.shared.data.TableSnapshot");
std::shared_ptr<TableSnapshot> TableSnapshot::create(deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::tableSnapshot::SnapshotType snapshotType, int64_t deltaSequence, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData>>> dataColumns, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> includedRows, int64_t tableSize) {
  return std::make_shared<TableSnapshot>(Private(), snapshotType, deltaSequence, std::move(dataColumns), std::move(includedRows), tableSize);
}
TableSnapshot::TableSnapshot(Private, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::tableSnapshot::SnapshotType snapshotType, int64_t deltaSequence, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData>>> dataColumns, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> includedRows, int64_t tableSize)
  : snapshotType_(snapshotType), deltaSequence_(deltaSequence), dataColumns_(std::move(dataColumns)), includedRows_(std::move(includedRows)), tableSize_(tableSize)
  {
}
TableSnapshot::~TableSnapshot() = default;
void TableSnapshot::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&snapshotType_);
  sa.write(&deltaSequence_);
  sa.write(&dataColumns_);
  sa.write(&includedRows_);
  sa.write(&tableSize_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> TableSnapshot::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::tableSnapshot::SnapshotType snapshotType;
  int64_t deltaSequence;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData>>> dataColumns;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> includedRows;
  int64_t tableSize;
  da.read(&snapshotType);
  da.read(&deltaSequence);
  da.read(&dataColumns);
  da.read(&includedRows);
  da.read(&tableSize);
  return TableSnapshot::create(snapshotType, deltaSequence, std::move(dataColumns), std::move(includedRows), tableSize);
}
const boost::string_view TableSubscriptionRequest::typeName("com.illumon.iris.web.shared.data.TableSubscriptionRequest");
std::shared_ptr<TableSubscriptionRequest> TableSubscriptionRequest::create(int32_t subscriptionId, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> rows, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> columns) {
  return std::make_shared<TableSubscriptionRequest>(Private(), subscriptionId, std::move(rows), std::move(columns));
}
TableSubscriptionRequest::TableSubscriptionRequest(Private, int32_t subscriptionId, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> rows, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> columns)
  : subscriptionId_(subscriptionId), rows_(std::move(rows)), columns_(std::move(columns))
  {
}
TableSubscriptionRequest::~TableSubscriptionRequest() = default;
void TableSubscriptionRequest::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&subscriptionId_);
  sa.write(&rows_);
  sa.write(&columns_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> TableSubscriptionRequest::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  int32_t subscriptionId;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RangeSet> rows;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> columns;
  da.read(&subscriptionId);
  da.read(&rows);
  da.read(&columns);
  return TableSubscriptionRequest::create(subscriptionId, std::move(rows), std::move(columns));
}
const boost::string_view TableValues::typeName("com.illumon.iris.web.shared.data.TableValues");
std::shared_ptr<TableValues> TableValues::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RowValues>>> rows) {
  return std::make_shared<TableValues>(Private(), std::move(handle), std::move(rows));
}
TableValues::TableValues(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RowValues>>> rows)
  : handle_(std::move(handle)), rows_(std::move(rows))
  {
}
TableValues::~TableValues() = default;
void TableValues::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&handle_);
  sa.write(&rows_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> TableValues::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> handle;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::RowValues>>> rows;
  da.read(&handle);
  da.read(&rows);
  return TableValues::create(std::move(handle), std::move(rows));
}
const boost::string_view UserInfo::typeName("com.illumon.iris.web.shared.data.UserInfo");
std::shared_ptr<UserInfo> UserInfo::create(std::shared_ptr<std::string> username, std::shared_ptr<std::string> operateAs) {
  return std::make_shared<UserInfo>(Private(), std::move(username), std::move(operateAs));
}
UserInfo::UserInfo(Private, std::shared_ptr<std::string> username, std::shared_ptr<std::string> operateAs)
  : username_(std::move(username)), operateAs_(std::move(operateAs))
  {
}
UserInfo::~UserInfo() = default;
void UserInfo::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&username_);
  sa.write(&operateAs_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> UserInfo::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::string> username;
  std::shared_ptr<std::string> operateAs;
  da.read(&username);
  da.read(&operateAs);
  return UserInfo::create(std::move(username), std::move(operateAs));
}
namespace columns {
const boost::string_view ColumnData::typeName("com.illumon.iris.web.shared.data.columns.ColumnData");
std::shared_ptr<ColumnData> ColumnData::create() {
  return std::make_shared<ColumnData>(Private());
}
ColumnData::ColumnData(Private)
  
  {
}
ColumnData::~ColumnData() = default;
void ColumnData::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> ColumnData::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  return ColumnData::create();
}
const boost::string_view BigDecimalArrayColumnData::typeName("com.illumon.iris.web.shared.data.columns.BigDecimalArrayColumnData");
std::shared_ptr<BigDecimalArrayColumnData> BigDecimalArrayColumnData::create(std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::math::BigDecimal>>> data) {
  return std::make_shared<BigDecimalArrayColumnData>(Private(), std::move(data));
}
BigDecimalArrayColumnData::BigDecimalArrayColumnData(Private, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::math::BigDecimal>>> data)
  : deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData(Private()), data_(std::move(data))
  {
}
BigDecimalArrayColumnData::~BigDecimalArrayColumnData() = default;
void BigDecimalArrayColumnData::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&data_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> BigDecimalArrayColumnData::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::math::BigDecimal>>> data;
  da.read(&data);
  return BigDecimalArrayColumnData::create(std::move(data));
}
const boost::string_view BigIntegerArrayColumnData::typeName("com.illumon.iris.web.shared.data.columns.BigIntegerArrayColumnData");
std::shared_ptr<BigIntegerArrayColumnData> BigIntegerArrayColumnData::create(std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::math::BigInteger>>> data) {
  return std::make_shared<BigIntegerArrayColumnData>(Private(), std::move(data));
}
BigIntegerArrayColumnData::BigIntegerArrayColumnData(Private, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::math::BigInteger>>> data)
  : deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData(Private()), data_(std::move(data))
  {
}
BigIntegerArrayColumnData::~BigIntegerArrayColumnData() = default;
void BigIntegerArrayColumnData::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&data_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> BigIntegerArrayColumnData::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::math::BigInteger>>> data;
  da.read(&data);
  return BigIntegerArrayColumnData::create(std::move(data));
}
const boost::string_view ByteArrayColumnData::typeName("com.illumon.iris.web.shared.data.columns.ByteArrayColumnData");
std::shared_ptr<ByteArrayColumnData> ByteArrayColumnData::create(std::shared_ptr<std::vector<int8_t>> data) {
  return std::make_shared<ByteArrayColumnData>(Private(), std::move(data));
}
ByteArrayColumnData::ByteArrayColumnData(Private, std::shared_ptr<std::vector<int8_t>> data)
  : deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData(Private()), data_(std::move(data))
  {
}
ByteArrayColumnData::~ByteArrayColumnData() = default;
void ByteArrayColumnData::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&data_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> ByteArrayColumnData::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::vector<int8_t>> data;
  da.read(&data);
  return ByteArrayColumnData::create(std::move(data));
}
const boost::string_view CharArrayColumnData::typeName("com.illumon.iris.web.shared.data.columns.CharArrayColumnData");
std::shared_ptr<CharArrayColumnData> CharArrayColumnData::create(std::shared_ptr<std::vector<char16_t>> data) {
  return std::make_shared<CharArrayColumnData>(Private(), std::move(data));
}
CharArrayColumnData::CharArrayColumnData(Private, std::shared_ptr<std::vector<char16_t>> data)
  : deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData(Private()), data_(std::move(data))
  {
}
CharArrayColumnData::~CharArrayColumnData() = default;
void CharArrayColumnData::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&data_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> CharArrayColumnData::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::vector<char16_t>> data;
  da.read(&data);
  return CharArrayColumnData::create(std::move(data));
}
const boost::string_view DoubleArrayColumnData::typeName("com.illumon.iris.web.shared.data.columns.DoubleArrayColumnData");
std::shared_ptr<DoubleArrayColumnData> DoubleArrayColumnData::create(std::shared_ptr<std::vector<double>> data) {
  return std::make_shared<DoubleArrayColumnData>(Private(), std::move(data));
}
DoubleArrayColumnData::DoubleArrayColumnData(Private, std::shared_ptr<std::vector<double>> data)
  : deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData(Private()), data_(std::move(data))
  {
}
DoubleArrayColumnData::~DoubleArrayColumnData() = default;
void DoubleArrayColumnData::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&data_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> DoubleArrayColumnData::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::vector<double>> data;
  da.read(&data);
  return DoubleArrayColumnData::create(std::move(data));
}
const boost::string_view FloatArrayColumnData::typeName("com.illumon.iris.web.shared.data.columns.FloatArrayColumnData");
std::shared_ptr<FloatArrayColumnData> FloatArrayColumnData::create(std::shared_ptr<std::vector<float>> data) {
  return std::make_shared<FloatArrayColumnData>(Private(), std::move(data));
}
FloatArrayColumnData::FloatArrayColumnData(Private, std::shared_ptr<std::vector<float>> data)
  : deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData(Private()), data_(std::move(data))
  {
}
FloatArrayColumnData::~FloatArrayColumnData() = default;
void FloatArrayColumnData::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&data_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> FloatArrayColumnData::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::vector<float>> data;
  da.read(&data);
  return FloatArrayColumnData::create(std::move(data));
}
const boost::string_view IntArrayColumnData::typeName("com.illumon.iris.web.shared.data.columns.IntArrayColumnData");
std::shared_ptr<IntArrayColumnData> IntArrayColumnData::create(std::shared_ptr<std::vector<int32_t>> data) {
  return std::make_shared<IntArrayColumnData>(Private(), std::move(data));
}
IntArrayColumnData::IntArrayColumnData(Private, std::shared_ptr<std::vector<int32_t>> data)
  : deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData(Private()), data_(std::move(data))
  {
}
IntArrayColumnData::~IntArrayColumnData() = default;
void IntArrayColumnData::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&data_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> IntArrayColumnData::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::vector<int32_t>> data;
  da.read(&data);
  return IntArrayColumnData::create(std::move(data));
}
const boost::string_view LocalDateArrayColumnData::typeName("com.illumon.iris.web.shared.data.columns.LocalDateArrayColumnData");
std::shared_ptr<LocalDateArrayColumnData> LocalDateArrayColumnData::create(std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LocalDate>>> data) {
  return std::make_shared<LocalDateArrayColumnData>(Private(), std::move(data));
}
LocalDateArrayColumnData::LocalDateArrayColumnData(Private, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LocalDate>>> data)
  : deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData(Private()), data_(std::move(data))
  {
}
LocalDateArrayColumnData::~LocalDateArrayColumnData() = default;
void LocalDateArrayColumnData::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&data_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> LocalDateArrayColumnData::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LocalDate>>> data;
  da.read(&data);
  return LocalDateArrayColumnData::create(std::move(data));
}
const boost::string_view LocalTimeArrayColumnData::typeName("com.illumon.iris.web.shared.data.columns.LocalTimeArrayColumnData");
std::shared_ptr<LocalTimeArrayColumnData> LocalTimeArrayColumnData::create(std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LocalTime>>> data) {
  return std::make_shared<LocalTimeArrayColumnData>(Private(), std::move(data));
}
LocalTimeArrayColumnData::LocalTimeArrayColumnData(Private, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LocalTime>>> data)
  : deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData(Private()), data_(std::move(data))
  {
}
LocalTimeArrayColumnData::~LocalTimeArrayColumnData() = default;
void LocalTimeArrayColumnData::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&data_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> LocalTimeArrayColumnData::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::LocalTime>>> data;
  da.read(&data);
  return LocalTimeArrayColumnData::create(std::move(data));
}
const boost::string_view LongArrayColumnData::typeName("com.illumon.iris.web.shared.data.columns.LongArrayColumnData");
std::shared_ptr<LongArrayColumnData> LongArrayColumnData::create(std::shared_ptr<std::vector<int64_t>> data) {
  return std::make_shared<LongArrayColumnData>(Private(), std::move(data));
}
LongArrayColumnData::LongArrayColumnData(Private, std::shared_ptr<std::vector<int64_t>> data)
  : deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData(Private()), data_(std::move(data))
  {
}
LongArrayColumnData::~LongArrayColumnData() = default;
void LongArrayColumnData::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&data_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> LongArrayColumnData::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::vector<int64_t>> data;
  da.read(&data);
  return LongArrayColumnData::create(std::move(data));
}
const boost::string_view ShortArrayColumnData::typeName("com.illumon.iris.web.shared.data.columns.ShortArrayColumnData");
std::shared_ptr<ShortArrayColumnData> ShortArrayColumnData::create(std::shared_ptr<std::vector<int16_t>> data) {
  return std::make_shared<ShortArrayColumnData>(Private(), std::move(data));
}
ShortArrayColumnData::ShortArrayColumnData(Private, std::shared_ptr<std::vector<int16_t>> data)
  : deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData(Private()), data_(std::move(data))
  {
}
ShortArrayColumnData::~ShortArrayColumnData() = default;
void ShortArrayColumnData::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&data_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> ShortArrayColumnData::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::vector<int16_t>> data;
  da.read(&data);
  return ShortArrayColumnData::create(std::move(data));
}
const boost::string_view StringArrayArrayColumnData::typeName("com.illumon.iris.web.shared.data.columns.StringArrayArrayColumnData");
std::shared_ptr<StringArrayArrayColumnData> StringArrayArrayColumnData::create(std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<std::string>>>>> data) {
  return std::make_shared<StringArrayArrayColumnData>(Private(), std::move(data));
}
StringArrayArrayColumnData::StringArrayArrayColumnData(Private, std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<std::string>>>>> data)
  : deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData(Private()), data_(std::move(data))
  {
}
StringArrayArrayColumnData::~StringArrayArrayColumnData() = default;
void StringArrayArrayColumnData::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&data_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> StringArrayArrayColumnData::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<std::string>>>>> data;
  da.read(&data);
  return StringArrayArrayColumnData::create(std::move(data));
}
const boost::string_view StringArrayColumnData::typeName("com.illumon.iris.web.shared.data.columns.StringArrayColumnData");
std::shared_ptr<StringArrayColumnData> StringArrayColumnData::create(std::shared_ptr<std::vector<std::shared_ptr<std::string>>> data) {
  return std::make_shared<StringArrayColumnData>(Private(), std::move(data));
}
StringArrayColumnData::StringArrayColumnData(Private, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> data)
  : deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData(Private()), data_(std::move(data))
  {
}
StringArrayColumnData::~StringArrayColumnData() = default;
void StringArrayColumnData::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&data_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> StringArrayColumnData::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> data;
  da.read(&data);
  return StringArrayColumnData::create(std::move(data));
}
}  // namespace columns
namespace plot {
const boost::string_view AxisDescriptor::typeName("com.illumon.iris.web.shared.data.plot.AxisDescriptor");
std::shared_ptr<AxisDescriptor> AxisDescriptor::create(std::shared_ptr<std::string> id, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::axisDescriptor::AxisFormatType formatType, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::axisDescriptor::AxisType type, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::axisDescriptor::AxisPosition position, bool log, std::shared_ptr<std::string> label, std::shared_ptr<std::string> labelFont, std::shared_ptr<std::string> ticksFont, std::shared_ptr<std::string> formatPattern, std::shared_ptr<std::string> color, double minRange, double maxRange, bool minorTicksVisible, bool majorTicksVisible, int32_t minorTickCount, double gapBetweenMajorTicks, std::shared_ptr<std::vector<double>> majorTickLocations, double tickLabelAngle, bool invert, bool isTimeAxis, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::BusinessCalendarDescriptor> businessCalendarDescriptor) {
  return std::make_shared<AxisDescriptor>(Private(), std::move(id), formatType, type, position, log, std::move(label), std::move(labelFont), std::move(ticksFont), std::move(formatPattern), std::move(color), minRange, maxRange, minorTicksVisible, majorTicksVisible, minorTickCount, gapBetweenMajorTicks, std::move(majorTickLocations), tickLabelAngle, invert, isTimeAxis, std::move(businessCalendarDescriptor));
}
AxisDescriptor::AxisDescriptor(Private, std::shared_ptr<std::string> id, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::axisDescriptor::AxisFormatType formatType, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::axisDescriptor::AxisType type, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::axisDescriptor::AxisPosition position, bool log, std::shared_ptr<std::string> label, std::shared_ptr<std::string> labelFont, std::shared_ptr<std::string> ticksFont, std::shared_ptr<std::string> formatPattern, std::shared_ptr<std::string> color, double minRange, double maxRange, bool minorTicksVisible, bool majorTicksVisible, int32_t minorTickCount, double gapBetweenMajorTicks, std::shared_ptr<std::vector<double>> majorTickLocations, double tickLabelAngle, bool invert, bool isTimeAxis, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::BusinessCalendarDescriptor> businessCalendarDescriptor)
  : id_(std::move(id)), formatType_(formatType), type_(type), position_(position), log_(log), label_(std::move(label)), labelFont_(std::move(labelFont)), ticksFont_(std::move(ticksFont)), formatPattern_(std::move(formatPattern)), color_(std::move(color)), minRange_(minRange), maxRange_(maxRange), minorTicksVisible_(minorTicksVisible), majorTicksVisible_(majorTicksVisible), minorTickCount_(minorTickCount), gapBetweenMajorTicks_(gapBetweenMajorTicks), majorTickLocations_(std::move(majorTickLocations)), tickLabelAngle_(tickLabelAngle), invert_(invert), isTimeAxis_(isTimeAxis), businessCalendarDescriptor_(std::move(businessCalendarDescriptor))
  {
}
AxisDescriptor::~AxisDescriptor() = default;
void AxisDescriptor::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&id_);
  sa.write(&formatType_);
  sa.write(&type_);
  sa.write(&position_);
  sa.write(&log_);
  sa.write(&label_);
  sa.write(&labelFont_);
  sa.write(&ticksFont_);
  sa.write(&formatPattern_);
  sa.write(&color_);
  sa.write(&minRange_);
  sa.write(&maxRange_);
  sa.write(&minorTicksVisible_);
  sa.write(&majorTicksVisible_);
  sa.write(&minorTickCount_);
  sa.write(&gapBetweenMajorTicks_);
  sa.write(&majorTickLocations_);
  sa.write(&tickLabelAngle_);
  sa.write(&invert_);
  sa.write(&isTimeAxis_);
  sa.write(&businessCalendarDescriptor_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> AxisDescriptor::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::string> id;
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::axisDescriptor::AxisFormatType formatType;
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::axisDescriptor::AxisType type;
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::axisDescriptor::AxisPosition position;
  bool log;
  std::shared_ptr<std::string> label;
  std::shared_ptr<std::string> labelFont;
  std::shared_ptr<std::string> ticksFont;
  std::shared_ptr<std::string> formatPattern;
  std::shared_ptr<std::string> color;
  double minRange;
  double maxRange;
  bool minorTicksVisible;
  bool majorTicksVisible;
  int32_t minorTickCount;
  double gapBetweenMajorTicks;
  std::shared_ptr<std::vector<double>> majorTickLocations;
  double tickLabelAngle;
  bool invert;
  bool isTimeAxis;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::BusinessCalendarDescriptor> businessCalendarDescriptor;
  da.read(&id);
  da.read(&formatType);
  da.read(&type);
  da.read(&position);
  da.read(&log);
  da.read(&label);
  da.read(&labelFont);
  da.read(&ticksFont);
  da.read(&formatPattern);
  da.read(&color);
  da.read(&minRange);
  da.read(&maxRange);
  da.read(&minorTicksVisible);
  da.read(&majorTicksVisible);
  da.read(&minorTickCount);
  da.read(&gapBetweenMajorTicks);
  da.read(&majorTickLocations);
  da.read(&tickLabelAngle);
  da.read(&invert);
  da.read(&isTimeAxis);
  da.read(&businessCalendarDescriptor);
  return AxisDescriptor::create(std::move(id), formatType, type, position, log, std::move(label), std::move(labelFont), std::move(ticksFont), std::move(formatPattern), std::move(color), minRange, maxRange, minorTicksVisible, majorTicksVisible, minorTickCount, gapBetweenMajorTicks, std::move(majorTickLocations), tickLabelAngle, invert, isTimeAxis, std::move(businessCalendarDescriptor));
}
const boost::string_view ChartDescriptor::typeName("com.illumon.iris.web.shared.data.plot.ChartDescriptor");
std::shared_ptr<ChartDescriptor> ChartDescriptor::create(int32_t colspan, int32_t rowspan, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SeriesDescriptor>>> series, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::MultiSeriesDescriptor>>> multiSeries, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::AxisDescriptor>>> axes, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::chartDescriptor::ChartType chartType, std::shared_ptr<std::string> title, std::shared_ptr<std::string> titleFont, std::shared_ptr<std::string> titleColor, bool showLegend, std::shared_ptr<std::string> legendFont, std::shared_ptr<std::string> legendColor, bool is3d) {
  return std::make_shared<ChartDescriptor>(Private(), colspan, rowspan, std::move(series), std::move(multiSeries), std::move(axes), chartType, std::move(title), std::move(titleFont), std::move(titleColor), showLegend, std::move(legendFont), std::move(legendColor), is3d);
}
ChartDescriptor::ChartDescriptor(Private, int32_t colspan, int32_t rowspan, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SeriesDescriptor>>> series, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::MultiSeriesDescriptor>>> multiSeries, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::AxisDescriptor>>> axes, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::chartDescriptor::ChartType chartType, std::shared_ptr<std::string> title, std::shared_ptr<std::string> titleFont, std::shared_ptr<std::string> titleColor, bool showLegend, std::shared_ptr<std::string> legendFont, std::shared_ptr<std::string> legendColor, bool is3d)
  : colspan_(colspan), rowspan_(rowspan), series_(std::move(series)), multiSeries_(std::move(multiSeries)), axes_(std::move(axes)), chartType_(chartType), title_(std::move(title)), titleFont_(std::move(titleFont)), titleColor_(std::move(titleColor)), showLegend_(showLegend), legendFont_(std::move(legendFont)), legendColor_(std::move(legendColor)), is3d_(is3d)
  {
}
ChartDescriptor::~ChartDescriptor() = default;
void ChartDescriptor::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&colspan_);
  sa.write(&rowspan_);
  sa.write(&series_);
  sa.write(&multiSeries_);
  sa.write(&axes_);
  sa.write(&chartType_);
  sa.write(&title_);
  sa.write(&titleFont_);
  sa.write(&titleColor_);
  sa.write(&showLegend_);
  sa.write(&legendFont_);
  sa.write(&legendColor_);
  sa.write(&is3d_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> ChartDescriptor::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  int32_t colspan;
  int32_t rowspan;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SeriesDescriptor>>> series;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::MultiSeriesDescriptor>>> multiSeries;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::AxisDescriptor>>> axes;
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::chartDescriptor::ChartType chartType;
  std::shared_ptr<std::string> title;
  std::shared_ptr<std::string> titleFont;
  std::shared_ptr<std::string> titleColor;
  bool showLegend;
  std::shared_ptr<std::string> legendFont;
  std::shared_ptr<std::string> legendColor;
  bool is3d;
  da.read(&colspan);
  da.read(&rowspan);
  da.read(&series);
  da.read(&multiSeries);
  da.read(&axes);
  da.read(&chartType);
  da.read(&title);
  da.read(&titleFont);
  da.read(&titleColor);
  da.read(&showLegend);
  da.read(&legendFont);
  da.read(&legendColor);
  da.read(&is3d);
  return ChartDescriptor::create(colspan, rowspan, std::move(series), std::move(multiSeries), std::move(axes), chartType, std::move(title), std::move(titleFont), std::move(titleColor), showLegend, std::move(legendFont), std::move(legendColor), is3d);
}
const boost::string_view FigureDescriptor::typeName("com.illumon.iris.web.shared.data.plot.FigureDescriptor");
std::shared_ptr<FigureDescriptor> FigureDescriptor::create(std::shared_ptr<std::string> title, std::shared_ptr<std::string> titleFont, std::shared_ptr<std::string> titleColor, bool resizable, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::ThemeDescriptor> theme, bool isDefaultTheme, double updateInterval, int32_t cols, int32_t rows, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::ChartDescriptor>>> charts, std::shared_ptr<std::vector<int32_t>> tableIds, std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>> plotHandleIds, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle>>> tableMaps, std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>> tableMapIds, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> errors) {
  return std::make_shared<FigureDescriptor>(Private(), std::move(title), std::move(titleFont), std::move(titleColor), resizable, std::move(theme), isDefaultTheme, updateInterval, cols, rows, std::move(charts), std::move(tableIds), std::move(plotHandleIds), std::move(tableMaps), std::move(tableMapIds), std::move(errors));
}
FigureDescriptor::FigureDescriptor(Private, std::shared_ptr<std::string> title, std::shared_ptr<std::string> titleFont, std::shared_ptr<std::string> titleColor, bool resizable, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::ThemeDescriptor> theme, bool isDefaultTheme, double updateInterval, int32_t cols, int32_t rows, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::ChartDescriptor>>> charts, std::shared_ptr<std::vector<int32_t>> tableIds, std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>> plotHandleIds, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle>>> tableMaps, std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>> tableMapIds, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> errors)
  : title_(std::move(title)), titleFont_(std::move(titleFont)), titleColor_(std::move(titleColor)), resizable_(resizable), theme_(std::move(theme)), isDefaultTheme_(isDefaultTheme), updateInterval_(updateInterval), cols_(cols), rows_(rows), charts_(std::move(charts)), tableIds_(std::move(tableIds)), plotHandleIds_(std::move(plotHandleIds)), tableMaps_(std::move(tableMaps)), tableMapIds_(std::move(tableMapIds)), errors_(std::move(errors))
  {
}
FigureDescriptor::~FigureDescriptor() = default;
void FigureDescriptor::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&title_);
  sa.write(&titleFont_);
  sa.write(&titleColor_);
  sa.write(&resizable_);
  sa.write(&theme_);
  sa.write(&isDefaultTheme_);
  sa.write(&updateInterval_);
  sa.write(&cols_);
  sa.write(&rows_);
  sa.write(&charts_);
  sa.write(&tableIds_);
  sa.write(&plotHandleIds_);
  sa.write(&tableMaps_);
  sa.write(&tableMapIds_);
  sa.write(&errors_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> FigureDescriptor::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::string> title;
  std::shared_ptr<std::string> titleFont;
  std::shared_ptr<std::string> titleColor;
  bool resizable;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::ThemeDescriptor> theme;
  bool isDefaultTheme;
  double updateInterval;
  int32_t cols;
  int32_t rows;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::ChartDescriptor>>> charts;
  std::shared_ptr<std::vector<int32_t>> tableIds;
  std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>> plotHandleIds;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableMapHandle>>> tableMaps;
  std::shared_ptr<std::vector<std::shared_ptr<std::vector<int32_t>>>> tableMapIds;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> errors;
  da.read(&title);
  da.read(&titleFont);
  da.read(&titleColor);
  da.read(&resizable);
  da.read(&theme);
  da.read(&isDefaultTheme);
  da.read(&updateInterval);
  da.read(&cols);
  da.read(&rows);
  da.read(&charts);
  da.read(&tableIds);
  da.read(&plotHandleIds);
  da.read(&tableMaps);
  da.read(&tableMapIds);
  da.read(&errors);
  return FigureDescriptor::create(std::move(title), std::move(titleFont), std::move(titleColor), resizable, std::move(theme), isDefaultTheme, updateInterval, cols, rows, std::move(charts), std::move(tableIds), std::move(plotHandleIds), std::move(tableMaps), std::move(tableMapIds), std::move(errors));
}
const boost::string_view MultiSeriesDescriptor::typeName("com.illumon.iris.web.shared.data.plot.MultiSeriesDescriptor");
std::shared_ptr<MultiSeriesDescriptor> MultiSeriesDescriptor::create(deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SeriesPlotStyle plotStyle, std::shared_ptr<std::string> name, std::shared_ptr<std::string> lineColorDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> lineColorKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> lineColorValues, std::shared_ptr<std::string> pointColorDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointColorKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointColorValues, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> linesVisibleDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> linesVisibleKeys, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean>>> linesVisibleValues, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> pointsVisibleDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointsVisibleKeys, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean>>> pointsVisibleValues, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> gradientVisibleDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> gradientVisibleKeys, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean>>> gradientVisibleValues, std::shared_ptr<std::string> pointLabelFormatDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointLabelFormatKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointLabelFormatValues, std::shared_ptr<std::string> xToolTipPatternDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> xToolTipPatternKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> xToolTipPatternValues, std::shared_ptr<std::string> yToolTipPatternDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> yToolTipPatternKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> yToolTipPatternValues, std::shared_ptr<std::string> pointLabelDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointLabelKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointLabelValues, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Double> pointSizeDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointSizeKeys, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Double>>> pointSizeValues, std::shared_ptr<std::string> pointShapeDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointShapeKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointShapeValues, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::MultiSeriesSourceDescriptor>>> dataSources) {
  return std::make_shared<MultiSeriesDescriptor>(Private(), plotStyle, std::move(name), std::move(lineColorDefault), std::move(lineColorKeys), std::move(lineColorValues), std::move(pointColorDefault), std::move(pointColorKeys), std::move(pointColorValues), std::move(linesVisibleDefault), std::move(linesVisibleKeys), std::move(linesVisibleValues), std::move(pointsVisibleDefault), std::move(pointsVisibleKeys), std::move(pointsVisibleValues), std::move(gradientVisibleDefault), std::move(gradientVisibleKeys), std::move(gradientVisibleValues), std::move(pointLabelFormatDefault), std::move(pointLabelFormatKeys), std::move(pointLabelFormatValues), std::move(xToolTipPatternDefault), std::move(xToolTipPatternKeys), std::move(xToolTipPatternValues), std::move(yToolTipPatternDefault), std::move(yToolTipPatternKeys), std::move(yToolTipPatternValues), std::move(pointLabelDefault), std::move(pointLabelKeys), std::move(pointLabelValues), std::move(pointSizeDefault), std::move(pointSizeKeys), std::move(pointSizeValues), std::move(pointShapeDefault), std::move(pointShapeKeys), std::move(pointShapeValues), std::move(dataSources));
}
MultiSeriesDescriptor::MultiSeriesDescriptor(Private, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SeriesPlotStyle plotStyle, std::shared_ptr<std::string> name, std::shared_ptr<std::string> lineColorDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> lineColorKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> lineColorValues, std::shared_ptr<std::string> pointColorDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointColorKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointColorValues, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> linesVisibleDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> linesVisibleKeys, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean>>> linesVisibleValues, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> pointsVisibleDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointsVisibleKeys, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean>>> pointsVisibleValues, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> gradientVisibleDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> gradientVisibleKeys, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean>>> gradientVisibleValues, std::shared_ptr<std::string> pointLabelFormatDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointLabelFormatKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointLabelFormatValues, std::shared_ptr<std::string> xToolTipPatternDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> xToolTipPatternKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> xToolTipPatternValues, std::shared_ptr<std::string> yToolTipPatternDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> yToolTipPatternKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> yToolTipPatternValues, std::shared_ptr<std::string> pointLabelDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointLabelKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointLabelValues, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Double> pointSizeDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointSizeKeys, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Double>>> pointSizeValues, std::shared_ptr<std::string> pointShapeDefault, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointShapeKeys, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointShapeValues, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::MultiSeriesSourceDescriptor>>> dataSources)
  : plotStyle_(plotStyle), name_(std::move(name)), lineColorDefault_(std::move(lineColorDefault)), lineColorKeys_(std::move(lineColorKeys)), lineColorValues_(std::move(lineColorValues)), pointColorDefault_(std::move(pointColorDefault)), pointColorKeys_(std::move(pointColorKeys)), pointColorValues_(std::move(pointColorValues)), linesVisibleDefault_(std::move(linesVisibleDefault)), linesVisibleKeys_(std::move(linesVisibleKeys)), linesVisibleValues_(std::move(linesVisibleValues)), pointsVisibleDefault_(std::move(pointsVisibleDefault)), pointsVisibleKeys_(std::move(pointsVisibleKeys)), pointsVisibleValues_(std::move(pointsVisibleValues)), gradientVisibleDefault_(std::move(gradientVisibleDefault)), gradientVisibleKeys_(std::move(gradientVisibleKeys)), gradientVisibleValues_(std::move(gradientVisibleValues)), pointLabelFormatDefault_(std::move(pointLabelFormatDefault)), pointLabelFormatKeys_(std::move(pointLabelFormatKeys)), pointLabelFormatValues_(std::move(pointLabelFormatValues)), xToolTipPatternDefault_(std::move(xToolTipPatternDefault)), xToolTipPatternKeys_(std::move(xToolTipPatternKeys)), xToolTipPatternValues_(std::move(xToolTipPatternValues)), yToolTipPatternDefault_(std::move(yToolTipPatternDefault)), yToolTipPatternKeys_(std::move(yToolTipPatternKeys)), yToolTipPatternValues_(std::move(yToolTipPatternValues)), pointLabelDefault_(std::move(pointLabelDefault)), pointLabelKeys_(std::move(pointLabelKeys)), pointLabelValues_(std::move(pointLabelValues)), pointSizeDefault_(std::move(pointSizeDefault)), pointSizeKeys_(std::move(pointSizeKeys)), pointSizeValues_(std::move(pointSizeValues)), pointShapeDefault_(std::move(pointShapeDefault)), pointShapeKeys_(std::move(pointShapeKeys)), pointShapeValues_(std::move(pointShapeValues)), dataSources_(std::move(dataSources))
  {
}
MultiSeriesDescriptor::~MultiSeriesDescriptor() = default;
void MultiSeriesDescriptor::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&plotStyle_);
  sa.write(&name_);
  sa.write(&lineColorDefault_);
  sa.write(&lineColorKeys_);
  sa.write(&lineColorValues_);
  sa.write(&pointColorDefault_);
  sa.write(&pointColorKeys_);
  sa.write(&pointColorValues_);
  sa.write(&linesVisibleDefault_);
  sa.write(&linesVisibleKeys_);
  sa.write(&linesVisibleValues_);
  sa.write(&pointsVisibleDefault_);
  sa.write(&pointsVisibleKeys_);
  sa.write(&pointsVisibleValues_);
  sa.write(&gradientVisibleDefault_);
  sa.write(&gradientVisibleKeys_);
  sa.write(&gradientVisibleValues_);
  sa.write(&pointLabelFormatDefault_);
  sa.write(&pointLabelFormatKeys_);
  sa.write(&pointLabelFormatValues_);
  sa.write(&xToolTipPatternDefault_);
  sa.write(&xToolTipPatternKeys_);
  sa.write(&xToolTipPatternValues_);
  sa.write(&yToolTipPatternDefault_);
  sa.write(&yToolTipPatternKeys_);
  sa.write(&yToolTipPatternValues_);
  sa.write(&pointLabelDefault_);
  sa.write(&pointLabelKeys_);
  sa.write(&pointLabelValues_);
  sa.write(&pointSizeDefault_);
  sa.write(&pointSizeKeys_);
  sa.write(&pointSizeValues_);
  sa.write(&pointShapeDefault_);
  sa.write(&pointShapeKeys_);
  sa.write(&pointShapeValues_);
  sa.write(&dataSources_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> MultiSeriesDescriptor::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SeriesPlotStyle plotStyle;
  std::shared_ptr<std::string> name;
  std::shared_ptr<std::string> lineColorDefault;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> lineColorKeys;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> lineColorValues;
  std::shared_ptr<std::string> pointColorDefault;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointColorKeys;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointColorValues;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> linesVisibleDefault;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> linesVisibleKeys;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean>>> linesVisibleValues;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> pointsVisibleDefault;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointsVisibleKeys;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean>>> pointsVisibleValues;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> gradientVisibleDefault;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> gradientVisibleKeys;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean>>> gradientVisibleValues;
  std::shared_ptr<std::string> pointLabelFormatDefault;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointLabelFormatKeys;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointLabelFormatValues;
  std::shared_ptr<std::string> xToolTipPatternDefault;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> xToolTipPatternKeys;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> xToolTipPatternValues;
  std::shared_ptr<std::string> yToolTipPatternDefault;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> yToolTipPatternKeys;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> yToolTipPatternValues;
  std::shared_ptr<std::string> pointLabelDefault;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointLabelKeys;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointLabelValues;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Double> pointSizeDefault;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointSizeKeys;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Double>>> pointSizeValues;
  std::shared_ptr<std::string> pointShapeDefault;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointShapeKeys;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> pointShapeValues;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::MultiSeriesSourceDescriptor>>> dataSources;
  da.read(&plotStyle);
  da.read(&name);
  da.read(&lineColorDefault);
  da.read(&lineColorKeys);
  da.read(&lineColorValues);
  da.read(&pointColorDefault);
  da.read(&pointColorKeys);
  da.read(&pointColorValues);
  da.read(&linesVisibleDefault);
  da.read(&linesVisibleKeys);
  da.read(&linesVisibleValues);
  da.read(&pointsVisibleDefault);
  da.read(&pointsVisibleKeys);
  da.read(&pointsVisibleValues);
  da.read(&gradientVisibleDefault);
  da.read(&gradientVisibleKeys);
  da.read(&gradientVisibleValues);
  da.read(&pointLabelFormatDefault);
  da.read(&pointLabelFormatKeys);
  da.read(&pointLabelFormatValues);
  da.read(&xToolTipPatternDefault);
  da.read(&xToolTipPatternKeys);
  da.read(&xToolTipPatternValues);
  da.read(&yToolTipPatternDefault);
  da.read(&yToolTipPatternKeys);
  da.read(&yToolTipPatternValues);
  da.read(&pointLabelDefault);
  da.read(&pointLabelKeys);
  da.read(&pointLabelValues);
  da.read(&pointSizeDefault);
  da.read(&pointSizeKeys);
  da.read(&pointSizeValues);
  da.read(&pointShapeDefault);
  da.read(&pointShapeKeys);
  da.read(&pointShapeValues);
  da.read(&dataSources);
  return MultiSeriesDescriptor::create(plotStyle, std::move(name), std::move(lineColorDefault), std::move(lineColorKeys), std::move(lineColorValues), std::move(pointColorDefault), std::move(pointColorKeys), std::move(pointColorValues), std::move(linesVisibleDefault), std::move(linesVisibleKeys), std::move(linesVisibleValues), std::move(pointsVisibleDefault), std::move(pointsVisibleKeys), std::move(pointsVisibleValues), std::move(gradientVisibleDefault), std::move(gradientVisibleKeys), std::move(gradientVisibleValues), std::move(pointLabelFormatDefault), std::move(pointLabelFormatKeys), std::move(pointLabelFormatValues), std::move(xToolTipPatternDefault), std::move(xToolTipPatternKeys), std::move(xToolTipPatternValues), std::move(yToolTipPatternDefault), std::move(yToolTipPatternKeys), std::move(yToolTipPatternValues), std::move(pointLabelDefault), std::move(pointLabelKeys), std::move(pointLabelValues), std::move(pointSizeDefault), std::move(pointSizeKeys), std::move(pointSizeValues), std::move(pointShapeDefault), std::move(pointShapeKeys), std::move(pointShapeValues), std::move(dataSources));
}
const boost::string_view MultiSeriesSourceDescriptor::typeName("com.illumon.iris.web.shared.data.plot.MultiSeriesSourceDescriptor");
std::shared_ptr<MultiSeriesSourceDescriptor> MultiSeriesSourceDescriptor::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::AxisDescriptor> axis, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SourceType type, int32_t tableMapId, std::shared_ptr<std::string> columnName) {
  return std::make_shared<MultiSeriesSourceDescriptor>(Private(), std::move(axis), type, tableMapId, std::move(columnName));
}
MultiSeriesSourceDescriptor::MultiSeriesSourceDescriptor(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::AxisDescriptor> axis, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SourceType type, int32_t tableMapId, std::shared_ptr<std::string> columnName)
  : axis_(std::move(axis)), type_(type), tableMapId_(tableMapId), columnName_(std::move(columnName))
  {
}
MultiSeriesSourceDescriptor::~MultiSeriesSourceDescriptor() = default;
void MultiSeriesSourceDescriptor::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&axis_);
  sa.write(&type_);
  sa.write(&tableMapId_);
  sa.write(&columnName_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> MultiSeriesSourceDescriptor::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::AxisDescriptor> axis;
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SourceType type;
  int32_t tableMapId;
  std::shared_ptr<std::string> columnName;
  da.read(&axis);
  da.read(&type);
  da.read(&tableMapId);
  da.read(&columnName);
  return MultiSeriesSourceDescriptor::create(std::move(axis), type, tableMapId, std::move(columnName));
}
const boost::string_view OneClickDescriptor::typeName("com.illumon.iris.web.shared.data.plot.OneClickDescriptor");
std::shared_ptr<OneClickDescriptor> OneClickDescriptor::create(std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columns, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnTypes, bool requireAllFiltersToDisplay) {
  return std::make_shared<OneClickDescriptor>(Private(), std::move(columns), std::move(columnTypes), requireAllFiltersToDisplay);
}
OneClickDescriptor::OneClickDescriptor(Private, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columns, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnTypes, bool requireAllFiltersToDisplay)
  : columns_(std::move(columns)), columnTypes_(std::move(columnTypes)), requireAllFiltersToDisplay_(requireAllFiltersToDisplay)
  {
}
OneClickDescriptor::~OneClickDescriptor() = default;
void OneClickDescriptor::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&columns_);
  sa.write(&columnTypes_);
  sa.write(&requireAllFiltersToDisplay_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> OneClickDescriptor::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columns;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> columnTypes;
  bool requireAllFiltersToDisplay;
  da.read(&columns);
  da.read(&columnTypes);
  da.read(&requireAllFiltersToDisplay);
  return OneClickDescriptor::create(std::move(columns), std::move(columnTypes), requireAllFiltersToDisplay);
}
const boost::string_view SeriesDescriptor::typeName("com.illumon.iris.web.shared.data.plot.SeriesDescriptor");
std::shared_ptr<SeriesDescriptor> SeriesDescriptor::create(deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SeriesPlotStyle plotStyle, std::shared_ptr<std::string> name, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> linesVisible, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> shapesVisible, bool gradientVisible, std::shared_ptr<std::string> lineColor, std::shared_ptr<std::string> pointLabelFormat, std::shared_ptr<std::string> xToolTipPattern, std::shared_ptr<std::string> yToolTipPattern, std::shared_ptr<std::string> shapeLabel, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Double> shapeSize, std::shared_ptr<std::string> shapeColor, std::shared_ptr<std::string> shape, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SourceDescriptor>>> dataSources) {
  return std::make_shared<SeriesDescriptor>(Private(), plotStyle, std::move(name), std::move(linesVisible), std::move(shapesVisible), gradientVisible, std::move(lineColor), std::move(pointLabelFormat), std::move(xToolTipPattern), std::move(yToolTipPattern), std::move(shapeLabel), std::move(shapeSize), std::move(shapeColor), std::move(shape), std::move(dataSources));
}
SeriesDescriptor::SeriesDescriptor(Private, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SeriesPlotStyle plotStyle, std::shared_ptr<std::string> name, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> linesVisible, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> shapesVisible, bool gradientVisible, std::shared_ptr<std::string> lineColor, std::shared_ptr<std::string> pointLabelFormat, std::shared_ptr<std::string> xToolTipPattern, std::shared_ptr<std::string> yToolTipPattern, std::shared_ptr<std::string> shapeLabel, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Double> shapeSize, std::shared_ptr<std::string> shapeColor, std::shared_ptr<std::string> shape, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SourceDescriptor>>> dataSources)
  : plotStyle_(plotStyle), name_(std::move(name)), linesVisible_(std::move(linesVisible)), shapesVisible_(std::move(shapesVisible)), gradientVisible_(gradientVisible), lineColor_(std::move(lineColor)), pointLabelFormat_(std::move(pointLabelFormat)), xToolTipPattern_(std::move(xToolTipPattern)), yToolTipPattern_(std::move(yToolTipPattern)), shapeLabel_(std::move(shapeLabel)), shapeSize_(std::move(shapeSize)), shapeColor_(std::move(shapeColor)), shape_(std::move(shape)), dataSources_(std::move(dataSources))
  {
}
SeriesDescriptor::~SeriesDescriptor() = default;
void SeriesDescriptor::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&plotStyle_);
  sa.write(&name_);
  sa.write(&linesVisible_);
  sa.write(&shapesVisible_);
  sa.write(&gradientVisible_);
  sa.write(&lineColor_);
  sa.write(&pointLabelFormat_);
  sa.write(&xToolTipPattern_);
  sa.write(&yToolTipPattern_);
  sa.write(&shapeLabel_);
  sa.write(&shapeSize_);
  sa.write(&shapeColor_);
  sa.write(&shape_);
  sa.write(&dataSources_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> SeriesDescriptor::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SeriesPlotStyle plotStyle;
  std::shared_ptr<std::string> name;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> linesVisible;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Boolean> shapesVisible;
  bool gradientVisible;
  std::shared_ptr<std::string> lineColor;
  std::shared_ptr<std::string> pointLabelFormat;
  std::shared_ptr<std::string> xToolTipPattern;
  std::shared_ptr<std::string> yToolTipPattern;
  std::shared_ptr<std::string> shapeLabel;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::lang::Double> shapeSize;
  std::shared_ptr<std::string> shapeColor;
  std::shared_ptr<std::string> shape;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SourceDescriptor>>> dataSources;
  da.read(&plotStyle);
  da.read(&name);
  da.read(&linesVisible);
  da.read(&shapesVisible);
  da.read(&gradientVisible);
  da.read(&lineColor);
  da.read(&pointLabelFormat);
  da.read(&xToolTipPattern);
  da.read(&yToolTipPattern);
  da.read(&shapeLabel);
  da.read(&shapeSize);
  da.read(&shapeColor);
  da.read(&shape);
  da.read(&dataSources);
  return SeriesDescriptor::create(plotStyle, std::move(name), std::move(linesVisible), std::move(shapesVisible), gradientVisible, std::move(lineColor), std::move(pointLabelFormat), std::move(xToolTipPattern), std::move(yToolTipPattern), std::move(shapeLabel), std::move(shapeSize), std::move(shapeColor), std::move(shape), std::move(dataSources));
}
const boost::string_view SourceDescriptor::typeName("com.illumon.iris.web.shared.data.plot.SourceDescriptor");
std::shared_ptr<SourceDescriptor> SourceDescriptor::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::AxisDescriptor> axis, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SourceType type, int32_t tableId, int32_t tableMapId, std::shared_ptr<std::string> columnName, std::shared_ptr<std::string> columnType, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::OneClickDescriptor> oneClick) {
  return std::make_shared<SourceDescriptor>(Private(), std::move(axis), type, tableId, tableMapId, std::move(columnName), std::move(columnType), std::move(oneClick));
}
SourceDescriptor::SourceDescriptor(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::AxisDescriptor> axis, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SourceType type, int32_t tableId, int32_t tableMapId, std::shared_ptr<std::string> columnName, std::shared_ptr<std::string> columnType, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::OneClickDescriptor> oneClick)
  : axis_(std::move(axis)), type_(type), tableId_(tableId), tableMapId_(tableMapId), columnName_(std::move(columnName)), columnType_(std::move(columnType)), oneClick_(std::move(oneClick))
  {
}
SourceDescriptor::~SourceDescriptor() = default;
void SourceDescriptor::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&axis_);
  sa.write(&type_);
  sa.write(&tableId_);
  sa.write(&tableMapId_);
  sa.write(&columnName_);
  sa.write(&columnType_);
  sa.write(&oneClick_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> SourceDescriptor::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::AxisDescriptor> axis;
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::SourceType type;
  int32_t tableId;
  int32_t tableMapId;
  std::shared_ptr<std::string> columnName;
  std::shared_ptr<std::string> columnType;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::plot::OneClickDescriptor> oneClick;
  da.read(&axis);
  da.read(&type);
  da.read(&tableId);
  da.read(&tableMapId);
  da.read(&columnName);
  da.read(&columnType);
  da.read(&oneClick);
  return SourceDescriptor::create(std::move(axis), type, tableId, tableMapId, std::move(columnName), std::move(columnType), std::move(oneClick));
}
const boost::string_view ThemeDescriptor::typeName("com.illumon.iris.web.shared.data.plot.ThemeDescriptor");
std::shared_ptr<ThemeDescriptor> ThemeDescriptor::create() {
  return std::make_shared<ThemeDescriptor>(Private());
}
ThemeDescriptor::ThemeDescriptor(Private)
  
  {
}
ThemeDescriptor::~ThemeDescriptor() = default;
void ThemeDescriptor::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> ThemeDescriptor::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  return ThemeDescriptor::create();
}
}  // namespace plot
namespace treetable {
const boost::string_view Key::typeName("com.illumon.iris.web.shared.data.treetable.Key");
Key::Key(Private, deephaven::openAPI::lowlevel::remoting::custom::com::illumon::iris::web::shared::data::treetable::KeyCustom custom)
  : custom_(std::move(custom))
  {
}
Key::~Key() = default;
void Key::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  custom_.serialize(serializer);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> Key::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  auto custom = deephaven::openAPI::lowlevel::remoting::custom::com::illumon::iris::web::shared::data::treetable::KeyCustom::deserialize(deserializer);
  return Key::create(std::move(custom));
}
const boost::string_view TableDetails::typeName("com.illumon.iris.web.shared.data.treetable.TableDetails");
std::shared_ptr<TableDetails> TableDetails::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::Key> key, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::Key>>> children) {
  return std::make_shared<TableDetails>(Private(), std::move(key), std::move(children));
}
TableDetails::TableDetails(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::Key> key, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::Key>>> children)
  : key_(std::move(key)), children_(std::move(children))
  {
}
TableDetails::~TableDetails() = default;
void TableDetails::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&key_);
  sa.write(&children_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> TableDetails::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::Key> key;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::Key>>> children;
  da.read(&key);
  da.read(&children);
  return TableDetails::create(std::move(key), std::move(children));
}
const boost::string_view TreeTableRequest::typeName("com.illumon.iris.web.shared.data.treetable.TreeTableRequest");
std::shared_ptr<TreeTableRequest> TreeTableRequest::create(int64_t viewportStart, int64_t viewportEnd, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> columns, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::FilterDescriptor>>> filters, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::SortDescriptor>>> sorts, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::TableDetails>>> expandedNodes, int32_t keyColumn, std::shared_ptr<std::vector<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::treeTableRequest::TreeRequestOperation>> includedOps, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> sourceTable) {
  return std::make_shared<TreeTableRequest>(Private(), viewportStart, viewportEnd, std::move(columns), std::move(filters), std::move(sorts), std::move(expandedNodes), keyColumn, std::move(includedOps), std::move(sourceTable));
}
TreeTableRequest::TreeTableRequest(Private, int64_t viewportStart, int64_t viewportEnd, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> columns, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::FilterDescriptor>>> filters, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::SortDescriptor>>> sorts, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::TableDetails>>> expandedNodes, int32_t keyColumn, std::shared_ptr<std::vector<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::treeTableRequest::TreeRequestOperation>> includedOps, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> sourceTable)
  : viewportStart_(viewportStart), viewportEnd_(viewportEnd), columns_(std::move(columns)), filters_(std::move(filters)), sorts_(std::move(sorts)), expandedNodes_(std::move(expandedNodes)), keyColumn_(keyColumn), includedOps_(std::move(includedOps)), sourceTable_(std::move(sourceTable))
  {
}
TreeTableRequest::~TreeTableRequest() = default;
void TreeTableRequest::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&viewportStart_);
  sa.write(&viewportEnd_);
  sa.write(&columns_);
  sa.write(&filters_);
  sa.write(&sorts_);
  sa.write(&expandedNodes_);
  sa.write(&keyColumn_);
  sa.write(&includedOps_);
  sa.write(&sourceTable_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> TreeTableRequest::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  int64_t viewportStart;
  int64_t viewportEnd;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> columns;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::FilterDescriptor>>> filters;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::SortDescriptor>>> sorts;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::TableDetails>>> expandedNodes;
  int32_t keyColumn;
  std::shared_ptr<std::vector<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::treeTableRequest::TreeRequestOperation>> includedOps;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> sourceTable;
  da.read(&viewportStart);
  da.read(&viewportEnd);
  da.read(&columns);
  da.read(&filters);
  da.read(&sorts);
  da.read(&expandedNodes);
  da.read(&keyColumn);
  da.read(&includedOps);
  da.read(&sourceTable);
  return TreeTableRequest::create(viewportStart, viewportEnd, std::move(columns), std::move(filters), std::move(sorts), std::move(expandedNodes), keyColumn, std::move(includedOps), std::move(sourceTable));
}
const boost::string_view TreeTableResult::typeName("com.illumon.iris.web.shared.data.treetable.TreeTableResult");
std::shared_ptr<TreeTableResult> TreeTableResult::create(int64_t treeSize, int64_t snapshotStart, int64_t snapshotEnd, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData>>> snapshotData, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> constituentColumnNames, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData>>> constituentColumnData, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::TableDetails>>> tableDetails, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::Key>>> keyColumn, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::Key>>> parentKeyColumn, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> childPresence, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> sourceTable) {
  return std::make_shared<TreeTableResult>(Private(), treeSize, snapshotStart, snapshotEnd, std::move(snapshotData), std::move(constituentColumnNames), std::move(constituentColumnData), std::move(tableDetails), std::move(keyColumn), std::move(parentKeyColumn), std::move(childPresence), std::move(sourceTable));
}
TreeTableResult::TreeTableResult(Private, int64_t treeSize, int64_t snapshotStart, int64_t snapshotEnd, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData>>> snapshotData, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> constituentColumnNames, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData>>> constituentColumnData, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::TableDetails>>> tableDetails, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::Key>>> keyColumn, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::Key>>> parentKeyColumn, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> childPresence, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> sourceTable)
  : treeSize_(treeSize), snapshotStart_(snapshotStart), snapshotEnd_(snapshotEnd), snapshotData_(std::move(snapshotData)), constituentColumnNames_(std::move(constituentColumnNames)), constituentColumnData_(std::move(constituentColumnData)), tableDetails_(std::move(tableDetails)), keyColumn_(std::move(keyColumn)), parentKeyColumn_(std::move(parentKeyColumn)), childPresence_(std::move(childPresence)), sourceTable_(std::move(sourceTable))
  {
}
TreeTableResult::~TreeTableResult() = default;
void TreeTableResult::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&treeSize_);
  sa.write(&snapshotStart_);
  sa.write(&snapshotEnd_);
  sa.write(&snapshotData_);
  sa.write(&constituentColumnNames_);
  sa.write(&constituentColumnData_);
  sa.write(&tableDetails_);
  sa.write(&keyColumn_);
  sa.write(&parentKeyColumn_);
  sa.write(&childPresence_);
  sa.write(&sourceTable_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> TreeTableResult::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  int64_t treeSize;
  int64_t snapshotStart;
  int64_t snapshotEnd;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData>>> snapshotData;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> constituentColumnNames;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData>>> constituentColumnData;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::TableDetails>>> tableDetails;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::Key>>> keyColumn;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::treetable::Key>>> parentKeyColumn;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::java::util::BitSet> childPresence;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle> sourceTable;
  da.read(&treeSize);
  da.read(&snapshotStart);
  da.read(&snapshotEnd);
  da.read(&snapshotData);
  da.read(&constituentColumnNames);
  da.read(&constituentColumnData);
  da.read(&tableDetails);
  da.read(&keyColumn);
  da.read(&parentKeyColumn);
  da.read(&childPresence);
  da.read(&sourceTable);
  return TreeTableResult::create(treeSize, snapshotStart, snapshotEnd, std::move(snapshotData), std::move(constituentColumnNames), std::move(constituentColumnData), std::move(tableDetails), std::move(keyColumn), std::move(parentKeyColumn), std::move(childPresence), std::move(sourceTable));
}
}  // namespace treetable
namespace workspace {
const boost::string_view WorkspaceData::typeName("com.illumon.iris.web.shared.data.workspace.WorkspaceData");
std::shared_ptr<WorkspaceData> WorkspaceData::create(std::shared_ptr<std::string> id, int32_t version, std::shared_ptr<std::string> name, std::shared_ptr<std::string> owner, std::shared_ptr<std::string> dataType, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::workspace::ItemStatus status, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> adminGroups, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> viewerGroups, std::shared_ptr<std::string> data) {
  return std::make_shared<WorkspaceData>(Private(), std::move(id), version, std::move(name), std::move(owner), std::move(dataType), status, std::move(adminGroups), std::move(viewerGroups), std::move(data));
}
WorkspaceData::WorkspaceData(Private, std::shared_ptr<std::string> id, int32_t version, std::shared_ptr<std::string> name, std::shared_ptr<std::string> owner, std::shared_ptr<std::string> dataType, deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::workspace::ItemStatus status, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> adminGroups, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> viewerGroups, std::shared_ptr<std::string> data)
  : id_(std::move(id)), version_(version), name_(std::move(name)), owner_(std::move(owner)), dataType_(std::move(dataType)), status_(status), adminGroups_(std::move(adminGroups)), viewerGroups_(std::move(viewerGroups)), data_(std::move(data))
  {
}
WorkspaceData::~WorkspaceData() = default;
void WorkspaceData::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&id_);
  sa.write(&version_);
  sa.write(&name_);
  sa.write(&owner_);
  sa.write(&dataType_);
  sa.write(&status_);
  sa.write(&adminGroups_);
  sa.write(&viewerGroups_);
  sa.write(&data_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> WorkspaceData::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::string> id;
  int32_t version;
  std::shared_ptr<std::string> name;
  std::shared_ptr<std::string> owner;
  std::shared_ptr<std::string> dataType;
  deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::workspace::ItemStatus status;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> adminGroups;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> viewerGroups;
  std::shared_ptr<std::string> data;
  da.read(&id);
  da.read(&version);
  da.read(&name);
  da.read(&owner);
  da.read(&dataType);
  da.read(&status);
  da.read(&adminGroups);
  da.read(&viewerGroups);
  da.read(&data);
  return WorkspaceData::create(std::move(id), version, std::move(name), std::move(owner), std::move(dataType), status, std::move(adminGroups), std::move(viewerGroups), std::move(data));
}
}  // namespace workspace
}  // namespace data
namespace ide {
const boost::string_view CommandResult::typeName("com.illumon.iris.web.shared.ide.CommandResult");
std::shared_ptr<CommandResult> CommandResult::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::VariableChanges> changes, std::shared_ptr<std::string> error) {
  return std::make_shared<CommandResult>(Private(), std::move(changes), std::move(error));
}
CommandResult::CommandResult(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::VariableChanges> changes, std::shared_ptr<std::string> error)
  : changes_(std::move(changes)), error_(std::move(error))
  {
}
CommandResult::~CommandResult() = default;
void CommandResult::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&changes_);
  sa.write(&error_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> CommandResult::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::VariableChanges> changes;
  std::shared_ptr<std::string> error;
  da.read(&changes);
  da.read(&error);
  return CommandResult::create(std::move(changes), std::move(error));
}
const boost::string_view ConsoleAddress::typeName("com.illumon.iris.web.shared.ide.ConsoleAddress");
std::shared_ptr<ConsoleAddress> ConsoleAddress::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ConnectToken> token, std::shared_ptr<std::string> websocketUrl, std::shared_ptr<std::string> serviceId) {
  return std::make_shared<ConsoleAddress>(Private(), std::move(token), std::move(websocketUrl), std::move(serviceId));
}
ConsoleAddress::ConsoleAddress(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ConnectToken> token, std::shared_ptr<std::string> websocketUrl, std::shared_ptr<std::string> serviceId)
  : token_(std::move(token)), websocketUrl_(std::move(websocketUrl)), serviceId_(std::move(serviceId))
  {
}
ConsoleAddress::~ConsoleAddress() = default;
void ConsoleAddress::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&token_);
  sa.write(&websocketUrl_);
  sa.write(&serviceId_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> ConsoleAddress::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::ConnectToken> token;
  std::shared_ptr<std::string> websocketUrl;
  std::shared_ptr<std::string> serviceId;
  da.read(&token);
  da.read(&websocketUrl);
  da.read(&serviceId);
  return ConsoleAddress::create(std::move(token), std::move(websocketUrl), std::move(serviceId));
}
const boost::string_view ConsoleConfig::typeName("com.illumon.iris.web.shared.ide.ConsoleConfig");
std::shared_ptr<ConsoleConfig> ConsoleConfig::create(std::shared_ptr<std::string> dispatcherHost, int32_t dispatcherPort, std::shared_ptr<std::string> jvmProfile, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> classpath, int32_t maxHeapMb, std::shared_ptr<std::string> queryDescription, bool debug, bool detailedGCLogging, bool omitDefaultGcParameters, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> jvmArgs, std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<std::string>>>>> envVars) {
  return std::make_shared<ConsoleConfig>(Private(), std::move(dispatcherHost), dispatcherPort, std::move(jvmProfile), std::move(classpath), maxHeapMb, std::move(queryDescription), debug, detailedGCLogging, omitDefaultGcParameters, std::move(jvmArgs), std::move(envVars));
}
ConsoleConfig::ConsoleConfig(Private, std::shared_ptr<std::string> dispatcherHost, int32_t dispatcherPort, std::shared_ptr<std::string> jvmProfile, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> classpath, int32_t maxHeapMb, std::shared_ptr<std::string> queryDescription, bool debug, bool detailedGCLogging, bool omitDefaultGcParameters, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> jvmArgs, std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<std::string>>>>> envVars)
  : dispatcherHost_(std::move(dispatcherHost)), dispatcherPort_(dispatcherPort), jvmProfile_(std::move(jvmProfile)), classpath_(std::move(classpath)), maxHeapMb_(maxHeapMb), queryDescription_(std::move(queryDescription)), debug_(debug), detailedGCLogging_(detailedGCLogging), omitDefaultGcParameters_(omitDefaultGcParameters), jvmArgs_(std::move(jvmArgs)), envVars_(std::move(envVars))
  {
}
ConsoleConfig::~ConsoleConfig() = default;
void ConsoleConfig::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&dispatcherHost_);
  sa.write(&dispatcherPort_);
  sa.write(&jvmProfile_);
  sa.write(&classpath_);
  sa.write(&maxHeapMb_);
  sa.write(&queryDescription_);
  sa.write(&debug_);
  sa.write(&detailedGCLogging_);
  sa.write(&omitDefaultGcParameters_);
  sa.write(&jvmArgs_);
  sa.write(&envVars_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> ConsoleConfig::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::string> dispatcherHost;
  int32_t dispatcherPort;
  std::shared_ptr<std::string> jvmProfile;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> classpath;
  int32_t maxHeapMb;
  std::shared_ptr<std::string> queryDescription;
  bool debug;
  bool detailedGCLogging;
  bool omitDefaultGcParameters;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> jvmArgs;
  std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<std::string>>>>> envVars;
  da.read(&dispatcherHost);
  da.read(&dispatcherPort);
  da.read(&jvmProfile);
  da.read(&classpath);
  da.read(&maxHeapMb);
  da.read(&queryDescription);
  da.read(&debug);
  da.read(&detailedGCLogging);
  da.read(&omitDefaultGcParameters);
  da.read(&jvmArgs);
  da.read(&envVars);
  return ConsoleConfig::create(std::move(dispatcherHost), dispatcherPort, std::move(jvmProfile), std::move(classpath), maxHeapMb, std::move(queryDescription), debug, detailedGCLogging, omitDefaultGcParameters, std::move(jvmArgs), std::move(envVars));
}
const boost::string_view ConsoleConnectionResult::typeName("com.illumon.iris.web.shared.ide.ConsoleConnectionResult");
std::shared_ptr<ConsoleConnectionResult> ConsoleConnectionResult::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> tables, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> widgets) {
  return std::make_shared<ConsoleConnectionResult>(Private(), std::move(handle), std::move(tables), std::move(widgets));
}
ConsoleConnectionResult::ConsoleConnectionResult(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> tables, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> widgets)
  : handle_(std::move(handle)), tables_(std::move(tables)), widgets_(std::move(widgets))
  {
}
ConsoleConnectionResult::~ConsoleConnectionResult() = default;
void ConsoleConnectionResult::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&handle_);
  sa.write(&tables_);
  sa.write(&widgets_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> ConsoleConnectionResult::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::ScriptHandle> handle;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> tables;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> widgets;
  da.read(&handle);
  da.read(&tables);
  da.read(&widgets);
  return ConsoleConnectionResult::create(std::move(handle), std::move(tables), std::move(widgets));
}
const boost::string_view ConsoleServerAddress::typeName("com.illumon.iris.web.shared.ide.ConsoleServerAddress");
std::shared_ptr<ConsoleServerAddress> ConsoleServerAddress::create(std::shared_ptr<std::string> host, std::shared_ptr<std::string> name, int32_t port) {
  return std::make_shared<ConsoleServerAddress>(Private(), std::move(host), std::move(name), port);
}
ConsoleServerAddress::ConsoleServerAddress(Private, std::shared_ptr<std::string> host, std::shared_ptr<std::string> name, int32_t port)
  : host_(std::move(host)), name_(std::move(name)), port_(port)
  {
}
ConsoleServerAddress::~ConsoleServerAddress() = default;
void ConsoleServerAddress::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&host_);
  sa.write(&name_);
  sa.write(&port_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> ConsoleServerAddress::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::string> host;
  std::shared_ptr<std::string> name;
  int32_t port;
  da.read(&host);
  da.read(&name);
  da.read(&port);
  return ConsoleServerAddress::create(std::move(host), std::move(name), port);
}
const boost::string_view ExecutionHandle::typeName("com.illumon.iris.web.shared.ide.ExecutionHandle");
ExecutionHandle::ExecutionHandle(Private, deephaven::openAPI::lowlevel::remoting::custom::com::illumon::iris::web::shared::ide::ExecutionHandleCustom custom)
  : custom_(std::move(custom))
  {
}
ExecutionHandle::~ExecutionHandle() = default;
void ExecutionHandle::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  custom_.serialize(serializer);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> ExecutionHandle::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  auto custom = deephaven::openAPI::lowlevel::remoting::custom::com::illumon::iris::web::shared::ide::ExecutionHandleCustom::deserialize(deserializer);
  return ExecutionHandle::create(std::move(custom));
}
const boost::string_view ScriptHandle::typeName("com.illumon.iris.web.shared.ide.ScriptHandle");
ScriptHandle::ScriptHandle(Private, deephaven::openAPI::lowlevel::remoting::custom::com::illumon::iris::web::shared::ide::ScriptHandleCustom custom)
  : custom_(std::move(custom))
  {
}
ScriptHandle::~ScriptHandle() = default;
void ScriptHandle::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  custom_.serialize(serializer);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> ScriptHandle::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  auto custom = deephaven::openAPI::lowlevel::remoting::custom::com::illumon::iris::web::shared::ide::ScriptHandleCustom::deserialize(deserializer);
  return ScriptHandle::create(std::move(custom));
}
const boost::string_view VariableChanges::typeName("com.illumon.iris.web.shared.ide.VariableChanges");
std::shared_ptr<VariableChanges> VariableChanges::create(std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::VariableDefinition>>> created, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::VariableDefinition>>> updated, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::VariableDefinition>>> removed) {
  return std::make_shared<VariableChanges>(Private(), std::move(created), std::move(updated), std::move(removed));
}
VariableChanges::VariableChanges(Private, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::VariableDefinition>>> created, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::VariableDefinition>>> updated, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::VariableDefinition>>> removed)
  : created_(std::move(created)), updated_(std::move(updated)), removed_(std::move(removed))
  {
}
VariableChanges::~VariableChanges() = default;
void VariableChanges::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&created_);
  sa.write(&updated_);
  sa.write(&removed_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> VariableChanges::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::VariableDefinition>>> created;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::VariableDefinition>>> updated;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::VariableDefinition>>> removed;
  da.read(&created);
  da.read(&updated);
  da.read(&removed);
  return VariableChanges::create(std::move(created), std::move(updated), std::move(removed));
}
const boost::string_view VariableDefinition::typeName("com.illumon.iris.web.shared.ide.VariableDefinition");
std::shared_ptr<VariableDefinition> VariableDefinition::create(std::shared_ptr<std::string> name, std::shared_ptr<std::string> type) {
  return std::make_shared<VariableDefinition>(Private(), std::move(name), std::move(type));
}
VariableDefinition::VariableDefinition(Private, std::shared_ptr<std::string> name, std::shared_ptr<std::string> type)
  : name_(std::move(name)), type_(std::move(type))
  {
}
VariableDefinition::~VariableDefinition() = default;
void VariableDefinition::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&name_);
  sa.write(&type_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> VariableDefinition::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::string> name;
  std::shared_ptr<std::string> type;
  da.read(&name);
  da.read(&type);
  return VariableDefinition::create(std::move(name), std::move(type));
}
namespace lsp {
const boost::string_view CompletionContext::typeName("com.illumon.iris.web.shared.ide.lsp.CompletionContext");
std::shared_ptr<CompletionContext> CompletionContext::create(int32_t triggerKind, std::shared_ptr<std::string> triggerCharacter) {
  return std::make_shared<CompletionContext>(Private(), triggerKind, std::move(triggerCharacter));
}
CompletionContext::CompletionContext(Private, int32_t triggerKind, std::shared_ptr<std::string> triggerCharacter)
  : triggerKind_(triggerKind), triggerCharacter_(std::move(triggerCharacter))
  {
}
CompletionContext::~CompletionContext() = default;
void CompletionContext::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&triggerKind_);
  sa.write(&triggerCharacter_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> CompletionContext::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  int32_t triggerKind;
  std::shared_ptr<std::string> triggerCharacter;
  da.read(&triggerKind);
  da.read(&triggerCharacter);
  return CompletionContext::create(triggerKind, std::move(triggerCharacter));
}
const boost::string_view CompletionItem::typeName("com.illumon.iris.web.shared.ide.lsp.CompletionItem");
std::shared_ptr<CompletionItem> CompletionItem::create(std::shared_ptr<std::string> label, int32_t kind, std::shared_ptr<std::string> detail, std::shared_ptr<std::string> documentation, bool deprecated, bool preselect, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextEdit> textEdit, std::shared_ptr<std::string> sortText, std::shared_ptr<std::string> filterText, int32_t insertTextFormat, int32_t start, int32_t length, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextEdit>>> additionalTextEdits, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> commitCharacters) {
  return std::make_shared<CompletionItem>(Private(), std::move(label), kind, std::move(detail), std::move(documentation), deprecated, preselect, std::move(textEdit), std::move(sortText), std::move(filterText), insertTextFormat, start, length, std::move(additionalTextEdits), std::move(commitCharacters));
}
CompletionItem::CompletionItem(Private, std::shared_ptr<std::string> label, int32_t kind, std::shared_ptr<std::string> detail, std::shared_ptr<std::string> documentation, bool deprecated, bool preselect, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextEdit> textEdit, std::shared_ptr<std::string> sortText, std::shared_ptr<std::string> filterText, int32_t insertTextFormat, int32_t start, int32_t length, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextEdit>>> additionalTextEdits, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> commitCharacters)
  : label_(std::move(label)), kind_(kind), detail_(std::move(detail)), documentation_(std::move(documentation)), deprecated_(deprecated), preselect_(preselect), textEdit_(std::move(textEdit)), sortText_(std::move(sortText)), filterText_(std::move(filterText)), insertTextFormat_(insertTextFormat), start_(start), length_(length), additionalTextEdits_(std::move(additionalTextEdits)), commitCharacters_(std::move(commitCharacters))
  {
}
CompletionItem::~CompletionItem() = default;
void CompletionItem::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&label_);
  sa.write(&kind_);
  sa.write(&detail_);
  sa.write(&documentation_);
  sa.write(&deprecated_);
  sa.write(&preselect_);
  sa.write(&textEdit_);
  sa.write(&sortText_);
  sa.write(&filterText_);
  sa.write(&insertTextFormat_);
  sa.write(&start_);
  sa.write(&length_);
  sa.write(&additionalTextEdits_);
  sa.write(&commitCharacters_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> CompletionItem::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::string> label;
  int32_t kind;
  std::shared_ptr<std::string> detail;
  std::shared_ptr<std::string> documentation;
  bool deprecated;
  bool preselect;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextEdit> textEdit;
  std::shared_ptr<std::string> sortText;
  std::shared_ptr<std::string> filterText;
  int32_t insertTextFormat;
  int32_t start;
  int32_t length;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextEdit>>> additionalTextEdits;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> commitCharacters;
  da.read(&label);
  da.read(&kind);
  da.read(&detail);
  da.read(&documentation);
  da.read(&deprecated);
  da.read(&preselect);
  da.read(&textEdit);
  da.read(&sortText);
  da.read(&filterText);
  da.read(&insertTextFormat);
  da.read(&start);
  da.read(&length);
  da.read(&additionalTextEdits);
  da.read(&commitCharacters);
  return CompletionItem::create(std::move(label), kind, std::move(detail), std::move(documentation), deprecated, preselect, std::move(textEdit), std::move(sortText), std::move(filterText), insertTextFormat, start, length, std::move(additionalTextEdits), std::move(commitCharacters));
}
const boost::string_view TextDocumentPositionParams::typeName("com.illumon.iris.web.shared.ide.lsp.TextDocumentPositionParams");
std::shared_ptr<TextDocumentPositionParams> TextDocumentPositionParams::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentIdentifier> textDocument, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::Position> position) {
  return std::make_shared<TextDocumentPositionParams>(Private(), std::move(textDocument), std::move(position));
}
TextDocumentPositionParams::TextDocumentPositionParams(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentIdentifier> textDocument, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::Position> position)
  : textDocument_(std::move(textDocument)), position_(std::move(position))
  {
}
TextDocumentPositionParams::~TextDocumentPositionParams() = default;
void TextDocumentPositionParams::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&textDocument_);
  sa.write(&position_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> TextDocumentPositionParams::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentIdentifier> textDocument;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::Position> position;
  da.read(&textDocument);
  da.read(&position);
  return TextDocumentPositionParams::create(std::move(textDocument), std::move(position));
}
const boost::string_view CompletionParams::typeName("com.illumon.iris.web.shared.ide.lsp.CompletionParams");
std::shared_ptr<CompletionParams> CompletionParams::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentIdentifier> textDocument, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::Position> position, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::CompletionContext> context) {
  return std::make_shared<CompletionParams>(Private(), std::move(textDocument), std::move(position), std::move(context));
}
CompletionParams::CompletionParams(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentIdentifier> textDocument, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::Position> position, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::CompletionContext> context)
  : deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentPositionParams(Private(), std::move(textDocument), std::move(position)), context_(std::move(context))
  {
}
CompletionParams::~CompletionParams() = default;
void CompletionParams::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&context_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> CompletionParams::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentIdentifier> textDocument;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::Position> position;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::CompletionContext> context;
  da.read(&textDocument);
  da.read(&position);
  da.read(&context);
  return CompletionParams::create(std::move(textDocument), std::move(position), std::move(context));
}
const boost::string_view DidChangeTextDocumentParams::typeName("com.illumon.iris.web.shared.ide.lsp.DidChangeTextDocumentParams");
std::shared_ptr<DidChangeTextDocumentParams> DidChangeTextDocumentParams::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::VersionedTextDocumentIdentifier> textDocument, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentContentChangeEvent>>> contentChanges) {
  return std::make_shared<DidChangeTextDocumentParams>(Private(), std::move(textDocument), std::move(contentChanges));
}
DidChangeTextDocumentParams::DidChangeTextDocumentParams(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::VersionedTextDocumentIdentifier> textDocument, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentContentChangeEvent>>> contentChanges)
  : textDocument_(std::move(textDocument)), contentChanges_(std::move(contentChanges))
  {
}
DidChangeTextDocumentParams::~DidChangeTextDocumentParams() = default;
void DidChangeTextDocumentParams::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&textDocument_);
  sa.write(&contentChanges_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> DidChangeTextDocumentParams::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::VersionedTextDocumentIdentifier> textDocument;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentContentChangeEvent>>> contentChanges;
  da.read(&textDocument);
  da.read(&contentChanges);
  return DidChangeTextDocumentParams::create(std::move(textDocument), std::move(contentChanges));
}
const boost::string_view DidCloseTextDocumentParams::typeName("com.illumon.iris.web.shared.ide.lsp.DidCloseTextDocumentParams");
std::shared_ptr<DidCloseTextDocumentParams> DidCloseTextDocumentParams::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentIdentifier> textDocument) {
  return std::make_shared<DidCloseTextDocumentParams>(Private(), std::move(textDocument));
}
DidCloseTextDocumentParams::DidCloseTextDocumentParams(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentIdentifier> textDocument)
  : textDocument_(std::move(textDocument))
  {
}
DidCloseTextDocumentParams::~DidCloseTextDocumentParams() = default;
void DidCloseTextDocumentParams::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&textDocument_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> DidCloseTextDocumentParams::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentIdentifier> textDocument;
  da.read(&textDocument);
  return DidCloseTextDocumentParams::create(std::move(textDocument));
}
const boost::string_view DidOpenTextDocumentParams::typeName("com.illumon.iris.web.shared.ide.lsp.DidOpenTextDocumentParams");
std::shared_ptr<DidOpenTextDocumentParams> DidOpenTextDocumentParams::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentItem> textDocument) {
  return std::make_shared<DidOpenTextDocumentParams>(Private(), std::move(textDocument));
}
DidOpenTextDocumentParams::DidOpenTextDocumentParams(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentItem> textDocument)
  : textDocument_(std::move(textDocument))
  {
}
DidOpenTextDocumentParams::~DidOpenTextDocumentParams() = default;
void DidOpenTextDocumentParams::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&textDocument_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> DidOpenTextDocumentParams::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentItem> textDocument;
  da.read(&textDocument);
  return DidOpenTextDocumentParams::create(std::move(textDocument));
}
const boost::string_view DocumentRange::typeName("com.illumon.iris.web.shared.ide.lsp.DocumentRange");
std::shared_ptr<DocumentRange> DocumentRange::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::Position> start, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::Position> end) {
  return std::make_shared<DocumentRange>(Private(), std::move(start), std::move(end));
}
DocumentRange::DocumentRange(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::Position> start, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::Position> end)
  : start_(std::move(start)), end_(std::move(end))
  {
}
DocumentRange::~DocumentRange() = default;
void DocumentRange::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&start_);
  sa.write(&end_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> DocumentRange::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::Position> start;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::Position> end;
  da.read(&start);
  da.read(&end);
  return DocumentRange::create(std::move(start), std::move(end));
}
const boost::string_view Position::typeName("com.illumon.iris.web.shared.ide.lsp.Position");
std::shared_ptr<Position> Position::create(int32_t line, int32_t character) {
  return std::make_shared<Position>(Private(), line, character);
}
Position::Position(Private, int32_t line, int32_t character)
  : line_(line), character_(character)
  {
}
Position::~Position() = default;
void Position::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&line_);
  sa.write(&character_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> Position::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  int32_t line;
  int32_t character;
  da.read(&line);
  da.read(&character);
  return Position::create(line, character);
}
const boost::string_view TextDocumentContentChangeEvent::typeName("com.illumon.iris.web.shared.ide.lsp.TextDocumentContentChangeEvent");
std::shared_ptr<TextDocumentContentChangeEvent> TextDocumentContentChangeEvent::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DocumentRange> range, int32_t rangeLength, std::shared_ptr<std::string> text) {
  return std::make_shared<TextDocumentContentChangeEvent>(Private(), std::move(range), rangeLength, std::move(text));
}
TextDocumentContentChangeEvent::TextDocumentContentChangeEvent(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DocumentRange> range, int32_t rangeLength, std::shared_ptr<std::string> text)
  : range_(std::move(range)), rangeLength_(rangeLength), text_(std::move(text))
  {
}
TextDocumentContentChangeEvent::~TextDocumentContentChangeEvent() = default;
void TextDocumentContentChangeEvent::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&range_);
  sa.write(&rangeLength_);
  sa.write(&text_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> TextDocumentContentChangeEvent::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DocumentRange> range;
  int32_t rangeLength;
  std::shared_ptr<std::string> text;
  da.read(&range);
  da.read(&rangeLength);
  da.read(&text);
  return TextDocumentContentChangeEvent::create(std::move(range), rangeLength, std::move(text));
}
const boost::string_view TextDocumentIdentifier::typeName("com.illumon.iris.web.shared.ide.lsp.TextDocumentIdentifier");
std::shared_ptr<TextDocumentIdentifier> TextDocumentIdentifier::create(std::shared_ptr<std::string> uri) {
  return std::make_shared<TextDocumentIdentifier>(Private(), std::move(uri));
}
TextDocumentIdentifier::TextDocumentIdentifier(Private, std::shared_ptr<std::string> uri)
  : uri_(std::move(uri))
  {
}
TextDocumentIdentifier::~TextDocumentIdentifier() = default;
void TextDocumentIdentifier::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&uri_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> TextDocumentIdentifier::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::string> uri;
  da.read(&uri);
  return TextDocumentIdentifier::create(std::move(uri));
}
const boost::string_view TextDocumentItem::typeName("com.illumon.iris.web.shared.ide.lsp.TextDocumentItem");
std::shared_ptr<TextDocumentItem> TextDocumentItem::create(std::shared_ptr<std::string> uri, std::shared_ptr<std::string> languageId, std::shared_ptr<std::string> text, int32_t version) {
  return std::make_shared<TextDocumentItem>(Private(), std::move(uri), std::move(languageId), std::move(text), version);
}
TextDocumentItem::TextDocumentItem(Private, std::shared_ptr<std::string> uri, std::shared_ptr<std::string> languageId, std::shared_ptr<std::string> text, int32_t version)
  : uri_(std::move(uri)), languageId_(std::move(languageId)), text_(std::move(text)), version_(version)
  {
}
TextDocumentItem::~TextDocumentItem() = default;
void TextDocumentItem::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&uri_);
  sa.write(&languageId_);
  sa.write(&text_);
  sa.write(&version_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> TextDocumentItem::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::string> uri;
  std::shared_ptr<std::string> languageId;
  std::shared_ptr<std::string> text;
  int32_t version;
  da.read(&uri);
  da.read(&languageId);
  da.read(&text);
  da.read(&version);
  return TextDocumentItem::create(std::move(uri), std::move(languageId), std::move(text), version);
}
const boost::string_view TextEdit::typeName("com.illumon.iris.web.shared.ide.lsp.TextEdit");
std::shared_ptr<TextEdit> TextEdit::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DocumentRange> range, std::shared_ptr<std::string> text) {
  return std::make_shared<TextEdit>(Private(), std::move(range), std::move(text));
}
TextEdit::TextEdit(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DocumentRange> range, std::shared_ptr<std::string> text)
  : range_(std::move(range)), text_(std::move(text))
  {
}
TextEdit::~TextEdit() = default;
void TextEdit::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&range_);
  sa.write(&text_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> TextEdit::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::DocumentRange> range;
  std::shared_ptr<std::string> text;
  da.read(&range);
  da.read(&text);
  return TextEdit::create(std::move(range), std::move(text));
}
const boost::string_view VersionedTextDocumentIdentifier::typeName("com.illumon.iris.web.shared.ide.lsp.VersionedTextDocumentIdentifier");
std::shared_ptr<VersionedTextDocumentIdentifier> VersionedTextDocumentIdentifier::create(std::shared_ptr<std::string> uri, int32_t version) {
  return std::make_shared<VersionedTextDocumentIdentifier>(Private(), std::move(uri), version);
}
VersionedTextDocumentIdentifier::VersionedTextDocumentIdentifier(Private, std::shared_ptr<std::string> uri, int32_t version)
  : deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentIdentifier(Private(), std::move(uri)), version_(version)
  {
}
VersionedTextDocumentIdentifier::~VersionedTextDocumentIdentifier() = default;
void VersionedTextDocumentIdentifier::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&version_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> VersionedTextDocumentIdentifier::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::string> uri;
  int32_t version;
  da.read(&uri);
  da.read(&version);
  return VersionedTextDocumentIdentifier::create(std::move(uri), version);
}
}  // namespace lsp
}  // namespace ide
namespace metrics {
const boost::string_view MetricsLog::typeName("com.illumon.iris.web.shared.metrics.MetricsLog");
std::shared_ptr<MetricsLog> MetricsLog::create(std::shared_ptr<std::string> type, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::ServerReplyHandle> clientId, int64_t nano) {
  return std::make_shared<MetricsLog>(Private(), std::move(type), std::move(clientId), nano);
}
MetricsLog::MetricsLog(Private, std::shared_ptr<std::string> type, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::ServerReplyHandle> clientId, int64_t nano)
  : type_(std::move(type)), clientId_(std::move(clientId)), nano_(nano)
  {
}
MetricsLog::~MetricsLog() = default;
void MetricsLog::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&type_);
  sa.write(&clientId_);
  sa.write(&nano_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> MetricsLog::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<std::string> type;
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::ServerReplyHandle> clientId;
  int64_t nano;
  da.read(&type);
  da.read(&clientId);
  da.read(&nano);
  return MetricsLog::create(std::move(type), std::move(clientId), nano);
}
}  // namespace metrics
namespace requests {
const boost::string_view AddToInputTableRequest::typeName("com.illumon.iris.web.shared.requests.AddToInputTableRequest");
std::shared_ptr<AddToInputTableRequest> AddToInputTableRequest::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableValues> rowsToAdd, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> tablesToAdd) {
  return std::make_shared<AddToInputTableRequest>(Private(), std::move(rowsToAdd), std::move(tablesToAdd));
}
AddToInputTableRequest::AddToInputTableRequest(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableValues> rowsToAdd, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> tablesToAdd)
  : rowsToAdd_(std::move(rowsToAdd)), tablesToAdd_(std::move(tablesToAdd))
  {
}
AddToInputTableRequest::~AddToInputTableRequest() = default;
void AddToInputTableRequest::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&rowsToAdd_);
  sa.write(&tablesToAdd_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> AddToInputTableRequest::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableValues> rowsToAdd;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> tablesToAdd;
  da.read(&rowsToAdd);
  da.read(&tablesToAdd);
  return AddToInputTableRequest::create(std::move(rowsToAdd), std::move(tablesToAdd));
}
const boost::string_view AddToInputTableResponse::typeName("com.illumon.iris.web.shared.requests.AddToInputTableResponse");
std::shared_ptr<AddToInputTableResponse> AddToInputTableResponse::create(std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableValues> failedRows, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> failedTables, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> failureMessages) {
  return std::make_shared<AddToInputTableResponse>(Private(), std::move(failedRows), std::move(failedTables), std::move(failureMessages));
}
AddToInputTableResponse::AddToInputTableResponse(Private, std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableValues> failedRows, std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> failedTables, std::shared_ptr<std::vector<std::shared_ptr<std::string>>> failureMessages)
  : failedRows_(std::move(failedRows)), failedTables_(std::move(failedTables)), failureMessages_(std::move(failureMessages))
  {
}
AddToInputTableResponse::~AddToInputTableResponse() = default;
void AddToInputTableResponse::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
  sa.write(&failedRows_);
  sa.write(&failedTables_);
  sa.write(&failureMessages_);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> AddToInputTableResponse::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableValues> failedRows;
  std::shared_ptr<std::vector<std::shared_ptr<deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::TableHandle>>> failedTables;
  std::shared_ptr<std::vector<std::shared_ptr<std::string>>> failureMessages;
  da.read(&failedRows);
  da.read(&failedTables);
  da.read(&failureMessages);
  return AddToInputTableResponse::create(std::move(failedRows), std::move(failedTables), std::move(failureMessages));
}
}  // namespace requests
}  // namespace shared
}  // namespace web
}  // namespace iris
}  // namespace illumon
}  // namespace com
namespace java {
namespace lang {
const boost::string_view Boolean::typeName("java.lang.Boolean");
Boolean::Boolean(Private, deephaven::openAPI::lowlevel::remoting::custom::java::lang::BooleanCustom custom)
  : custom_(std::move(custom))
  {
}
Boolean::~Boolean() = default;
void Boolean::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  custom_.serialize(serializer);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> Boolean::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  auto custom = deephaven::openAPI::lowlevel::remoting::custom::java::lang::BooleanCustom::deserialize(deserializer);
  return Boolean::create(std::move(custom));
}
const boost::string_view Byte::typeName("java.lang.Byte");
Byte::Byte(Private, deephaven::openAPI::lowlevel::remoting::custom::java::lang::ByteCustom custom)
  : custom_(std::move(custom))
  {
}
Byte::~Byte() = default;
void Byte::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  custom_.serialize(serializer);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> Byte::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  auto custom = deephaven::openAPI::lowlevel::remoting::custom::java::lang::ByteCustom::deserialize(deserializer);
  return Byte::create(std::move(custom));
}
const boost::string_view Character::typeName("java.lang.Character");
Character::Character(Private, deephaven::openAPI::lowlevel::remoting::custom::java::lang::CharacterCustom custom)
  : custom_(std::move(custom))
  {
}
Character::~Character() = default;
void Character::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  custom_.serialize(serializer);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> Character::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  auto custom = deephaven::openAPI::lowlevel::remoting::custom::java::lang::CharacterCustom::deserialize(deserializer);
  return Character::create(std::move(custom));
}
const boost::string_view Double::typeName("java.lang.Double");
Double::Double(Private, deephaven::openAPI::lowlevel::remoting::custom::java::lang::DoubleCustom custom)
  : custom_(std::move(custom))
  {
}
Double::~Double() = default;
void Double::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  custom_.serialize(serializer);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> Double::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  auto custom = deephaven::openAPI::lowlevel::remoting::custom::java::lang::DoubleCustom::deserialize(deserializer);
  return Double::create(std::move(custom));
}
const boost::string_view Float::typeName("java.lang.Float");
Float::Float(Private, deephaven::openAPI::lowlevel::remoting::custom::java::lang::FloatCustom custom)
  : custom_(std::move(custom))
  {
}
Float::~Float() = default;
void Float::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  custom_.serialize(serializer);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> Float::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  auto custom = deephaven::openAPI::lowlevel::remoting::custom::java::lang::FloatCustom::deserialize(deserializer);
  return Float::create(std::move(custom));
}
const boost::string_view Integer::typeName("java.lang.Integer");
Integer::Integer(Private, deephaven::openAPI::lowlevel::remoting::custom::java::lang::IntegerCustom custom)
  : custom_(std::move(custom))
  {
}
Integer::~Integer() = default;
void Integer::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  custom_.serialize(serializer);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> Integer::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  auto custom = deephaven::openAPI::lowlevel::remoting::custom::java::lang::IntegerCustom::deserialize(deserializer);
  return Integer::create(std::move(custom));
}
const boost::string_view Long::typeName("java.lang.Long");
Long::Long(Private, deephaven::openAPI::lowlevel::remoting::custom::java::lang::LongCustom custom)
  : custom_(std::move(custom))
  {
}
Long::~Long() = default;
void Long::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  custom_.serialize(serializer);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> Long::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  auto custom = deephaven::openAPI::lowlevel::remoting::custom::java::lang::LongCustom::deserialize(deserializer);
  return Long::create(std::move(custom));
}
const boost::string_view Number::typeName("java.lang.Number");
std::shared_ptr<Number> Number::create() {
  return std::make_shared<Number>(Private());
}
Number::Number(Private)
  
  {
}
Number::~Number() = default;
void Number::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  deephaven::openAPI::lowlevel::remoting::util::SerializerAdapter sa(serializer);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> Number::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  deephaven::openAPI::lowlevel::remoting::util::DeserializerAdapter da(deserializer);
  return Number::create();
}
const boost::string_view Short::typeName("java.lang.Short");
Short::Short(Private, deephaven::openAPI::lowlevel::remoting::custom::java::lang::ShortCustom custom)
  : custom_(std::move(custom))
  {
}
Short::~Short() = default;
void Short::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  custom_.serialize(serializer);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> Short::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  auto custom = deephaven::openAPI::lowlevel::remoting::custom::java::lang::ShortCustom::deserialize(deserializer);
  return Short::create(std::move(custom));
}
const boost::string_view String::typeName("java.lang.String");
String::String(Private, deephaven::openAPI::lowlevel::remoting::custom::java::lang::StringCustom custom)
  : custom_(std::move(custom))
  {
}
String::~String() = default;
void String::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  custom_.serialize(serializer);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> String::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  auto custom = deephaven::openAPI::lowlevel::remoting::custom::java::lang::StringCustom::deserialize(deserializer);
  return String::create(std::move(custom));
}
const boost::string_view Void::typeName("java.lang.Void");
Void::Void(Private, deephaven::openAPI::lowlevel::remoting::custom::java::lang::VoidCustom custom)
  : custom_(std::move(custom))
  {
}
Void::~Void() = default;
void Void::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  custom_.serialize(serializer);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> Void::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  auto custom = deephaven::openAPI::lowlevel::remoting::custom::java::lang::VoidCustom::deserialize(deserializer);
  return Void::create(std::move(custom));
}
}  // namespace lang
namespace math {
const boost::string_view BigDecimal::typeName("java.math.BigDecimal");
BigDecimal::BigDecimal(Private, deephaven::openAPI::lowlevel::remoting::custom::java::math::BigDecimalCustom custom)
  : custom_(std::move(custom))
  {
}
BigDecimal::~BigDecimal() = default;
void BigDecimal::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  custom_.serialize(serializer);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> BigDecimal::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  auto custom = deephaven::openAPI::lowlevel::remoting::custom::java::math::BigDecimalCustom::deserialize(deserializer);
  return BigDecimal::create(std::move(custom));
}
const boost::string_view BigInteger::typeName("java.math.BigInteger");
BigInteger::BigInteger(Private, deephaven::openAPI::lowlevel::remoting::custom::java::math::BigIntegerCustom custom)
  : custom_(std::move(custom))
  {
}
BigInteger::~BigInteger() = default;
void BigInteger::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  custom_.serialize(serializer);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> BigInteger::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  auto custom = deephaven::openAPI::lowlevel::remoting::custom::java::math::BigIntegerCustom::deserialize(deserializer);
  return BigInteger::create(std::move(custom));
}
}  // namespace math
namespace util {
const boost::string_view BitSet::typeName("java.util.BitSet");
BitSet::BitSet(Private, deephaven::openAPI::lowlevel::remoting::custom::java::util::BitSetCustom custom)
  : custom_(std::move(custom))
  {
}
BitSet::~BitSet() = default;
void BitSet::serializeObject(deephaven::openAPI::core::remoting::util::Serializer *serializer) const {
  serializer->writeStringView(typeName);
  custom_.serialize(serializer);
}
std::shared_ptr<deephaven::openAPI::core::remoting::Object> BitSet::deserializeObjectHelper(deephaven::openAPI::core::remoting::util::Deserializer *deserializer) {
  auto custom = deephaven::openAPI::lowlevel::remoting::custom::java::util::BitSetCustom::deserialize(deserializer);
  return BitSet::create(std::move(custom));
}
}  // namespace util
}  // namespace java
std::array<const char *, 20> dynamicDeserializerNames = {
  "com.illumon.iris.web.shared.cmd.RequestId",
  "com.illumon.iris.web.shared.cmd.ServerReplyHandle",
  "com.illumon.iris.web.shared.data.columns.BigDecimalArrayColumnData",
  "com.illumon.iris.web.shared.data.columns.BigIntegerArrayColumnData",
  "com.illumon.iris.web.shared.data.columns.ByteArrayColumnData",
  "com.illumon.iris.web.shared.data.columns.CharArrayColumnData",
  "com.illumon.iris.web.shared.data.columns.ColumnData",
  "com.illumon.iris.web.shared.data.columns.DoubleArrayColumnData",
  "com.illumon.iris.web.shared.data.columns.FloatArrayColumnData",
  "com.illumon.iris.web.shared.data.columns.IntArrayColumnData",
  "com.illumon.iris.web.shared.data.columns.LocalDateArrayColumnData",
  "com.illumon.iris.web.shared.data.columns.LocalTimeArrayColumnData",
  "com.illumon.iris.web.shared.data.columns.LongArrayColumnData",
  "com.illumon.iris.web.shared.data.columns.ShortArrayColumnData",
  "com.illumon.iris.web.shared.data.columns.StringArrayArrayColumnData",
  "com.illumon.iris.web.shared.data.columns.StringArrayColumnData",
  "com.illumon.iris.web.shared.ide.lsp.CompletionParams",
  "com.illumon.iris.web.shared.ide.lsp.TextDocumentIdentifier",
  "com.illumon.iris.web.shared.ide.lsp.TextDocumentPositionParams",
  "com.illumon.iris.web.shared.ide.lsp.VersionedTextDocumentIdentifier",
};
std::array<deephaven::openAPI::core::remoting::util::Deserializer::objectFactory_t, 20> dynamicDeserializerMethods = {
  &deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::RequestId::deserializeObjectHelper,
  &deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::cmd::ServerReplyHandle::deserializeObjectHelper,
  &deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::BigDecimalArrayColumnData::deserializeObjectHelper,
  &deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::BigIntegerArrayColumnData::deserializeObjectHelper,
  &deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ByteArrayColumnData::deserializeObjectHelper,
  &deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::CharArrayColumnData::deserializeObjectHelper,
  &deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ColumnData::deserializeObjectHelper,
  &deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::DoubleArrayColumnData::deserializeObjectHelper,
  &deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::FloatArrayColumnData::deserializeObjectHelper,
  &deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::IntArrayColumnData::deserializeObjectHelper,
  &deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::LocalDateArrayColumnData::deserializeObjectHelper,
  &deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::LocalTimeArrayColumnData::deserializeObjectHelper,
  &deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::LongArrayColumnData::deserializeObjectHelper,
  &deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::ShortArrayColumnData::deserializeObjectHelper,
  &deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::StringArrayArrayColumnData::deserializeObjectHelper,
  &deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::data::columns::StringArrayColumnData::deserializeObjectHelper,
  &deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::CompletionParams::deserializeObjectHelper,
  &deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentIdentifier::deserializeObjectHelper,
  &deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::TextDocumentPositionParams::deserializeObjectHelper,
  &deephaven::openAPI::lowlevel::remoting::generated::com::illumon::iris::web::shared::ide::lsp::VersionedTextDocumentIdentifier::deserializeObjectHelper,
};
}  // namespace generated
}  // namespace remoting
}  // namespace lowlevel
}  // namespace openAPI
}  // namespace deephaven
