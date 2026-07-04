from datetime import datetime, timedelta
from airflow import DAG
from airflow.providers.standard.operators.bash import BashOperator


REPO_PATH = "/home/nicolas/Escritorio/work/personal/snowflake_project/proyect/"


default_args = {
    "owner": "admin",
    "retries": 1,
    "retry_delay": timedelta(seconds=30),
    "email": ["nicolasgallu@pm.me"],
    "email_on_failure": True,
    "email_on_retry": False,
}

with DAG(
    dag_id="run_existing_gcs_bash_script",
    start_date=datetime(2026, 6, 1),
    schedule=None,
    catchup=False,
    default_args=default_args,
    tags=["local", "bash", "gcs"],
) as dag:

    t0 = BashOperator(
        task_id="run_data_generation",
        bash_command=f"cd {REPO_PATH} && bash generate_data.sh ",
    )

    t1 = BashOperator(
        task_id="run_upload_script",
        bash_command=f"cd {REPO_PATH} && bash load_to_gcp.sh ",
    )

    t2 = BashOperator(
        task_id="run_load_to_gbq",
        bash_command=f"cd {REPO_PATH} && bash load_to_gbq.sh ",
    )

t0 >> t1 >> t2