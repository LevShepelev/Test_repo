#include "my_assemb.h"

void Finishing(FILE* CMD_MACHINE, FILE* CMD_ENG, FILE* log_file, mark_t* labels, char* bufout, char* bufin, int labels_size)
    {
    for (int z = 0; z < labels_size; z++)
        free(labels[z].name); 
    fclose(log_file);
    free(bufout);
    free(bufin);
    fclose(CMD_MACHINE);
    fclose(CMD_ENG);
    }

int assemb(mark_t* labels, const char* bufin, char* bufout, int stat, FILE* log_file, int assemb_level)
    {
    int i = 0, j = 0, mark_index = 0, line_counter = 1;
    for (int i = 0; i < stat - 1; i++, j += 2)
        {
        if (!strncmp((bufin + i), "pop r", 5))
            {
            bufout[j] = 12;
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
        if (!strncmp((bufin + i), "printf", 6))
            {
            bufout[j] = 7;
            }
        else
        if (!strncmp((bufin + i), "push r", 6))
            {
            bufout[j] = 9;
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
            bufout[j] = 1;
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
        if (!strncmp((bufin + i), "jmp", 3))
            {
            int k = 0, length = 0;
            i += 4;
            while (bufin[i + length] != ':')
                {
                if (bufin[i] == '\n')
                    {
                    if (assemb_level == 1) fprintf(log_file, "ERROR: incorrect format of function \"jump\", line %d\nexample: jmp HELL:\n", line_counter);
                    break;
                    return -1;
                    }
                length++;
                }
            for (k = 0; (strncmp((bufin + i), labels[k].name, length) != 0); k++)
                if (k == labels_size - 1) break;
            if (k < labels_size)
                {
                char p[max_pointer];
                bufout[j] = 13;
                j++;
                int t = j;
                sprintf(p, "%d", labels[k].pointer);
                while (p[j - t] != 0)
                    {
                    bufout[j] = p[j - t];
                    j++;
                    }
                j--;
                }
            else 
            if (assemb_level == 1) 
                {fprintf(log_file, "ERROR: Label has not been foundm line %d\n", line_counter);
                return -1;
                }
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
            bufout[j] = 11;
            }
        else
        if (!strncmp((bufin + i), "add", 3))
            {
            bufout[j] = 2;
            }
        else
        if (!strncmp((bufin + i), "mult", 4))
            {
            bufout[j] = 3;
            }
        else
        if (!strncmp((bufin + i), "mod", 3))
            {
            bufout[j] = 6;
            }
        else
        if (!strncmp((bufin + i), "sub", 3))
            {
            bufout[j] = 4;
            }
        else
        if (!strncmp((bufin + i), "scanf", 5))
            {
            bufout[j] = 8;
            }
        else
        if (!strncmp((bufin + i), "div", 3))
            {
            bufout[j] = 5;
            }
        else 
            {
            if (assemb_level == 1) fprintf(log_file, "ERROR: incorrect command name, line %dy\n", line_counter);
            return -1;
            }
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
        labels[z].name = (char*) calloc (labels_size, sizeof(char));
        labels[z].pointer = -1;
        }
    const int log_size = 2000;
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
        Finishing(CMD_MACHINE, CMD_ENG, logf, labels, bufout,bufin, labels_size);
        return -1;
        }
    bufout[j + 1] = '\0';
    for (int k = 0; k <= j + 2; k++)    
        {
        fprintf(CMD_MACHINE, "%c", bufout[k]);
        //printf("%d\n", bufout[k]);
        }
    Finishing(CMD_MACHINE, CMD_ENG, log_file, labels, bufout, bufin, labels_size);
    return 0;
    }