#include <stdio.h>
#include <stdlib.h>
int main()
    {
    system("gcc -c Assembler.c");
    system("gcc -Wall Assembler.o -o Assembler");
    int err = system("./Assembler CMD_ENG.txt");
    if (err) printf ("compilation error\n");
    //if (!err) system("./proc Commands.txt");
    //else printf("compilation error\n");
    }