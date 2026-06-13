variable "name" {
  type        = string
  description = "Name of the GCS bucket. Must be globally unique."
}

variable "location" {
  type        = string
  description = "Location of the GCS bucket, for example US, EU, or us-central1."
}