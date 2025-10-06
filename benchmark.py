import glob
import os
import time
import pandas as pd
import duckdb
import pyspark
from pyspark.sql import SparkSession
from pyspark.sql import functions as F

def duckdb_benchmark(parquet_files):
    cn = duckdb.connect()
    results = []
    for f_path in parquet_files:
        start = time.time()
        cn.sql(f"select rand_dt, count(distinct rand_str) from read_parquet('{f_path}') group by all order by 2 desc").fetchall()
        end = time.time()
        elapsed_ms = (end - start) * 1000
        row_count = cn.sql(f"select count(*) from read_parquet('{f_path}')").fetchone()[0]
        results.append({"Engine": "DuckDB", "File": os.path.basename(f_path), "Rows": f"{row_count:,}", "Run Time (ms)": f"{elapsed_ms:.2f}"})
    return results

spark=SparkSession.builder.appName("benchmark").getOrCreate()
def spark_benchmark(parquet_files, spark):
    results = []
    for f_path in parquet_files:
        start = time.time()
        df = spark.read.parquet(f_path)
        grouped = df.groupBy("rand_dt").agg(F.count_distinct("rand_str").alias("distinct_rand_str_count")).orderBy("distinct_rand_str_count", ascending=False)
        grouped.collect()
        end = time.time()
        elapsed_ms = (end - start) * 1000
        row_count = df.count()
        results.append({"Engine": "Spark", "File": os.path.basename(f_path), "Rows": f"{row_count:,}", "Run Time (ms)": f"{elapsed_ms:.2f}"})
    return results

data_dir = os.path.expanduser("./data/duckdb_generated")
parquet_files = sorted(glob.glob(os.path.join(data_dir, "ds_*.parquet")))

duckdb_results = duckdb_benchmark(parquet_files)
print(duckdb_results)
spark_results = spark_benchmark(parquet_files, spark)
print(spark_results)
