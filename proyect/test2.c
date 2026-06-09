#include <stdio.h>
#include <time.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdlib.h>


void loadingBar()
{   
    printf("\r%c", '[');
    for (int i = 0; i <= 10; i++) {
        int spaces_left = i - 10;
        int progress = i;
        //##########
        printf("\r[");
        for (int x = 0; x<=progress; x++) {
            printf("#");
        }
        sleep(1);
        printf("]");
        fflush(stdout);



    };
}

int main()
{
    loadingBar();
    printf("\n");
    return 0;
}