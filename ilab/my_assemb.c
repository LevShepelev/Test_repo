#include "my_assemb.h"



int assemb(mark_t* labels, const char* bufin, char* bufout, int stat)
    {
    int i = 0, j = 0, mark_index = 0, d;
    for (int i = 0; i < stat - 1; i++, j += 2)
        {
        if (!strncmp((bufin + i), "pop r", 5))
            {
            bufout[j] = 12;
            bufout[j + 1] = bufin[i + 5] - '0';
            bufout[j + 2] = bufin[i + 6] - '0';
            j += 2;
            i += 6;
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
            bufout[j + 1] = bufin[i + 6] - '0';
            bufout[j + 2] = bufin[i + 7] - '0';
            j += 2;
            i += 7;
            }
        else
        if (!strncmp((bufin + i), "push", 4))
            {
            bufout[j] = 1;
            j++;
            i += 5;
            while (bufin[i] != '\n')
                {
                bufout[j] = bufin[i];
                i++;
                j++;
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
                length++;
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
            } 
        else
        if ((bufin[i] > 'A') && (bufin[i] < 'Z')) // заполнение массива меток (указатели)
            {
            int length = 0, ind = 0, k = 0, z = 0;
            while (bufin[i + length] != ':')
                length++;
            for (k = 0; (strncmp(bufin + i, labels[k].name, length) != 0); k++)
                if (k == labels_size - 1) break;
            if (k >= labels_size - 1) // Новая Метка
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
    int j = 0, d = 0;
    struct stat statistica;
    FILE* CMD_ENG     = fopen(argv[1], "r");
    FILE* CMD_MACHINE = fopen("Commands.txt", "w");
    int stat_error = stat ("CMD_ENG.txt", &statistica);
    assert(stat_error == 0);
    char* bufin = (char*) calloc ((statistica.st_size + 1), sizeof(char));
    fread ((void*) bufin, sizeof(char), statistica.st_size, CMD_ENG);
    bufin[statistica.st_size] = '\n';
    char* bufout = (char*) calloc((statistica.st_size + 1), sizeof(char));
    assemb(labels, bufin, bufout, statistica.st_size);
    j = assemb(labels, bufin, bufout, statistica.st_size);
    bufout[j + 1] = '\0';
    for (int k = 0; k <= j + 2; k++)    
        {
        fprintf(CMD_MACHINE, "%c", bufout[k]);
        printf("%d\n", bufout[k]);
        }

    for (int z = 0; z < labels_size; z++)
        free(labels[z].name); 
    free(bufout);
    free(bufin);
    fclose(CMD_MACHINE);
    fclose(CMD_ENG);
    }