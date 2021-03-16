#include "Assembler.h"


void* my_calloc (FILE* log_file, int size_of_elem, int size)
    {
    char* mem = (char*) calloc (size, size_of_elem);
    if (mem == NULL) 
            {
            printf("Calloc error\n");
            fprintf(log_file, "Calloc error\n");
            exit;
            }
    return mem;
    }

void get_lexemm(char* Input_buf, int* ri, char* temp, int* line_counter)
    {
    for (int k = 0; ((Input_buf[*ri] != ' ') || (Input_buf[*ri] != '\n') || (Input_buf[*ri] != '\0')) && (*ri < stat - 1); (*ri)++, k++)
        {
        temp[k] = Input_buf[*ri];
        }
    temp[k] = '\0';
    while ((Input_buf[*ri] == ' ') || (Input_buf[*ri] == '\n'))
        {
        if (Input_buf[*ri] == '\n')
            (*line_counter)++;
        (*ri)++;
        }
    }

int Start (char* Input_file_name, FILE* CMD_ENG, char* Input_buf, char* Output_buf, FILE* log_file)
    {
    struct stat statistica;
    int stat_error = stat (Input_file_name, &statistica);
    assert(stat_error == 0);
    char temp[max_lexemm_length];

    Input_buf = (char*) my_calloc (log_file, (statistica.st_size + 1), sizeof(char));

    fread ((void*) Input_buf, sizeof(char), statistica.st_size, CMD_ENG);

    Output_buf = (char*) my_calloc(log_file, (statistica.st_size + 1), sizeof(char));

    mark_t* labels = (mark_t*) my_calloc (log_file, labels_size, sizeof(mark_t));

    for (int z = 0; z < labels_size; z++)
        {
        (labels[z]).name = (char*) my_calloc (log_file, Label_name_size, sizeof(char));
        (labels[z]).pointer = -1;
        }
    }

void push_handling(char* Input_buf, char* Output_buf, int* ri, int* wi, FILE* log_file, int line_counter, char* temp)
    {
    if temp[0] = 'r';
        {
        Output_buf[*wi] = CMD_PUSH_R;
        (*wi)++;
        if (!strcmp(temp, "rax"))
            Output_buf[*wi] = CMD_RAX;
        else if (!strcmp(temp, "rbx"))
            Output_buf[*wi] = CMD_RBX;
        else if (!strcmp(temp, "rcx"))
            Output_buf[*wi] = CMD_RCX;
        else if (!strcmp(temp, "rdx"))
            Output_buf[*wi] = CMD_RDX;
        else 
            {
            fprintf(log_file, "ERROR: incorrect name of register, line %d\n", line_counter);
            exit;
            }
        }
    else
        {
        Output_buf[*wi] = CMD_PUSH;
        (*wi)++;
        char **endptr, numb_byte[4];
        int number = strtol(temp, endptr, 0);
        if (*endptr - temp - 1 != strlen(temp))
            {
            printf("Input error");
            fprintf(log_file, "ERROR: incorrect input in function \"push\", line %d\n", line_counter);
            exit;
            }
        for (int i = 0; i < data_size; i++)
            Output_buf[i + (*wi)] = (char) ((number >> 8*i) & 0xFF);   
        (*wi) += data_size - 1;    
        }
    }

void pop_handling(char* Input_buf, char* Output_buf, int* ri, int* wi, FILE* log_file, int line_counter, char* temp)
    {
    }


int assembling(mark_t* labels, const char* bufin, char* bufout, int stat, FILE* log_file)
    {
    int line_counter = 1;
    int ri = 0; // Reading bufer index
    int wi = 0; // Writing bufer index

    for (ri = 0; ri < stat - 1; ri++)
        {
        get_lexemm(Input_buf, &ri, temp);

        if (!strcmp(temp, "exit"))
            Ouput_buf[wi] = CMD_EXIT;

        else if (!strcmp(temp, "add"))
            Output_buf[wi] = CMD_ADD;

        else if (!strcmp(temp, "mul"))
            Output_buf[wi] = CMD_MUL;

        else if (!strcmp(temp, "mod"))
            Output_buf[wi] = CMD_MOD;
        
        else if (!strcmp(temp, "sub"))
            Output_buf[wi] = CMD_SUB;
        
        else if (!strcmp(temp, "scanf"))
            Output_buf[wi] = CMD_SCANF;
        
        else if (!strcmp(temp, "div"))
            Output_buf[wi] = CMD_DIV;
        
        else if (!strcmp(temp, "printf"))
            Output_buf[wi] = CMD_PRINTF;
        
        else if (!strcmp(temp, "push"))
            push_handling(Input_buf, Output_buf, &ri, &wi, log_file, line_couunter, temp);
        
        else if (!strcmp(temp, "pop"))
            pop_handling(Input_buf, Output_buf, &ri, &wi, log_file, line_couunter, temp);
        
        else if (!strcmp(temp, ""))
            Output_buf[wi] = CMD_;
        
        else if (!strcmp(temp, ""))
            Output_buf[wi] = CMD_;
        
        }
    }



int main(int argc, char* argv[])
    {
    FILE* log_file    = fopen("log.txt", "w");
    FILE* CMD_MACHINE = fopen("Commands.txt", "w");
    FILE* CMD_ENG     = fopen(argv[1], "r");
    char* Input_buf, *Output_buf;
    Start(argv[1], CMD_ENG, Input_buf, Output_buf, log_file);

    }