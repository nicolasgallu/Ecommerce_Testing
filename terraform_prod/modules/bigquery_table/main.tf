resource "google_bigquery_table" "this" {
  dataset_id = var.dataset_id
  table_id   = var.table_id

  description         = var.description
  deletion_protection = var.deletion_protection

  schema = jsonencode(var.schema)
}