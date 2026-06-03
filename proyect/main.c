#include <stdio.h>


void names() {
    printf("nicolas");
}

void options(int num) {
    if (num == 2) {
        printf("%c\n","loquita");
    }
    else {
        printf("\nnot loquita");
    }
}

void lup() {
    for (int i = 0; i < 5; i++) {
    printf("%d\n", i);
}
}


int main() {

    int num = 12;
    float flt = 12.0;
    double dbl = 12.0505050;
    char name[] = "nicolas vito sebas";

    printf("%d\n", num);
    printf("%f\n", flt);
    printf("%f\n", flt);
    printf("%s\n", name);
    names();
    options(num);
    lup();

    return 0;

}