#
# Copyright (c) 2016-2025 Deephaven Data Labs and Patent Pending
#
from typing import Union, List, Optional

from pydeephaven._batch_assembler import BatchOpAssembler
from pydeephaven._table_ops import TableOp
from pydeephaven.dherror import DHError
from deephaven_core.proto import table_pb2_grpc, table_pb2
from pydeephaven.table import Table, InputTable
from pydeephaven.ticket import ExportTicket, Ticket, _ticket_from_proto


class TableService:
    def __init__(self, session):
        self.session = session
        self._grpc_table_stub = table_pb2_grpc.TableServiceStub(session.grpc_channel)

    def batch(self, ops: List[TableOp]) -> Table:
        """Assembles and executes chain table operations in a batch."""
        batch_ops = BatchOpAssembler(self.session, table_ops=ops).build_batch()

        try:
            response = self.session.wrap_bidi_rpc(
                self._grpc_table_stub.Batch,
                table_pb2.BatchTableRequest(ops=batch_ops))

            exported_tables = []
            for exported in response:
                if not exported.success:
                    raise DHError(exported.error_info)
                if exported.result_id.WhichOneof("ref") == "ticket":
                    exported_tables.append(Table(self.session, ticket=ExportTicket(ticket_bytes=exported.result_id.ticket.ticket),
                                                 schema_header=exported.schema_header,
                                                 size=exported.size,
                                                 is_static=exported.is_static))
            return exported_tables[-1]
        except Exception as e:
            raise DHError("failed to finish the table batch operation.") from e

    def grpc_table_op(self, table: Optional[Table], op: TableOp, table_class: type = Table) -> Union[Table, InputTable]:
        """Makes a single gRPC Table operation call and returns a new Table."""
        try:
            export_ticket = self.session.make_export_ticket()
            if table:
                table_reference = table_pb2.TableReference(ticket=table.pb_ticket)
            else:
                table_reference = None
            stub_func = op.__class__.get_stub_func(self._grpc_table_stub)
            response = self.session.wrap_rpc(
                stub_func,
                op.make_grpc_request(
                    result_id=export_ticket.pb_ticket,
                    source_id=table_reference))
            if response.success:
                return table_class(self.session, ticket=ExportTicket(response.result_id.ticket.ticket),
                                   schema_header=response.schema_header,
                                   size=response.size,
                                   is_static=response.is_static)
            else:
                raise DHError(f"Server error received for {op.__class__.__name__}: {response.error_info}")
        except Exception as e:
            raise DHError(f"failed to finish {op.__class__.__name__} operation") from e

    def fetch_etcr(self, ticket) -> Table:
        """Given a ticket, constructs a table around it, by fetching metadata from the server."""
        response = self.session.wrap_rpc(
            self._grpc_table_stub.GetExportedTableCreationResponse,
            ticket)

        ticket = _ticket_from_proto(response.result_id.ticket)
        if response.success:
            return Table(self.session, ticket=ticket,
                         schema_header=response.schema_header,
                         size=response.size,
                         is_static=response.is_static)
        raise DHError(
            f"Server error received for ExportedTableCreationResponse: {response.error_info}")
