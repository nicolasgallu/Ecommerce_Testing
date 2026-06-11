#include <stdio.h>
#include <time.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdlib.h>



int main(){      
    time_t currentTime;
    time(&currentTime); // Get the current time
    printf("%s", ctime(&currentTime));
    srand(time(NULL)); 
    int r = rand() % 10;
    printf("%d\n", r);
}
