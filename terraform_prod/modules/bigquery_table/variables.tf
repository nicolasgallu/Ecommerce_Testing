variable "dataset_id" {
  type = string
}

variable "table_id" {
  type = string
}

variable "description" {
  type    = string
  default = null
}

variable "deletion_protection" {
  type    = bool
  default = true
}

variable "schema" {
  type = list(object({
    name = string
    type = string
    mode = optional(string)
  }))
}