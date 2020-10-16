#include <stdio.h>
#include <stdlib.h>

struct str{char* s; int l;};
int cmp2 (struct str text1, struct str text2);
int cmp1 (struct str text1, struct str text2);
void bubbleSort(struct str* text, int nstr, int (*cmp)(struct str, struct str) );
int filltext (FILE* fin, struct str* text, struct str* copyt);

/// \brief The fuction read text from file and fill array of struct
int filltext (FILE* fin, struct str* text, struct str* copyt)
    {
    const int mem = 250;
    int nrealoc = 1;
    int numb = 0;
    for(;;)
        {
        int krealoc = 1;
        int j = -1;
        text[numb].s = (char*) calloc (mem, sizeof (char));
        copyt[numb].s = (char*) calloc (mem, sizeof (char));
        for(;;)
            {
            j++;
            text[numb].s[j] = (char)fgetc(fin);
            copyt[numb].s[j] = text[numb].s[j];
            if ((krealoc * mem - j) == 2)
                {
                krealoc++;
                text[numb].s = (char*) realloc (text[numb].s, mem * krealoc * sizeof (char));
                copyt[numb].s = (char*) realloc (text[numb].s, mem * krealoc * sizeof (char));
                }
            if (((text[numb].s[j] == '\n') ||( text[numb].s[j] == EOF) || (text[numb].s[j] == '\0')) == 1)
                {
                if (text[numb].s[j] != EOF)
                    {
                    text[numb].s[j] = '\0';
                    copyt[numb].s[j] = '\0';
                    }
                text[numb].l = j;
                copyt[numb].l = j;
                break;
                }
            }
        if (text[numb].s[j] == EOF) break;
        numb++;
        if ((nrealoc * mem - numb) == 1 + 1)
                {
                nrealoc++;
                text = (struct str*) realloc (text, mem * nrealoc * sizeof (struct str));
                copyt = (struct str*) realloc (text, mem * nrealoc * sizeof (struct str));
                }
        }
    return numb;
    }

/// \brief Rhyme Comparator, it compare symbols of 2 strings from the end of strings
int cmp2 (struct str text1, struct str text2)
    {
    int i = 0;
    int j = 0;
    while ((i < text1.l) && (j < text2.l))
        {
        while (!(((text1.s[text1.l - i - 1] <= 'z') && (text1.s[text1.l - i - 1] >= 'a')) || ((text1.s[text1.l - i - 1] <= 'Z') && (text1.s[text1.l - i - 1] >= 'A'))))
            i++;
        while (!(((text2.s[text2.l - j - 1] <= 'z') && (text2.s[text2.l - j - 1] >= 'a')) || ((text2.s[text2.l - j - 1] <= 'Z') && (text2.s[text2.l - j - 1] >= 'A'))))
            j++;
        if (text1.s[text1.l - i - 1] < text2.s[text2.l - j - 1]) return 1;
        if (text1.s[text1.l - i - 1] > text2.s[text2.l - j - 1]) return 0;

        i++;
        j++;
        }
    return (text1.l < text2.l);
    }

/// \brief general comparator for strings
int cmp1 (struct str text1, struct str text2)
    {
    int i = 0;
    int j = 0;
    while ((i < text1.l) && (j < text2.l))
        {
        while (!(((text1.s[i] <= 'z') && (text1.s[i] >= 'a')) || ((text1.s[i] <= 'Z') && (text1.s[i] >= 'A'))))
            i++;
        while (!(((text2.s[j] <= 'z') && (text2.s[j] >= 'a')) || ((text2.s[j] <= 'Z') && (text2.s[j] >= 'A'))))
            j++;
        if (text1.s[i] < text2.s[j]) return 1;
        if (text1.s[i] > text2.s[j]) return 0;

        i++;
        j++;
        }
    return (text1.l < text2.l);
    }

/// \brief Function sorts array of structure, using different comparator
void bubbleSort(struct str* text, int nstr, int (*cmp)(struct str, struct str) )
    {
    struct str temp;
    int k = 0, m = 0;
    for (k = 0; k < nstr; k++)
        {
            for (m = nstr - 1; m > k; m--)
            {
            if (cmp(text[m], text[m - 1]))
                {
                temp = text[m];
                text[m] = text[m - 1];
                text[m - 1] = temp;
                }
            }
        }
    }
int main ()
    {
    FILE* fin = fopen("first.txt", "r");
    struct str* text = (struct str*) calloc (250, sizeof(struct str));
    struct str* copyt = (struct str*) calloc (250, sizeof(struct str));
    int numb = filltext (fin, text, copyt);
    fclose (fin);

    bubbleSort(text, numb, cmp1);
    FILE* fout = fopen("first.txt", "w");


    fprintf (fout, "\n Sorted text \n");
    for (int i = 0; i < numb; i++)
        fprintf (fout, "%s\n", text[i].s);


    fprintf (fout, "\n  Rhyme Sorted text \n");
    bubbleSort(text, numb, cmp2);
    for (int i = 0; i < numb; i++)
        fprintf (fout, "%s\n", text[i].s);


    fprintf (fout, "\n  Original text \n");
    for (int i = 0; i < numb; i++)
        fprintf (fout, "%s\n", copyt[i].s);

    fclose (fout);
    return 0;
    }

