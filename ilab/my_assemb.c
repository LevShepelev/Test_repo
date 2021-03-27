#include "my_assemb.h"

void Finishing(FILE* CMD_MACHINE, FILE* CMD_ENG, FILE* log_file, mark_t* labels, char* bufout, char* bufin)
    {
    for (int z = 0; z < labels_size; z++)
        free(labels[z].name); 
    fclose(log_file);
    free(bufout);
    free(bufin);
    fclose(CMD_MACHINE);
    fclose(CMD_ENG);
    }

int Jumping(const char* bufin, char* bufout, mark_t* labels, FILE* log_file, int jump_type, int* i, int* j, int line_counter, int assemb_level)
    {
    for (int e = 0; e < labels_size; e++)
        {
        printf("Label[%d] = %d,  %s", e, labels[e].pointer, labels[e].name);
        }
    printf("Hello\n");
    int k = 0, length = 0, debug;
    while (bufin[*i] != ' ');
        i++;
    i++;
    while (bufin[*i + length] != ':')
        {
        if (bufin[*i] == '\n')
            {
            if (assemb_level == 1) fprintf(log_file, "ERROR: incorrect format of function \"jump\", line %d\nexample: jmp HELL:\n", line_counter);
                break;
                return -1;
            }
        length++;
        }
    for (int z = 0; z < length; z++)
        printf("%d ", bufin[*i + z]);
    for (k = 0; (strncmp((bufin + *i), labels[k].name, length) != 0); k++)
        if (k == labels_size - 1) 
            {
            k++;
            break;
            }
        if (k < labels_size)
            {
            char p[max_pointer];
            bufout[*j] = jump_type;
            (*j)++;
            int t = *j;
            sprintf(p, "%d", labels[k].pointer);
            while (p[*j - t] != 0)
                {
                bufout[*j] = p[(*j) - t];
                (*j)++;
                }
            (*j)--;
            }
        else 
        if (assemb_level == 1) 
            {
            fprintf(log_file, "ERROR: Label has not been found line %d\n", line_counter);
            return -1;
            }
    printf("\n%d\n", bufin[*i]);
    }

