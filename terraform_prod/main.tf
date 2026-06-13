module "raw_bucket" {
  source      = "./modules/gcs_bucket"
  name        = var.bucket_name
  location    = var.bucket_location
}

module "raw_dataset" {
  source     = "./modules/bigquery_dataset"
  dataset_id = var.gbq_raw_dataset_id
  location   = var.gbq_raw_location
  environment   = var.gbq_raw_environment
}

module "raw_table" {
  source     = "./modules/bigquery_table"
  dataset_id = var.gbq_raw_dataset_id
  table_id   = var.gbq_staging_orders_table
  deletion_protection = false
  schema = [
    {
      name = "transaction_id"
      type = "STRING"
      mode = "NULLABLE"
    },
    {
      name = "amount"
      type = "STRING"
      mode = "NULLABLE"
    },
    {
      name = "user_id"
      type = "STRING"
      mode = "NULLABLE"
    },
    {
      name = "timestamp"
      type = "STRING"
      mode = "NULLABLE"
    }
  ]
}