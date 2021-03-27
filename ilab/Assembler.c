#include "Assembler.h"



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



void Finishing(FILE* CMD_MACHINE, FILE* CMD_ENG, mark_t* labels, assemb_t* pr)
    {
    assert((pr != NULL) || (labels != NULL));
    for (int z = 0; z < labels_size; z++)
        free((labels[z]).name); 
    free(pr -> Input);
    free(pr -> Output);
    pr -> Input  = (void*) 1;
    pr -> Output = (void*) 1;
    fclose(pr -> log_file);
    fclose(CMD_MACHINE);
    fclose(CMD_ENG);
    printf("Succesfully compiled\n");
    }



void write_number_like_chars(int number, assemb_t* pr)
    {
    assert(pr != NULL);
    for (int i = 0; i < data_size; i++, pr -> wi++)
        {
        pr -> Output[pr -> wi] = ((char) (number >> 8*i)) & 0xFF;
        printf("write_number = %d\n", pr -> Output[pr -> wi]);
        }
    pr -> wi--;
    }



void error_report(assemb_t* pr, char* message)
    {
    assert(pr != NULL);
    printf(message, pr -> line_counter);
    fprintf(pr -> log_file, message, pr -> line_counter);
    exit (1);
    }
    


void get_lexemm(assemb_t* pr)
    {
    assert(pr != NULL);
    int k = 0;
    for (k = 0; (pr -> Input[pr -> ri] != ' ') && (pr -> Input[pr -> ri] != '\n') && (pr -> Input[pr -> ri] != ';') && (pr -> ri < pr -> buf_size); pr -> ri++, k++)
        pr -> lexemm[k] = pr -> Input[pr -> ri];
    pr -> lexemm[k] = '\0';
    if (pr -> Input[pr -> ri] == ';')
        for (; pr -> Input[pr -> ri] != '\n'; pr -> ri++) // comments
            ;
    do 
        {
        if (pr -> Input[pr -> ri] == '\n')
            (pr -> line_counter)++;
        pr -> ri++;
        } while (((pr -> Input[pr -> ri] == ' ') || (pr -> Input[pr -> ri] == '\n')) && pr -> ri < pr -> buf_size - 1);
    }



int Start (char* Input_file_name, FILE* CMD_ENG, assemb_t* pr, mark_t* labels)
    {
    assert((pr != NULL) || (labels != NULL));
    struct stat statistica;
    int stat_error = stat (Input_file_name, &statistica);
    assert(stat_error == 0);

    pr -> Input = (char*) my_calloc (pr -> log_file, (statistica.st_size + 1), sizeof(char));

    fread ((void*) pr -> Input, sizeof(char), statistica.st_size, CMD_ENG);

    pr -> Output = (char*) my_calloc(pr -> log_file, data_size * (statistica.st_size + 1), sizeof(char));

    pr -> buf_size = statistica.st_size;

    pr -> line_counter = 1;

    for (int z = 0; z < labels_size; z++)
        {
        (labels[z]).name = (char*) my_calloc (pr -> log_file, Label_name_size, sizeof(char));
        (labels[z]).pointer = -1;
        }
    }



void push_handling(assemb_t* pr)
    {
    assert(pr != NULL);
    get_lexemm(pr);
    printf("lexemm = %s\n", pr -> lexemm);
    if (pr -> lexemm[0] == 'r')
        {
        pr -> Output[pr -> wi] = CMD_PUSH_R;
        pr -> wi++;
        if (!strcmp(pr -> lexemm, "rax"))
            pr -> Output[pr -> wi] = CMD_RAX;
        else if (!strcmp(pr -> lexemm, "rbx"))
            pr -> Output[pr -> wi] = CMD_RBX;
        else if (!strcmp(pr -> lexemm, "rcx"))
            pr -> Output[pr -> wi] = CMD_RCX;
        else if (!strcmp(pr -> lexemm, "rdx"))
            pr -> Output[pr -> wi] = CMD_RDX;
        else 
            error_report(pr, "ERROR: incorrect name of register, line %d\n");
        }
    else
        {
        pr -> Output[pr -> wi] = CMD_PUSH;
        pr -> wi++;
        char *endptr, numb_byte[data_size];
        int number = strtol(pr -> lexemm, &endptr, 0);
        if (endptr - (pr -> lexemm) != strlen(pr -> lexemm))
            error_report(pr, "ERROR: incorrect input in function \"push\", line %d\n");
        write_number_like_chars(number, pr);
        }
    }



