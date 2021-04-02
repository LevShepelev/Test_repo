#include <stdio.h>
#include <stdlib.h>
class Disasm
    {
    char* Input_;
    char* Output_;
    int InputSize_;
    int ri_;
    int wi_;
    char* lexemm_;
    FILE* log_file_;
    };



void* my_calloc (FILE* log_file, int size_of_elem, int size)
    {
    char* mem = (char*) calloc (size, size_of_elem);
    if (mem == NULL) 
        {
        printf("Calloc error\n");
        fprintf(log_file, "Calloc error\n");
        exit (1);
        }
    return mem;
    }



Disasm::Disasm (char* file_name)
    {
    struct stat statistica;
    int stat_error = stat (Input_file_name, &statistica);
    assert(stat_error == 0);
    log_file_ = fopen("log_disasm.txt", "w");
    Input_ = (char*) my_calloc (log_file, (statistica.st_size + 1), sizeof(char));
    Output_ = char*) my_calloc (log_file, (statistica.st_size + 1), sizeof(char));
    fread ((void*) Input_, sizeof(char), statistica.st_size, file_name);
    ri_ = 0;
    wi_ = 0;
    InputSzie_ = statistica.st_size;
    }



int main(int argc, char* argv[])
    {
    Disasm pr(argv[1]);
    for (ri_ = 0; ri_ <  InputSize_; ri_++);

    }