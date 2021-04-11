#include <cstdio>
#include <stdlib.h>
int main()
    {
    system("g++ Assembler.cpp -o Assembler");
    int err = system("./Assembler CMD_ENG.txt");
    if (err) printf ("compilation error\n");
    if (!err) 
        {
        system("g++ CPU.cpp stack_cpp.cpp -o CPU");
        system("./CPU Commands.txt");
        }
    else printf("compilation error\n");
    }