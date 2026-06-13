bq load \
  --source_format=CSV \
  --replace \
  --skip_leading_rows=1 \
  raw_data.staging_orders \
  "gs://new-buck-test/data_*.csv.gz"