int assemb(mark_t* labels, const char* bufin, char* bufout, int stat, FILE* log_file, int assemb_level)
    {
    int i = 0, j = 0, mark_index = 0, line_counter = 1, debug;
    for (i = 0; i < stat - 1; i++, j += 2)
        {
        if (!strncmp((bufin + i), "pop r", 5))
            {
            printf("pop r\n");
            bufout[j] = CMD_POP_R;
            if ((bufin[i + 5] >= '0') && (bufin[i + 5] <= '9') && (bufin[i + 6] >= '0') && (bufin[i + 6] <= '9'))
                {
                bufout[j + 1] = bufin[i + 5] - '0';
                bufout[j + 2] = bufin[i + 6] - '0';
                j += 2;
                i += 6;
                }
            else 
                {
                if (assemb_level == 1) fprintf(log_file, "ERROR: incorrect name of register, line %d\n", line_counter);
                return -1;
                }
            }
        else 
        if (!strncmp((bufin + i), "push r", 6))
            {
            printf("push r\n");
            bufout[j] = CMD_PUSH_R;
            if ((bufin[i + 6] >= '0') && (bufin[i + 6] <= '9') && (bufin[i + 7] >= '0') && (bufin[i + 7] <= '9'))
                {
                bufout[j + 1] = bufin[i + 6] - '0';
                bufout[j + 2] = bufin[i + 7] - '0';
                j += 2;
                i += 7;
                }
            else 
                {
                if (assemb_level == 1) fprintf(log_file, "ERROR: incorrect name of register, line %d\n", line_counter);
                return -1;
                }
            }
        else
        if (!strncmp((bufin + i), "push", 4))
            {
            printf("push\n");
            bufout[j] = CMD_PUSH;
            j++;
            i += 5;
            while (bufin[i] != '\n')
                {
                if ((bufin[i] >= '0') && (bufin[i] <= '9'))
                    {
                    bufout[j] = bufin[i];
                    i++;
                    j++;
                    }
                else 
                    {
                    if (assemb_level == 1) fprintf(log_file, "ERROR: incorrect input in function \"push\", line %d\n", line_counter);
                    return -1;
                    }
                }
            i--;
            j--;
            }
        else
        if (!strncmp((bufin + i), "printf", 6))
            {
            printf("printf\n");
            bufout[j] = CMD_PRINTF;
            }
        else
        if (!strncmp((bufin + i), "jmpb", 4))
            {
            printf("jmpb\n");
            if (Jumping(bufin, bufout, labels, log_file, CMD_JMPB, &i, &j, line_counter, assemb_level) < 0)
                return -1;
            }
        else
        if (!strncmp((bufin + i), "jmpa", 4))
            {
            printf("jmpb\n");
            if (Jumping(bufin, bufout, labels, log_file, CMD_JMPA, &i, &j, line_counter, assemb_level) < 0)
                return -1;
            }
        else
        if (!strncmp((bufin + i), "jmpe", 4))
            {
            printf("jmpb\n");
            if (Jumping(bufin, bufout, labels, log_file, CMD_JMPE, &i, &j, line_counter, assemb_level) < 0)
                return -1;
            }
        else
        if (!strncmp((bufin + i), "jae", 3))
            {
            printf("jmpb\n");
            if (Jumping(bufin, bufout, labels, log_file, CMD_JAE, &i, &j, line_counter, assemb_level) < 0)
                return -1;
            }
        else
        if (!strncmp((bufin + i), "jbe", 3))
            {
            printf("jmpb\n");
            if (Jumping(bufin, bufout, labels, log_file, CMD_JBE, &i, &j, line_counter, assemb_level) < 0)
                return -1;
            }
        else
        if (!strncmp((bufin + i), "jne", 3))
            {
            printf("jmpb\n");
            if (Jumping(bufin, bufout, labels, log_file, CMD_JNE, &i, &j, line_counter, assemb_level) < 0)
                return -1;
            }
        else
        if (!strncmp((bufin + i), "jmp", 3))
            {
            printf("jmp\n");
            if (Jumping(bufin, bufout, labels, log_file,  CMD_JMP, &i, &j, line_counter, assemb_level) < 0)
                return -1; 
            }
        else
        if ((bufin[i] > 'A') && (bufin[i] < 'Z')) // заполнение массива меток (указатели)
            {
            int length = 0, ind = 0, k = 0, z = 0;
            while (bufin[i + length] != ':')
                {
                if (bufin[i] == '\n')
                    {
                    if (assemb_level == 1) fprintf(log_file, "ERROR: incorrect format of function \"jump\", line %d\nexample: jmp HELL:\n", line_counter);
                    return -1;
                    }
                length++;
                }
            for (k = 0; (strncmp(bufin + i, labels[k].name, length) != 0); k++)
                if (k == labels_size - 1) break;
            if (k >= labels_size - 1) // Создаем Новую Метку
                {
                for (z = 0; z < length; z++)
                    labels[mark_index].name[z] = bufin[i + z];
                labels[mark_index].name[z] = '\0';
                labels[mark_index].pointer = j;
                mark_index++;
                }
            j -= 2;
            }
        else 
        if (!strncmp((bufin + i), "exit", 4))
            {
            printf("exit\n");
            bufout[j] = CMD_EXIT;
            }
        else
        if (!strncmp((bufin + i), "add", 3))
            {
            printf("add\n");
            bufout[j] = CMD_ADD;
            }
        else
        if (!strncmp((bufin + i), "mul", 4))
            {
            printf("mul\n");
            bufout[j] = CMD_MULT;
            }
        else
        if (!strncmp((bufin + i), "mod", 3))
            {
            printf("mod\n");
            bufout[j] = CMD_MOD;
            }
        else
        if (!strncmp((bufin + i), "sub", 3))
            {
            printf("sub\n");
            bufout[j] = CMD_SUB;
            }
        else
        if (!strncmp((bufin + i), "scanf", 5))
            {
            printf("scanf\n");
            bufout[j] = CMD_SCANF;
            }
        else
        if (!strncmp((bufin + i), "div", 3))
            {
            printf("div\n");
            bufout[j] = CMD_DIV;
            }
        else 
        if (assemb_level == 1) 
            {
            printf("error\n");
            fprintf(log_file, "ERROR: incorrect command name, line %d\n", line_counter);
            return -1;
            }
        for (int e = 0; e < j; e++)
            printf("%d ", bufout[e]); 
        printf("\n");
        printf("bufin[%d] = %d = %c\n", i,  bufin[i], bufin[i]); 
        line_counter++;
        while (bufin[i] != '\n')
            i++;
        bufout[j + 1] = '\n';
        }
    return j;
    }


int main(int argc, char* argv[])
    {
    mark_t labels[labels_size];
    for (int z = 0; z < labels_size; z++)
        {
        labels[z].name = (char*) calloc (Label_name_size, sizeof(char));
        labels[z].pointer = -1;
        }
    int j = 0, test = 0;
    struct stat statistica;
    FILE* CMD_ENG     = fopen(argv[1], "r");
    FILE* CMD_MACHINE = fopen("Commands.txt", "w");
    FILE* log_file    = fopen("log.txt", "w");
    int stat_error = stat ("CMD_ENG.txt", &statistica);
    assert(stat_error == 0);
    char* bufin = (char*) calloc ((statistica.st_size + 1), sizeof(char));
    fread ((void*) bufin, sizeof(char), statistica.st_size, CMD_ENG);
    bufin[statistica.st_size] = '\n';
    char* bufout = (char*) calloc((statistica.st_size + 1), sizeof(char));
    assemb(labels, bufin, bufout, statistica.st_size, log_file, 0);
    j = assemb(labels, bufin, bufout, statistica.st_size, log_file, 1);
    fclose(log_file);
    FILE* logf = fopen("log.txt", "r");
    if (j < 0) 
        {
        stat_error = stat ("log.txt", &statistica);
        char* log = (char*) calloc ((statistica.st_size + 1), sizeof(char));
        fread ((void*) log, sizeof(char), statistica.st_size, logf);
        printf("%s", log);
        Finishing(CMD_MACHINE, CMD_ENG, logf, labels, bufout, bufin);
        return -1;
        }
    bufout[j + 1] = '\0';
    printf("assemb end\n");
    for (int k = 0; k <= j + 2; k++)    
        {
        fprintf(CMD_MACHINE, "%c", bufout[k]);
        printf("%d\n", bufout[k]);
        }
    Finishing(CMD_MACHINE, CMD_ENG, log_file, labels, bufout, bufin);
    return 0;
    }