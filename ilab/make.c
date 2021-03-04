#include <stdio.h>
#include <stdlib.h>
int main()
    {
    system("gcc -c my_assemb.c");
    system("gcc -Wall my_assemb.o -o my_assemb");
    system("gcc -c stack.c proc.c");
    system("gcc -Wall stack.o proc.o -o proc");
    int err = system("./my_assemb CMD_ENG.txt");//запускаем prog.c
    if (!err) system("./proc Commands.txt");
    else printf("compilation error\n");
    }