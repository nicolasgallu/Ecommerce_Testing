#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>
#include <unistd.h>


int workers;

typedef struct {
    FILE *adrss_fp;
    int partition;
    int records;
    float progress;
    } Table;

typedef struct {
    Table *ptr_table[4];
    } ProgressTracker;

void* progress_bar(void* arg){
    ProgressTracker *ptracker = (ProgressTracker *) arg;
    int cond = 0; 
    float progress;
    float total_progress;
    sleep(3);
    while (total_progress < 300) {
        system("clear");
        for (int i=0; i<workers; i++) {
            cond++;
            Table *pointer = ptracker->ptr_table[i];
            progress = pointer->progress;
            printf("Puntero: %p | Progress: %3.f %%\n", pointer, progress);
            total_progress = total_progress + progress;
        }
}
}

void* aux(void* arg) {
    Table *tabla = (Table *) arg;
    int partition, start, end;
    
    partition = tabla->partition;
    start = tabla->partition * (tabla->records / workers);
    end = (tabla->partition + 1) * (tabla->records / workers);

    char line[100];

    FILE *fp = tabla->adrss_fp;
    for (int i = start; i <= end; i++) {
        snprintf(line, sizeof(line), "Partition: %d, ID: %d\n", partition, i);
        fprintf(fp,line);
        tabla->progress = (i/end) * 100 ;
    };
    return NULL;
};

int aux_time()
{
    time_t result = time(NULL);
    int epch_time = (intmax_t)result;
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

    printf("Sr, how many Workers do u need?: \n");
    scanf("%d", &workers);

    int lines = (1000000000 * gigas) / 25;

    Table tabla[workers];
    ProgressTracker ptracking;
    pthread_t th[workers];
    pthread_t th_master;

    int start,end;

    start = aux_time();
    printf("started epch: %d\n",start);

    
    pthread_create(&th_master, NULL, progress_bar, &ptracking);
    for (int i=0; i<workers; i++) {
        ptracking.ptr_table[i] = &tabla[i];
        char name[15];
        snprintf(name, sizeof(name), "data_%d.csv", i);
        tabla[i].adrss_fp = fopen(name, "w");
        tabla[i].partition = i;
        tabla[i].records = lines;
        printf("particion inicial: %d\n",i);
        pthread_create(&th[i], NULL, aux, &tabla[i]);
    }
    

    for (int i=0; i < workers; i++){
        pthread_join(th[i], NULL);
    };

    pthread_join(th_master, NULL);

    for (int i=0; i < workers; i++){
        FILE  *fp = tabla[i].adrss_fp;
        fclose(fp);
    };
    
    end = aux_time();
    printf("ended epch: %d\n",end);

    int dif = end - start;
    printf("segundos pasados: %d\n",dif);

    return 0;

}