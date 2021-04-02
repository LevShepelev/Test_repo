#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <math.h>
int main()
    {
        struct stat statistica;

    FILE* fin = fopen("test.txt", "r");
    int stat_error = stat ("test.txt", &statistica);

    char* bufin = (char*) calloc ((statistica.st_size + 1), sizeof(char));
    fread ((void*) bufin, sizeof(char), statistica.st_size, fin);
    for (int i = 0; i < 9; i++)
        printf("%f\n", sqrt(bufin[i]));
    }