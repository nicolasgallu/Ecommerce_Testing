What is Snowflake?

Snowflake is a data cloud service that allows us to centralize
data from diferent sources.
Allowing us to store, transform, query, analyse large amount of data.

Is similar to a Warehouse, but with some steroids:
Snowflake’s docs describe core concepts like databases, schemas, tables, 
warehouses, stages, streams, tasks, dynamic tables, and Snowpark as part of the platform.

#Data Engineer Guide to work with snowflake.

1. What kind of data im ingesting?
  - CSV
  - JSON
  - PARQUET
  - AVRO
  - DATABASES TABLES
  - EVENT STREAMS
  - LOGS

2. Where the data comes from?
  - S3
  - Azure Blob Storage
  - Google Cloud Storage
  - Local files
  - Databases
  - Kafka / streaming tools
  - ETL tools like Fivetran, Airbyte, Matillion, dbt, etc.

3. SNOWFLAKE OBJECTS

WAREHOUSE: is where the compute is done (this allow u to work with basic sql features and more)

CREATE WAREHOUSE dev_wh
  WAREHOUSE_SIZE = 'XSMALL'
  AUTO_SUSPEND = 60
  AUTO_RESUME = TRUE
  INITIALLY_SUSPENDED = TRUE;

DATABASES: Serves as a way to organize data-project related
SCHEMAS: Serves to organize inter data-project
TABLES: Place were we will store the data
STREAMS: Streams is an object that detect new/updated rows inside a table.
TAKS: Is a snowflake schedule job, this is basic to automatize indeed tasks, 
  it can be created to run also with a trigger instead.
PIPE: Snowpipe are used for automatic dataload (copy into), cause it runs 
at the moment we receive the file.

-- SNOWFLAKE DAY TO DAY USE

1.DATA INGESTION

Data ingestion is the whole point, for this we are gonna learn the required steps
in order to being able to load data inside the SF.

[step 1]
File formats: is the way to tell snowflake how to read the data.
In Snowflake, you create a file format with SQL so that you can reuse it for multiple 
loads. Here’s a simple example for a CSV file:
  CREATE OR REPLACE FILE FORMAT csv_format
      TYPE = CSV
      FIELD_DELIMITER = ','
      SKIP_HEADER = 1
      NULL_IF = ('NULL', 'null', '')
      EMPTY_FIELD_AS_NULL = TRUE
      FIELD_OPTIONALLY_ENCLOSED_BY = '"';

[step 2]
Stages: Stages are the landing zone for the data.
There are both Internals and Externals, in summary when we talk about internals, we
refeer to self-hosted snowflake storage, and with externals we cover the 3 Biggest
(Amazon S3, Google Cloud storage, Microsoft Azure containers).

[step 3]
COPY-INTO: copy into is the final step and basically where we gather both file formats, 
target tables, and stages.
Here is were we finally ingest the data normally into a raw layer of our DB.


[ingestion methods]
FULL REFRESH: is simpler to build but expensive combined with manual approach, 
then we have a mix of wasted time/money.
List of issues related with full refresh.
  - It costs more compute.
  - It takes longer.
  - It can lock you into long refresh windows.
  - It can break downstream dashboards while rebuilding.
  - It can duplicate data if you append incorrectly.
  - It can erase history if you overwrite incorrectly.
  - It makes recovery harder.

APPEND:Perserve the olds records, and add the new ones.

INCREMENTAL: Are what we know in SQL as upserting methods, 
were we only update what is new.
Logic Concept
  - Detect changed data.
  - Load changed data into a staging/change table.
  - MERGE it into the target table.
  - Only update what needs to change.

The [MERGE] command is in charge of this operation.
It can insert, update, or delete rows in a target table based on whether 
rows match a source dataset.
The command supports semantics for handling the following cases:
Values that match (for updates and deletes).
Values that don’t match (for inserts).

Incremental Logic is based on this question:
How do I know which rows changed since the last successful run?
To answer that we need one or more fo this keys:
  - A unique key
  - A timestamp column
  - A batch/load date
  - A source file name
  - A change-data-capture mechanism
  - A stream

The most important one is the UNIQUE KEY, this field
allow us to identify when 2 sources represent the same
entity/event.
Examples:
  - order_id
  - customer_id
  - product_id

Conceptually what we need is to follow a mental model like:
1. Source table: this is where our raw data lives.
2. Target table: table that we want to maintain incrementally.
3. Unique key: identifier to match rows between tables.
4. Change detection logic: field that allow us to detect if the row changed 
    since the last sync. we can use different strategies, 
    even snowflake streams.
5. MERGE statement: is the snowflake method that allow us to run this operation.
6. Metadata columns: this helps you debug and control the pipeline.
7. Validation checks: this is the usual D.E sanity check control.
    - How many rows inserted?
    - How many rows updated?
    - Any duplicates?
    - Any null keys?
    - Did row count increase as expected?

The [stream] is an object that track and stores DML changes into a table, view,
dynamic tables, external tables.

What a [stream] shows?

