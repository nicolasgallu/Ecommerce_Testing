#!/bin/bash

# crear un bash idempotente, que al correrlo varias veces por error, o lo que
# fuere no genere ningun problema de duplicacion de procesos.

max_retrys=3


#Creation/Reset of auxiliar files.
if  [[ -f files_to_send.txt ]]; then
    > files_to_send.txt
else 
    touch files_to_send.txt
fi;

if  [[ -f upload_logger.txt ]]; then
    > upload_logger.txt
else 
    touch upload_logger.txt
fi;


if [ -z "$(ls ./data)" ]; then 
    echo "There is not data."
    exit
fi;

#Init Files & Start Process.
ls ./data | grep -v compressed > files_to_send.txt ;
echo "starting process..";


while IFS= read -r files_to_send; do
    echo "beggining from while loop"
    gzip -c ./data/$files_to_send > ./data/"${files_to_send}_compressed.csv.gz";
    echo "compression finish"

    for ((i=0; i<=max_retrys; i++)); do
        echo "try number: $i"
        if gcloud storage cp ./data/"${files_to_send}_compressed.csv.gz" gs://new-buck-test ; then
            echo "$files_to_send succesfully loaded in GCS" >> upload_logger.txt
            rm ./data/$files_to_send | rm ./data/"${files_to_send}_compressed.csv.gz"
            break
        elif [ $i == $max_retrys ]; then
            echo "max trys reached"
            echo "$files_to_send failed to load in GCS" >> upload_logger.txt 
        else
            echo "$files_to_send failed to load in GCS, trying again in 5 seconds.." 
            sleep 5
        fi; 
    done;
done < files_to_send.txt