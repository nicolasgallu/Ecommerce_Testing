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

variable "gbq_raw_dataset_id" {
  type        = string
  description = "BigQuery dataset ID."
}

variable "gbq_raw_location" {
  type        = string
  description = "BigQuery dataset location, for example US, EU, or us-central1."
}

variable "gbq_raw_environment" {
  type        = string
  description = "Environment name, for example dev, staging, or prod."
}

variable "gbq_staging_orders_table" {
  type = string
}