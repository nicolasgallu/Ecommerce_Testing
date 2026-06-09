#include <stdio.h>
#include <time.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{    //(float) ((i/end) * 100)
    float num = 39998;
    float base = 40000;
    float result = num / base;
    printf("result %f", result);
}