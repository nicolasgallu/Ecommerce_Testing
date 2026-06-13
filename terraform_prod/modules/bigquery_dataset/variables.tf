variable "dataset_id" {
  type        = string
  description = "BigQuery dataset ID."
}

variable "location" {
  type        = string
  description = "BigQuery dataset location, for example US, EU, or us-central1."
}

variable "friendly_name" {
  type        = string
  description = "Human-readable name for the BigQuery dataset."
  default     = null
}

variable "description" {
  type        = string
  description = "Description of the BigQuery dataset."
  default     = null
}

variable "environment" {
  type        = string
  description = "Environment name, for example dev, staging, or prod."
}

variable "delete_contents_on_destroy" {
  type        = bool
  description = "Whether Terraform should delete all dataset contents when destroying the dataset."
  default     = false
}