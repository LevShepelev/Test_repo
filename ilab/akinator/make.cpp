#include <cstdio>
#include <stdlib.h>
int main()
    {
    system("g++ -o akinator akinator.cpp");
    int err = system("./akinator");
    if (err) printf ("compilation error\n");
    }