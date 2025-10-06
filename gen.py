import os
import duckdb
import time

# Generate dummy data using DuckDB SQL
def gen_dataset(rows):

    lower_bound = "2020-01-01"
    upper_bound = "2025-01-01"  

    duckdb.execute(f"""
        COPY (
        select  
              t.row_id
            , cast(uuid() as varchar(30)) as txn_key
            , date '{lower_bound}' 
            + (random() * (date_diff('day', date '{lower_bound}', date '{upper_bound}')))::int as rand_dt
            , round(random() * 100, 2) as rand_val
            , substr(
                  'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789', 
                  1, 
                  1 + (random() * 25)::int
              ) as rand_str
        from generate_series(1,{rows}) t(row_id)
        ) TO './ds_{rows}_rows.parquet' (FORMAT 'parquet')
    """)

n_rows = [500, 5_000, 50_000, 500_000, 5_000_000, 50_000_000, 500_000_000]
for n_row in n_rows:
    gen_dataset(n_row)
