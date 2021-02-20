#include <stdio.h>
#include <sys/stat.h>
#include <assert.h>
#include <stdlib.h>
int main(int argc, char* argv[])
    {
    int i = 0, j = 0;//почитать про аргументы коммандной строки main  даем мейну название файла с кодом на английском
    struct stat statistica;
    FILE* CMD_ENG     = fopen(argv[1], "r");
    FILE* CMD_MACHINE = fopen("Commands.txt", "w");
    int stat_error = stat ("CMD_ENG.txt", &statistica);
    assert(stat_error == 0);
    char* bufin = (char*) calloc ((statistica.st_size + 1), sizeof(char));
    fread ((void*) bufin, sizeof(char), statistica.st_size, CMD_ENG);
    bufin[statistica.st_size] = '\n';
    char* bufout = (char*) calloc((statistica.st_size + 1), sizeof(char));
    for (int i = 0; i < statistica.st_size - 1; i++, j += 2)
        {
        switch (bufin[i])
            {
            case 'p':
                if (bufin[i + 1] == 'o')
                    bufout[j] = 10;

                if (bufin[i + 1] == 'r')
                    bufout[j] = 7;

                if (bufin[i + 1] == 'u')
                   {
                   if  (bufin[i + 5] == 'r')
                        {
                        bufout[j] = 9;
                        bufout[j + 1] = bufin[i + 6] - '0';
                        j += 2;
                        i += 8;
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
                   }
                break;

            case 'e':
                bufout[j] = 11;
                break;

            case 'a':
                bufout[j] = 2;
                break;


            case 'm':
                if (bufin[i + 1] == 'u')
                      bufout[j] = 3;
                if (bufin[i + 1] == 'o')
                      bufout[j] = 6;
                break;

            case 's':
                if (bufin[i + 1] == 'u')
                    bufout[j] = 4;
                if (bufin[i + 1] == 'c')
                    bufout[j] = 8;
                break;

            case 'd':
                bufout[j] = 5;
                break;
            default: 
                bufout[j] = 'X';
                break;
            }
        while (bufin[i] != '\n')
            i++;
        bufout[j + 1] = '\n';
        }
    bufout = (char*) realloc(bufout, (j + 2) * sizeof(char));
    bufout[j + 1] = '\0';
    for (int k = 0; k <= j + 2; k++)
        fprintf(CMD_MACHINE, "%c", bufout[k]);
    fclose(CMD_MACHINE);
    fclose(CMD_ENG);
    }