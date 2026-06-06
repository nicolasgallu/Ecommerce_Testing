#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <inttypes.h>
#include <time.h>

int aux_time()
{
    time_t result = time(NULL);
    int epch_time = (intmax_t)result;
};


int workers;

typedef struct {
    int partition;
    int records;
    } Table;

void* aux(void* arg) {
    sleep(3);
    Table *tabla = (Table *) arg;
    int partition;
    
    partition = tabla->partition;

    for (int i = 0; i <= 1000*1000; i++) {
        //printf("partition:%d number:%d\n",partition,i);
    };
    return NULL;
};

int main() {

    printf("Sr, how many Workers do u need?: \n");
    scanf("%d", &workers);

    Table tabla[workers];    
    pthread_t th[workers];

    int start,end;

    start = aux_time();
    printf("started epch: %d\n",start);

    for (int i=0; i<workers; i++) {
        tabla[i].partition = i;
        //printf("particion inicial: %d\n",i);
        pthread_create(&th[i], NULL, aux, &tabla[i]);
    }

    for (int i=0; i < workers; i++){
        pthread_join(th[i], NULL);
    };

    end = aux_time();
    printf("ended epch: %d\n",end);

    int dif = end - start;
    printf("segundos pasados: %d\n",dif);

    return 0;

}