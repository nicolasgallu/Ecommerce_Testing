module "raw_bucket" {
  source      = "./modules/gcs_bucket"
  name        = var.bucket_name
  location    = var.bucket_location
}