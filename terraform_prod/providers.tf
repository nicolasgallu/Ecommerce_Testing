//In PROVIDERS we declare how we are gonna connect to the providers.

provider "google" {
  project = var.project_id
  region  = var.region
}