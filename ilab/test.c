#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
    {
    int r = 321;
    FILE* fin = fopen("test.txt", "w");
    char a[10];
    fprintf(fin, "%s", '\0');
    fprintf(fin, "%s", "kak");
    fclose(fin);
    FILE* fout = fopen("test.txt", "r");

    fscanf(fin, "%s", a);
    fclose(fin);
    printf("%s", a);
    }