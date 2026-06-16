from datetime import datetime
from airflow import DAG
from airflow.providers.standard.operators.bash import BashOperator


REPO_PATH = "/home/nicolas/Escritorio/work/personal/snowflake_project/proyect/"

with DAG(
    dag_id="run_existing_gcs_bash_script",
    start_date=datetime(2026, 6, 1),
    schedule=None,
    catchup=False,
    tags=["local", "bash", "gcs"],
) as dag:

    run_upload_script = BashOperator(
        task_id="run_upload_script",
        bash_command=f"cd {REPO_PATH} && bash upload_to_gcs.sh",
    )