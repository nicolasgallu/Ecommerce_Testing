What is Terraform?
Terraform is basically a Architecture Orchestator (IaC), allowing us to work with 
different technologies and their resources.

Terraform Architecture
The Arch. of Terraform is based on a client - server protocol.
Where us as clients use the CLI and write commands that the
Terraform server reads, for this we "talk" using the HCL language
(this is a configuration language from the same comapany that 
developed Terraform, "HashiGroup").

There are basic components inside the Architecture:
  - Terraform Core: Is the Engine, responsible to the config.file read,
    manage the state file, and execute plans to apply changes.
  - Providers: Are plug-ins that allow us to work with the available
    technologies and resources inside Terraform ecosystem.
  - Configuration Files: Are the user writted files (HCL) that allow
    us to configure the desire architecture model.
  - State Managment: Track the changes, and is the base to compare
    the current model to the desire one, letin Terraform to decide
    which changes needs to be done.

Terraform LifeCycle
Init -> Plan -> Apply -> Destroy

[PROVIDERS]
  - Check available providers and resourcers: https://registry.terraform.io/browse/providers
  - If there is not a providor that u need, u can develop it by yourself 
    using the Terraform Plugin SDK
  - 


[PLAN]
Terraform is gonna run an analysis in our behalf, 
reviewing what needs to be done in order to create 
the desire enviroment. This is where Terraform cames with
a "Plan" that is gonna execute, and we are still capable to
reviewing this plan and determining if the planned is what we
intended. The plans are saved since they store the differences
from the actual source code and the enviroment.

Example:
  - On Day1 since the enviroment is yet not created, Terraform will
    generate everything from zero.
  - On Day2, if we had made changes on our source code, then we
    Terraform runs a complex process detailed on the LifeCycle.


[TERRAFORM LIFECYCLE]

  - INIT: The command <terraform init> would initialize the 
    Terraform workspace which loads and configures all 
    referenced providers and modules.
  
  - PLAN: The command <terraform plan> will generate the plan
    to be executed, is a little bit complex, but basically
    Terraform will first check if the desire resources had been 
    already provided (checking against the file statte), 
    if not is gonna create it.
    Now if it already exists, and this is noticed when checking the
    state file, and after that it also checks the provider resourcer.
    This is important to check against the reality and have a good 
    reconciliation process.
    With this process in mind, Terraform is gonna be able to Plan
    the creation, update or delete of the resource.

    --> RESOURCE ACTIONS: A Plan is determinated depending on the
        resource state in enviroment, this actions can be
        create, update or delete.

        - Graph: Is very important to understand that Terraform
          builds an internal graph of the resources and their
          dependencies, because  when deleting Terraform
          would run a Cascade Effect, leading to unexpected events
          if not treat it carefoully.
          This is were is also important to have a minimal knoweledge
          over Stateless and Staeful resources.
          SUMMARY OF STATELESS AND STATEFUL: 
            -Stateless: Means that persistent state leaves outside
              the servers.
            -Stateful: Means that persisten state leaves inside
              the servers, we usually want to avoid deleting
              sateful services cause this ones has potentally 
              critical data.


        - Create: Caused by different scenarios, as for example
          when resource doesnt exists in file state then
          Terraform asumes it needs to be created, what can
          indeed leads to issues where the result does exists
          in providors enviroment (due to external manual input).
          This would actaully tell us that it was an error while 
          applying but not in the planning stage.

          Also for certaing resources, providers would actaully
          need to recreate the resources once updated, lets
          suppose u had vm_01 with 8gb and 2cpu, and now you
          updated to 16gb and 4cpu, well depending on the providor
          Terraform would need to delete the resource and 
          re-created with the new update. (thats why is important
          to read docs. over the resources that you use to not fall
          in data losses.)

        - Update: This can happen both when source code has changed,
          or when the resource has change outside Terraform. 
          The last case happens when someone changed the resource outside 
          Terraform, and the philosofy of Terraform (IaC) is that
          the source of truth would always be the Code.
          So if your vm in file state is 8gb and 2cpu, and in
          the real infra is now 16gb and 2cpu, then Terraform (if you 
          run the full cycle until apply) would rever the VM 
          to the current file state (probably leading to Data Loss).

        - Destruction: This can happen when from source code we 
          directly remove a certain resource, or if we update a 
          resource that needs to be re-created by providor.



  -APPLY: The command <terraform apply> is the responsible to
    execute the previous plan.


