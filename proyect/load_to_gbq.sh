bq load \
  --source_format=CSV \
  --replace \
  --skip_leading_rows=1 \
  raw_data.staging_orderss \
  "gs://new-buck-test/data_*.csv.gz"