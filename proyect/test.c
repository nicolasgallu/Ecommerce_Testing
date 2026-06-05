#include <stdio.h>


int main() {

    FILE *fp = fopen("data.csv", "w");

    char name[] = "Customer";
    int var;
    printf("please enter a number: \n");
    scanf("%d", &var);
    for (int i = 1; i<=var; i++) {
        fprintf(fp,"Name: %s, ID: %d\n", name, i);
    };

    fclose(fp);

    fopen("data.csv", "r");
    char line[10];

    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    };
    
    fclose(fp);
    return 0;

}