#include <stdio.h>
#include <stdlib.h>
int main()
    {
    int r = 321;
    char a[20] = {'a'};
    sprintf(a, "%d", r);
    for (int i = 0; i < 20; i++)
        printf("GIT_TEST%d  ", a[i]); 
    printf("%d", atoi(a));
    }