void pop_handling(assemb_t* pr)
    {
    assert(pr != NULL);
    get_lexemm(pr);
    printf("lexemm = %s\n", pr -> lexemm);
    if (pr -> lexemm[0] = 'r')
        {
        pr -> Output[pr -> wi] = CMD_POP_R;
        pr -> wi++;
        if (!strcmp(pr -> lexemm, "rax"))
            pr -> Output[pr -> wi] = CMD_RAX;
        else if (!strcmp(pr -> lexemm, "rbx"))
            pr -> Output[pr -> wi] = CMD_RBX;
        else if (!strcmp(pr -> lexemm, "rcx"))
            pr -> Output[pr -> wi] = CMD_RCX;
        else if (!strcmp(pr -> lexemm, "rdx"))
            pr -> Output[pr -> wi] = CMD_RDX;
        else if (!strcmp(pr -> lexemm, "rsi"))
            pr -> Output[pr -> wi] = CMD_RSI;   
        else 
            error_report(pr, "ERROR: incorrect name of register, line %d\n");
        }
    }



void Label_handling(assemb_t* pr, mark_t* labels)
    {
    assert((pr != NULL) || (labels != NULL));
    int i = 0;
    if (strchr(pr -> lexemm, ':') - pr -> lexemm == strlen(pr -> lexemm) - 1)
        {
        for (i = 0; i < labels_size; i++)
            if (strcmp(pr -> lexemm, labels[i].name) == 0)
                {
                pr -> wi--;
                return;
                }
        for (i = 0; labels[i].pointer != -1; i++)
            if (i == labels_size) 
                {
                error_report(pr, "Too many labels in program, max number %d\n");
                break;
                }            
        strcpy(labels[i].name, pr -> lexemm);
        labels[i].pointer = pr -> wi;
        pr -> wi--;
        }
    else 
        error_report(pr, "Incorrect name of label, line %d\n");
    }



void Jump_handling(assemb_t* pr, mark_t* labels)
    { 
    assert((pr != NULL) || (labels != NULL));
    int i = 0;
    pr -> wi++;
    get_lexemm(pr);
    for (i = 0; i < labels_size; i++)
        if (strcmp(labels[i].name, pr -> lexemm) == 0) 
            {
            printf("HERE lexemm = %s\n", pr -> lexemm);
            write_number_like_chars(labels[i].pointer, pr);
            return;
            }
    if ((i == labels_size) && (pr -> assembling_level == 1)) 
        error_report(pr, "Label has not wound line %d\n");
    else pr -> wi += data_size - 1;
    }