Imagine your raw table: raw.orders_raw
    order_id | status  | updated_at
    1        | pending | 2026-05-17

Then you insert a new version:
    order_id | status | updated_at
    1        | paid   | 2026-05-18

The stream can expose the new changed row plus metadata columns:
    order_id | status | updated_at  | METADATA$ACTION | METADATA$ISUPDATE
    1        | paid   | 2026-05-18  | INSERT          | FALSE

Important metadata columns:
    METADATA$ACTION     → INSERT or DELETE
    METADATA$ISUPDATE   → whether the row is part of an update operation
    METADATA$ROW_ID     → internal row identifier


Consuming data from a [stream], a stream keeps track of changes since 
its last consumption point.
This means that if you used the steam in a DML operation, snowflake
consider those record already "consumed" and would no be showed again.
A stream should be consumed regularly; if it is not consumed within the 
source table’s retention window, it can become stale and lose access 
to unconsumed change records.

How to create [streams]?
  CREATE OR REPLACE STREAM <db>.<schema>.<stream_name>
  ON TABLE <db>.<schema>.<table>;

The [tasks] are the object that allow us to run sql, procedures, and even scripts
automatically.
REF: https://docs.snowflake.com/en/user-guide/tasks-intro

Task creation workflow overview
  1. Create a task administrator role that can run the commands in the following steps.
  2. Define a new task using CREATE TASK.
  3. Define compute resources
  4. Define schedules or triggers
  5. Define what happens when a task fails
  6. Define additional session parameters
  7. Manually test tasks using EXECUTE TASK.
  8. Allow the task to run continuously using ALTER TASK … RESUME.
  9. Monitor task costs
  10. Refine the task as needed using ALTER TASK.

Example for our auto-merge goal with stream:
  CREATE TASK <task_name>
    WHEN SYSTEM$STREAM_HAS_DATA(<stream_name>)
    AS
      <logic to automatize>

Snowflake creates all tasks in the SUSPENDED state, thats why u need to 
activate it manually.
  ALTER TASK <db.schema.task_name> RESUME;





LOCAL CLI CONNECTION
for linux, download the corresponding package according to your pc requiremens,
and compression tool.

after that go to the snwoflake config file (.toml) and add this data:
[connections.my_dev_env]
account = "account identifier"
user = "user name (from snowflake)"
password = "user password (from snowflake)"

After doing that u can run the following command to check the connection.
-- snow connection test --connection my_dev_env

To send a file for example you can use:
 snow sql --connection my_dev_env -q "PUT file:your_source_file.csv @%your_target_stage AUTO_COMPRESS=TRUE;"



COMMANDS CHEATSHEET

----"""SOME USEFULL COMMANDS"""
-- SELECT CURRENT_USER()
-- SELECT CURRENT_ROLE()
-- USE ROLE <role to pick>

--SELECT CURRENT_WAREHOUSE()

--USER WAREHOUSE <your warehouse name>

--LIST @<db.schema>.%<table name>;

--LIST @learning_db.raw.%orders

--REMOVE @learning_db.raw.%orders/commerce_orders_dataset.csv.gz

-- describe file format learning_db.raw.csv_format

--COPY INTO learning_db.raw.orders
--FROM @learning_db.raw.%orders
--FILE_FORMAT = (FORMAT_NAME = 'learning_db.raw.csv_format')
--select * from learning_db.staging.stg_orders
--select * from learning_db.raw.orders


MERGE INTO learning_db.staging.stg_orders AS target
USING (
     
    SELECT
        ORDER_ID::varchar AS  ORDER_ID,
        ORDER_DATE::timestamp AS  ORDER_DATE,
        CUSTOMER_ID::varchar AS  CUSTOMER_ID,
        PRODUCT::varchar AS  PRODUCT,
        QUANTITY::int AS  QUANTITY,
        UNIT_PRICE::float AS  UNIT_PRICE,
        UPDATED_AT::timestamp AS  UPDATED_AT
    FROM learning_db.raw.orders
    WHERE order_id IS NOT NULL
    QUALIFY ROW_NUMBER() OVER (
        PARTITION BY order_id
        ORDER BY updated_at asc
    ) = 1
) AS source
ON target.order_id = source.order_id

WHEN MATCHED
     AND source.updated_at > target.updated_at
THEN UPDATE SET
    target.ORDER_DATE = source.ORDER_DATE,
    target.CUSTOMER_ID = source.CUSTOMER_ID,
    target.PRODUCT = source.PRODUCT,
    target.QUANTITY = source.QUANTITY,
    target.UNIT_PRICE = source.UNIT_PRICE,
    target.UPDATED_AT = source.UPDATED_AT

WHEN NOT MATCHED THEN INSERT (
    ORDER_ID,
    ORDER_DATE,
    CUSTOMER_ID,
    PRODUCT,
    QUANTITY,
    UNIT_PRICE,
    UPDATED_AT
)
VALUES (
    ORDER_ID,
    ORDER_DATE,
    CUSTOMER_ID,
    PRODUCT,
    QUANTITY,
    UNIT_PRICE,
    UPDATED_AT
);
