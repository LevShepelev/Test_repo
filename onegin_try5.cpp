#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>

struct str{char* s; int l;};

int linecount(const char* buf, const int value);
void filltext(char* buf, struct str* text, const int numb);
int cmp1 (const void* qtext1, const void* qtext2);
int cmp2 (const void* qtext1, const void* qtext2);
void textprintf(struct str* text, int numb, FILE* fout);
void length_of_strings(const char* buf, struct str* text, const int numb, int value);
char* starting(int* numb, struct str** text);
void* my_calloc (int size_of_elem, int size);
void writing_to_file(char* buf, struct str* text, int numb);
void finishing(char* buf, struct str* text);


/// \brief general comparator for strings
int cmp1 (const void* qtext1, const void* qtext2)
    {
    struct str text1 = *((struct str*)qtext1);
    struct str text2 = *((struct str*)qtext2);
    int i = 0;
    int j = 0;
    while ((i < text1.l) && (j < text2.l))
        {
        while (!(((text1.s[i] <= 'z') && (text1.s[i] >= 'a')) || ((text1.s[i] <= 'Z') && (text1.s[i] >= 'A'))) && (i < text1.l) && (j < text2.l))
            i++;
        while (!(((text2.s[j] <= 'z') && (text2.s[j] >= 'a')) || ((text2.s[j] <= 'Z') && (text2.s[j] >= 'A'))) && (i < text1.l) && (j < text2.l))
            j++;
        if (text1.s[i] < text2.s[j]) return -1;
        if (text1.s[i] > text2.s[j]) return 1;

        i++;
        j++;
        }
    if (text1.l < text2.l) return -1;
    if (text1.l > text2.l) return 1;
    if (text1.l == text2.l) return 0;
    }



/// \brief Rhyme Comparator, it compare symbols of 2 strings from the end of strings
int cmp2 (const void* qtext1, const void* qtext2)
    {
    struct str text1 = *((struct str*)qtext1);
    struct str text2 = *((struct str*)qtext2);
    int i = 0;
    int j = 0;
    while ((i < text1.l) && (j < text2.l))
        {
        while (!(((text1.s[text1.l - i - 1] <= 'z') && (text1.s[text1.l - i - 1] >= 'a')) || ((text1.s[text1.l - i - 1] <= 'Z') && (text1.s[text1.l - i - 1] >= 'A'))) && (i < text1.l - 1) && (j < text2.l - 1))
            i++;
        while (!(((text2.s[text2.l - j - 1] <= 'z') && (text2.s[text2.l - j - 1] >= 'a')) || ((text2.s[text2.l - j - 1] <= 'Z') && (text2.s[text2.l - j - 1] >= 'A'))) && (i < text1.l - 1) && (j < text2.l - 1))
            j++;
        if (text1.s[text1.l - i - 1] < text2.s[text2.l - j - 1]) return -1;
        if (text1.s[text1.l - i - 1] > text2.s[text2.l - j - 1]) return 1;

        i++;
        j++;
        }
    if (text1.l < text2.l) return -1;
    if (text1.l > text2.l) return 1;
    if (text1.l == text2.l) return 0;
    }



/// \brief The function prints text to file
void textprintf(struct str* text, int numb, FILE* fout)
    {
    int n_empty = 0;
    for (n_empty = 0; (text[n_empty].s[0] == '\n'); n_empty++);
    for (int i = n_empty; i < numb; i++)
        for (int j = 0; j <= text[i].l; j++)
            fprintf(fout, "%c", *(text[i].s + j));
    }



/// \brief The function count number of lines in the text
int linecount(const char* buf, const int value)
    {
    int linecounter = 0;

    for (int i = 0; i <= value; i++)  // считаем сколько строк
        if (buf[i] == '\n')
            linecounter++;
    return linecounter + 1;
    }



/// \brief The function fill array of struct from bufer
void filltext(char* buf, struct str* text, const int numb)
    {
    int j = 0;
    int i = 0;

    for (i = 0; i < numb; i++)
        {
        text[i].s = buf + j;
        j += text[i].l + 1;
        }
    }



/// \brief The function count length of each string in text
void length_of_strings(const char* buf, struct str* text, const int numb, int value)
    {
    for (int i = 0; i < numb; i++)
        for (int j = 0; j < value; j++)
            if ((buf[j] == '\n') || (buf[j] == '\0'))
                {
                text[i].l = j;
                buf += j + 1;
                break;
                }
    }



/// \brief The function open file and fill the bufer
char* starting(int* numb, struct str** text)
    {
    printf("Welcome to text sorting machine...\n");
    FILE* fin = fopen("Onegin_input.txt", "r");
    struct stat statistica;
    int stat_error = stat ("Onegin_input.txt", &statistica);
    assert(stat_error == 0);

    char* buf = (char*) my_calloc (statistica.st_size + 1, sizeof(char));

    fread ((void*) buf, sizeof(char), statistica.st_size, fin);  // recording text in bufer

    *numb = linecount(buf, statistica.st_size); //finding the number of strings in the text

    (*text) = (struct str*) my_calloc (*numb, sizeof(struct str));
    length_of_strings(buf, *text, *numb, statistica.st_size);

    fclose (fin);

    return buf;
    }



/// \brief The function allocate memory carefully
void* my_calloc (int size_of_elem, int size)
    {
    char* mem = (char*) calloc (size, size_of_elem);
    if (mem == NULL) 
        {
        printf("Calloc error\n");
        exit (1);
        }
    return mem;
    }



/// \brief The function write sort version to file
void writing_to_file(char* buf, struct str* text, int numb)
    {
    assert(text);
    assert(buf);

    FILE* fout = fopen("Onegin_output.txt", "w");

    qsort((void*)text, numb, sizeof(struct str), cmp1); // Sorting the text using the general comparator and printing the text

    fprintf(fout, "SORTED TEXT\n");
    textprintf(text, numb, fout);

    qsort((void*)text, numb, sizeof(struct str), cmp2);// Sorting the text using the rhyme comparator and printing the text

    fprintf(fout, "\nRHYME SORTED TEXT\n");
    textprintf(text, numb, fout);

    fprintf(fout, "\nOriginal Text\n%s", buf);
    fclose(fout);
    }



/// \brief The function free memory
void finishing(char* buf, struct str* text)
    {
    printf("Well done !\n");
    free(buf);
    free(text);
    }



int main()
    {
    struct str* text = NULL;
    int numb = 0;
    char* buf = starting(&numb, &text);

    filltext(buf, text, numb);
    writing_to_file(buf, text, numb);
    finishing(buf, text);
    }
