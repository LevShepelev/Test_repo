#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct str{char* s; int l;};
int cmp2 (struct str text1, struct str text2);
int cmp1 (struct str text1, struct str text2);
void bubbleSort(struct str* text, int nstr, int (*cmp)(struct str, struct str) );
int filltext (FILE* fin, struct str** text, struct str** copyt);

/// \brief The fuction read text from file and fill array of struct
int filltext (FILE* fin, struct str** text)
    {
    const int mems = 50;
    const int mem = 250;
    int nrealoc = 1;
    int numb = 0;
    for(;;)
        {
        int krealoc = 1;
        int j = -1;
        (*text)[numb].s = (char*) calloc (mem, sizeof (char));
        for(;;)
            {
            j++;
            (*text)[numb].s[j] = (char)fgetc(fin);
            if ((krealoc * mems - j) <= 1 + 1)
                {
                krealoc++;
                (*text)[numb].s  = (char*) realloc ((*text)[numb].s, mems * krealoc * sizeof (char));
                }
            if ((((*text)[numb].s[j] == '\n') ||( (*text)[numb].s[j] == EOF) || ((*text)[numb].s[j] == '\0')) == 1)
                {
                if ((*text)[numb].s[j] != EOF)
                    (*text)[numb].s[j] = '\0';
                (*text)[numb].l = j;
                break;
                }
            }
        if ((*text)[numb].s[j] == EOF)
        {
        (*text)[numb].s[j] = '\0';
        break;
        }
        numb++;

        if ((nrealoc * mem - numb) <= 1)
                {
                nrealoc++;
                (*text) = (struct str*) realloc ((*text), mem * nrealoc * sizeof (struct str));
                printf ("Realocation %d\n", nrealoc);
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
        while (!(((text1.s[text1.l - i - 1] <= 'z') && (text1.s[text1.l - i - 1] >= 'a')) || ((text1.s[text1.l - i - 1] <= 'Z') && (text1.s[text1.l - i - 1] >= 'A'))) && (i < text1.l - 1) && (j < text2.l - 1))
            i++;
        while (!(((text2.s[text2.l - j - 1] <= 'z') && (text2.s[text2.l - j - 1] >= 'a')) || ((text2.s[text2.l - j - 1] <= 'Z') && (text2.s[text2.l - j - 1] >= 'A'))) && (i < text1.l - 1) && (j < text2.l - 1))
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
        while (!(((text1.s[i] <= 'z') && (text1.s[i] >= 'a')) || ((text1.s[i] <= 'Z') && (text1.s[i] >= 'A'))) && (i < text1.l) && (j < text2.l))
            i++;
        while (!(((text2.s[j] <= 'z') && (text2.s[j] >= 'a')) || ((text2.s[j] <= 'Z') && (text2.s[j] >= 'A'))) && (i < text1.l) && (j < text2.l))
            j++;
        if (text1.s[i] < text2.s[j]) return 1;
        if (text1.s[i] > text2.s[j]) return 0;

        i++;
        j++;
        }
    return (text1.l < text2.l);
    }

/// \brief Function sorts array of structure quickly, using different comparator

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
                assert((m <= nstr) && (m > 0));
                temp = text[m];
                text[m] = text[m - 1];
                text[m - 1] = temp;

                }
            }
        }
    }
int main ()
    {
    int n_empty = 0;
    FILE* fin = fopen("Onegin_input.txt", "r");
    struct str* text = (struct str*) calloc (250, sizeof(struct str));
    int numb = filltext (fin, &text);
    char** copyt = (char**) calloc (numb + 1, sizeof(char*));
    for (int i = 0; i <= numb; i++)
        copyt[i] = text[i].s;
    printf("numb = %d\n", numb);
    fclose (fin);
    
    for (int i = 0; i <= numb; i++)  //Createion copy of text
        printf ( "%s\n", copyt[i]); 

    bubbleSort(text, numb, cmp1);
    
    for (n_empty = 0; (text[n_empty].s[0] == '\0'); n_empty++);

    FILE* fout = fopen("Onegin_output.txt", "w");

    fprintf (fout, "Sorted text \n");
    for (int i = n_empty; i <= numb; i++)
        fprintf (fout, "%s\n", text[i].s);


    fprintf (fout, "\nRhyme Sorted text\n");
    bubbleSort(text, numb, cmp2);
   
    for (int i = n_empty; i <= numb; i++)
        fprintf (fout, "%s\n", text[i].s);


    fprintf (fout, "\nOriginal text\n");
    for (int i = 0; i <= numb; i++)
        fprintf (fout, "%s\n", copyt[i]);

    fclose (fout);

    for (int i = 0; i <= numb; i++)
        free (text[i].s);
    free (text);
    free (copyt);
    return 0;
    }