int assembling(mark_t* labels, assemb_t* pr)
    {
    assert((pr != NULL) || (labels != NULL));
    pr -> line_counter = 0;
    pr -> wi = 0;
    int IsExit = 0;
    for (pr -> ri = 0; pr -> ri < pr -> buf_size; pr -> wi++)
        {
        get_lexemm(pr);
        printf("wi = %d lexemm = %s\n", pr -> wi,  pr -> lexemm);

        if (strchr(pr -> lexemm, ':') != NULL)
            Label_handling(pr, labels);
        
        else if (!strcmp(pr -> lexemm, "exit"))
            {
            pr -> Output[pr -> wi] = CMD_EXIT;
            IsExit = 1;
            }

        else if (!strcmp(pr -> lexemm, "add"))
            pr -> Output[pr -> wi] = CMD_ADD;

        else if (!strcmp(pr -> lexemm, "mul"))
            pr -> Output[pr -> wi] = CMD_MUL;

        else if (!strcmp(pr -> lexemm, "mod"))
            pr -> Output[pr -> wi] = CMD_MOD;
        
        else if (!strcmp(pr -> lexemm, "sub"))
            pr -> Output[pr -> wi] = CMD_SUB;
        
        else if (!strcmp(pr -> lexemm, "scanf"))
            pr -> Output[pr -> wi] = CMD_SCANF;
        
        else if (!strcmp(pr -> lexemm, "div"))
            pr -> Output[pr -> wi] = CMD_DIV;
        
        else if (!strcmp(pr -> lexemm, "printf"))
            pr -> Output[pr -> wi] = CMD_PRINTF;
        
        else if (!strcmp(pr -> lexemm, "push"))
            push_handling(pr);
        
        else if (!strcmp(pr -> lexemm, "pop"))
            pop_handling(pr);

        else if (!strcmp(pr -> lexemm, "ret"))
            pr -> Output[pr -> wi] = CMD_RET;

        else if (!strcmp(pr -> lexemm, "call"))
            {
            pr -> Output[pr -> wi] = CMD_CALL;
            Jump_handling(pr, labels);
            }

        else if (!strcmp(pr -> lexemm, "jmp"))
            {
            pr -> Output[pr -> wi] = CMD_JMP;
            Jump_handling(pr, labels);
            }

        else if (!strcmp(pr -> lexemm, "jmpb"))
            {
            pr -> Output[pr -> wi] = CMD_JMPB;
            Jump_handling(pr, labels);
            }

        else if (!strcmp(pr -> lexemm, "jmpa"))
            {
            pr -> Output[pr -> wi] = CMD_JMPA;
            Jump_handling(pr, labels);
            }

        else if (!strcmp(pr -> lexemm, "jmpe"))
            {
            pr -> Output[pr -> wi] = CMD_JMPE;
            Jump_handling(pr, labels);
            }

        else if (!strcmp(pr -> lexemm, "jbe"))
            {
            pr -> Output[pr -> wi] = CMD_JBE;
            Jump_handling(pr, labels);
            }

        else if (!strcmp(pr -> lexemm, "jae"))
            {
            pr -> Output[pr -> wi] = CMD_JAE;
            Jump_handling(pr, labels);
            }

        else if (!strcmp(pr -> lexemm, "jne"))
            {
            pr -> Output[pr -> wi] = CMD_JNE;
            Jump_handling(pr, labels);
            }
        else if (!strcmp(pr -> lexemm, "debug"))
            pr -> Output[pr -> wi] = CMD_DEBUG;

        else error_report(pr, "Command has not found, line %d\n");
        }
    if (IsExit == 0) 
        error_report(pr, "exit was not found");
    }



int main(int argc, char* argv[])
    {
    char lexem[max_lexemm_length];
    assemb_t pr = {NULL, NULL, 0, 0, NULL, 0, NULL, 0, 0};
    mark_t labels[labels_size];

    pr.lexemm = lexem;
    pr.log_file         = fopen("log.txt", "w");
    FILE* CMD_MACHINE   = fopen("Commands.txt", "w");
    FILE* CMD_ENG       = fopen(argv[1], "r");

    Start(argv[1], CMD_ENG, &pr, labels);

    assembling(labels, &pr);
    printf("\nSecond Assembling\n");
    pr.assembling_level = 1;
    assembling(labels, &pr);

    for (int i = 0; i < pr.wi; i++)
        {
        fprintf(CMD_MACHINE, "%c", pr.Output[i]);
        printf("%d ID = %d\n", pr.Output[i], i);
        }
    
    Finishing(CMD_MACHINE, CMD_ENG, labels, &pr);
    }