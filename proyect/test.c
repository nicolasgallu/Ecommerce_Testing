#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>
#include <unistd.h>
#include <math.h>
#include <inttypes.h>
#include <string.h>


int workers;
int workers_activated = 0;

typedef struct {
    FILE *adrss_fp;
    int partition;
    long int records;
    float progress;
    int flag_finish;
    } Table;

typedef struct {
    Table *ptr_table[10];
    } ProgressTracker;

void* progress_bar(void* arg){
    ProgressTracker *ptracker = (ProgressTracker *) arg;
    float progress;
    int total = 0;
    int instance = 0;
    printf("\033[?25l");
    #define GREEN "\033[32m"
    #define WHT "\e[0;37m"
    while (workers_activated == 0) {
        printf("Master esperando threads...");
        printf("\r");
        fflush(stdout);
    }
    sleep(1);
    while (total < workers) {
        total = 0;
        for (int i = 0; i < workers; i++) {
            Table *pointer = ptracker->ptr_table[i];
            printf(GREEN "[Puntero: %p | Progress: %4.f %%]\n",  pointer, pointer->progress);   
            total += pointer->flag_finish; 
            if (i == workers-1 & total < workers) {
                for (int x = 0; x < workers; x++){
                    printf("\033[1A");
                }
                printf("\r");
            }
        }
        fflush(stdout);
        usleep(200000);
    }
    printf(WHT"\n");
    printf("\033[?25h");
    printf("main thread finished.\n");
}


void* aux(void* arg) {
    while (workers_activated == 0) {
    }    
    //initializing variables
    Table *tabla = (Table *) arg;
    FILE *fp = tabla->adrss_fp;
    tabla->flag_finish = 0;
    int partition;
    long int start, end;
    char buffer[4000];
    char new_row[50];
    int used_buffer = 0;
    //accesing table data
    partition = tabla->partition;
    start = partition * (tabla->records / workers);
    end = (partition + 1) * (tabla->records / workers);
    unsigned int seed = time(NULL) ^ pthread_self();

    time_t currentTime = time(NULL);
    struct tm timeinfo;
    localtime_r(&currentTime, &timeinfo);
    char now[32];
    strftime(now, sizeof(now), "%Y-%m-%d %H:%M:%S", &timeinfo);

    //CSV Headers
    fprintf(fp,"id,customer_ID,amount,created_at\n");
    for (long int i = start; i <= end; i++) {
        
        int amount = rand_r(&seed) %1000;
        int user_id = rand_r(&seed) %100;
        
        if (i%10000 == 0){
            strftime(now, sizeof(now), "%Y-%m-%d %H:%M:%S", &timeinfo);
            tabla->progress = ((float)i/ (float)end) * 100.0;
        }
         /*
            amount = max num of bytes = 4 bytes        
            user_id = max num of bytes = 4 bytes
            now =  32 bytes
            i = max num of byes = 8 bytes
            salto de linea = 2bytes
            total per line in worst case scenario = 50 bytes
         */
        int row_size = snprintf(new_row, sizeof(new_row), "%d,%d,%d,%s\n", i, amount, user_id, now);

        if (used_buffer + row_size <= sizeof(buffer)) {
            memcpy(buffer + used_buffer, new_row, row_size);
            used_buffer += row_size;
        }

        else {
            fwrite(buffer, 1, used_buffer, fp);
            fwrite(new_row, 1, row_size, fp);
            used_buffer = 0;
        }
        
    };
    
    if (used_buffer > 0 ) {
            fwrite(buffer, 1, used_buffer, fp);
        }
    tabla->flag_finish = 1;
    return NULL;
}

int aux_time()
{
    time_t result = time(NULL);
    int epch_time = (intmax_t)result;
};

int main() {

    int gigas;
    int user_choice;
    srand(time(NULL));

    printf("Welcome Sr, how many Gigas do u want for today?: \n");
    scanf("%d", &gigas);

    printf("Are u sure u wanna create this sintetic data? 1= Yes, 0=No\n");
    scanf("%d", &user_choice);

    if (user_choice == 0) {
        return 0;
    };

    printf("Sr, how many Workers do u need?: \n");
    scanf("%d", &workers);
    long int bytes_size = (pow(1000, 3) * gigas);
    printf("bytes_size: %" PRIu64 "\n", bytes_size);
    long int records = bytes_size / 25;
    printf("Records per Partition: %d\n", records);

    Table tabla[workers];
    ProgressTracker ptracking;
    pthread_t th[workers];
    pthread_t th_master;

    int start,end;

    start = aux_time();
    
    pthread_create(&th_master, NULL, progress_bar, &ptracking);
    
    for (int i=0; i<workers; i++) {
        ptracking.ptr_table[i] = &tabla[i];
        char name[15];
        snprintf(name, sizeof(name), "data_%d.csv", i);
        tabla[i].adrss_fp = fopen(name, "w");
        tabla[i].partition = i;
        tabla[i].records = records;
        pthread_create(&th[i], NULL, aux, &tabla[i]);
    }

    workers_activated =1;
    
    
    for (int i=0; i < workers; i++){
        pthread_join(th[i], NULL);
    };
    pthread_join(th_master, NULL);

    for (int i=0; i < workers; i++){
        FILE  *fp = tabla[i].adrss_fp;
        fclose(fp);
    };
    
    end = aux_time();
    int dif = end - start;
    printf("segundos pasados: %d\n",dif);
    return 0;

}