resource "google_bigquery_dataset" "this" {
  dataset_id = var.dataset_id
  location   = var.location

  friendly_name = var.friendly_name
  description   = var.description

  delete_contents_on_destroy = var.delete_contents_on_destroy

  labels = {
    environment = var.environment
    managed_by  = "terraform"
  }
}