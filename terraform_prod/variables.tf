variable "project_id" {
  type        = string
  description = "GCP project ID where Terraform will create resources."
}

variable "region" {
  type        = string
  description = "Default GCP region for regional resources."
  default     = "us-central1"
}

variable "bucket_name" {
  type        = string
  description = "Name of the GCS bucket to create."
}

variable "bucket_location" {
  type        = string
  description = "Location of the GCS bucket."
  default     = "US"
}