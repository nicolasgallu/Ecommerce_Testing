#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct {
    FILE *adrss_fp;
    int partition;
    int records;
    } Table;

void* aux(void* arg) {
    Table *tabla = (Table *) arg;
    int partition, start, end;
    
    partition = tabla->partition;
    start = tabla->partition * (tabla->records/2);
    end = (tabla->partition + 1) * (tabla->records/2);

    char line[100];

    printf("valores iniciales'\n");
    printf("start: %d\n", start);
    printf("end: %d\n", end);
    FILE *fp = tabla->adrss_fp;
    printf("did it.\n");
    for (int i = start; i <= end; i++) {
        snprintf(line, sizeof(line), "Partition: %d, ID: %d\n", partition, i);
        fprintf(fp,line);
    };

    return NULL;
};

int main() {

    int gigas;
    int user_choice;

    printf("Welcome Sr, how many Gigas do u want for today?: \n");
    scanf("%d", &gigas);

    printf("Are u sure u wanna create this sintetic data? 1= Yes, 0=No\n");
    scanf("%d", &user_choice);

    if (user_choice == 0) {
        return 0;
    };
    
    int lines = (1000000000 * gigas) / 25;
    FILE *fp = fopen("data.csv", "w");
    Table tabla[2];
    tabla[0].adrss_fp = fp;
    tabla[1].adrss_fp = fp;
    tabla[0].partition = 0;
    tabla[1].partition = 1;
    tabla[0].records = lines;
    tabla[1].records = lines;

    pthread_t th[2];

    for (int i=0; i < 2; i++){
        printf("particion inicial: %d\n",i);
        
        pthread_create(&th[i], NULL, aux, &tabla[i]);
    };

    for (int i=0; i < 2; i++){
        pthread_join(th[i], NULL);
    };

    fclose(fp);

    return 0;

}