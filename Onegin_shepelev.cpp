#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <io.h>
#include <stdlib.h>
void exchange(char* text, int x, int y, int nstr);
int strcmp(char* s1, int y, int x);
void bubbleSort(char* text, int nstrok);
void exchange(char* text, int x, int y, int nstr)  // ������� ���������� �������
    {
    char chng;
    for (int i = 0; i < nstr; i++)
        {
        chng = text[256*x + i];
        text[256*x + i] = text[256*y + i];
        text[256*y + i] = chng;
        }
    }
int strcmp(char* s1, int y, int x)    // ������� ���������� �������
    {
    int i = 0;
    for (i = 0; ((s1[256*y + i] != '\n') && (s1[256*y + i] != '\0')); i++)
        {
        if (((s1[256*y + i] < 91) && (s1[256*y + i] > 64)) || ((s1[256*y + i] < 123) && (s1[256*y + i] > 96)))
            {
            if (s1[256*y + i] < s1[256*x + i])
                {
                return 1;
                }
            if (s1[256*y + i] > s1[256*x + i])
                {
                return 0;
                }
            if ((s1[256*x + i] == '\n') || (s1[256*x + i] == '\0'))
                {
                return 0;
                }
            }
        return 0;
        }
        if ((s1[256*x + i] == '\n') || (s1[256*x + i] == '\0'))
        {
        return 0;
        }
    return 0;
    }
void bubbleSort(char* text, int nstr)   // ������� ��������� ������ �� �������
    {
        int k, m;
        for (k = 0; k < nstr; k++)
        {
            for (m = nstr - 1; m > k; m--)
            {
            if (strcmp(text, m, m - 1))
                {
                exchange(text, m, m - 1, nstr);
                }
            }
        }
    }
int main()
    {
    char musor[255];
    int i, j, nstr = 0;
    FILE* fin = fopen("first.txt", "r");
    while (fgets (musor, 255, fin) != NULL)
        {
        nstr++;
        }
    printf ("%d\n", nstr);

    char* text = (char*)calloc (256*nstr + 10000, sizeof(char));
    fclose (fin);
    fin = fopen ("first.txt", "r");

    for (i = 0; !feof(fin); i++)
        {
        fscanf(fin, "%c", &(text[256*i]));
        for (j = 1; (text[256*i + j - 1] != ('\n')) && (!feof(fin)); j++)
            {
            fscanf(fin, "%c", &(text[256*i + j]));
            }
        text[256*i + j] = '\0';
        }



    fclose(fin);

    bubbleSort (text, nstr);

    FILE* fout = fopen("second.txt", "w"); //�������� fin ���� ��� ������ ��� �� �������

    for (i = 0; i < nstr; i++)
    {
        for (j = 0; j < 255 && text[256*i + j] != 0; j++)
        {
            fprintf(fout, "%c", text[256*i + j]);
        }
        if (j != 0 && text[256*i + j - 1] != '\n')
            fprintf(fout, "\n");
    }

    fclose(fout);
    printf("Executed\n"); //����� ��� ��������� �����������
    return 0;
    }