FILE STATE:
  The file state is a json file where Terraform keeps track over the pushed to production,
  basically the last file state should be our mirror to the real world.
  One important aspect, is that Terraform allow users to work with the tool as intended,
  this means that we want to use Terraform for some resources, and for others we want
  to create them directly on the services, we can, only when we are not dealing with
  the same resource reference (ej creating VM01 in Terraform and modifying it in the
  cloud service.) 


MODULES:
  Terraform allow us to create modules easily using folders, this can be done
  after executing the command "terraform init" that would create the root folder.

  A simple structure would be:
  /terraform
    /modules
      /rando
    /root
      main.tf
      outputs.tf
      variables.tf
      versions.tf

  - In versions we would declare the version of terraform along with the providors
    versions that we are gonna make use of.
  - Variables & Outputs can also exists inside other modules folders, but is always
    a good practice to try to mantain simplicity and not make other coworkers look
    over the entire repo to find certain declarations.
  - At main, this is where the magic happens. (needs more elaboration)

  Notice that all this *.tf files can be created inside modules aslong as the 
  project complexity really needs it.
  This "Design Choice" comes along with the question of "all of this can be writted
  inside a single module, do i really need to separate it?"

  Different Design Patterns:

  - Folder by enviroment
  - .. others



[COMMANDS]
 -INIT: This would instance the direct folder (as like git init).
  is gonna accoumlish somethings:
  - providers installation (read trough the providers declared to work with)
  - moduels installation (read trough the modules that we are requesting or even if those are local modules)
  - backend initiliazitation (terraform init and connects to the folder where state files will be created)

 -VALIDATE: This command allow us to run a "compiler" process to check dependencies and syntax.

 -WORKSPACE: Allow us to fork different instances over the same file state.

 -PLAN: Runs the plan of Terraform, first needing to set up the workspace and variables needed.
  You can do this in three ways: Individual Command Line Argument, Variable File, and Environment Variables.

 -APPLY: Sends to production the plan.

 -DESTROY: Destroy the enviroment.


 




  

HCL:
A block's definition has three parts: the Block Type, the Resource Type, 
and the Reference Name. In the down example, the Block Type is resource, 
the Resource Type is random_string, and the Reference Name is foo. 
To create dependencies between resources, we use the reference name 
and type to access output values from the resource.	
  
  resource "random_string" "foo" {
	  length  = 4
	  upper   = false
	  special = false
	}

  resource "azurerm_resource_group" "bar" {
    name     = "rg-${random_string.foo.result}"
    location = var.location
  }

[Resources and Data Sources]

Resources and Data Sources are the core concepts when writting HCL,
resources allow us to call providors resources in order to perform an action
this means executing some new action if needed.
Data Sources by the other hand allow us to call resources directly from the 
providor, this means reviewing the state of a resource without limiting 
the scope to the state file.

  Resource Example:
	resource "random_string" "foobar" {
	  length  = 4
	  upper   = false
	  special = false
	}

  Data Source example:
  	data "azurerm_resource_group" "bar" {
	  name     = "rg-foo"
	  location = "westus"
	}


[LOCALS, TYPES, COLLECTIONS & OBJECTS]

- Locals: This are variables defined inside a .tf, and can be only access
    by the current module.
    Example of both writting and accesing:
    locals {
	    foo = "foo"
	    bar = "bar"
	    foobar = "${local.foo}${local.bar}"
	  }

    notice that declaring the block locals is in plural, but when
    accessing their values is on singular "local.<>"


-Types: For simplicity we only have, strings, numbers and booleans.

-Collections: we can work with lists and maps collections.


[INPUTS]
We can declare "input variables" inside terraform.
  Example:
  variable "foo" {
	  type        = string
	  description = "This is the value for foo. It is needed because 'reasons'. Its value must be less than 6 characters."
	}
  We declared the type and also a description as guidence to the user.

Variables also allow us to declare options:

- Sensitive Data: With this option we can tell Terraform to not display
  the output. 
  Example:
  	variable "super_secret_password" {
	  type        = string
	  description = "Password that I get from somewhere else"
	  sensitive   = true
	}

- Optional: We can specify that certain variables are optionals.
  Example:
  	variable "totally_optional_field" {
	  type        = string
	  description = "Yes, No, or Maybe"
	  default     = null
	}

- Validation: We can also apply some "constrains" in our variables.
  This is usefull for example in escenarios where different resources
  needs differents input format types.
  Clasical example (im gonna say just an invented example, not to mean real)
  in GCP VM names convention can not contain more than 30 characters and in AWS does.

  variable "name" {
	  type        = string
	  description = "Name of the thing"
	  validation {
	    condition     = length(name) < 30
	    error_message = "Length of name must be less than 30"
	  }
	}







