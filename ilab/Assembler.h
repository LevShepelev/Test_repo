#include <stdio.h>
#include <sys/stat.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

const int Label_name_size = 20;
const int labels_size = 16;
const int max_pointer = 8;
const int log_size = 2000;
const int max_lexemm_length = 100;
const int data_size = 4;
typedef struct mark {int pointer; char* name;} mark_t;

void* my_calloc (FILE* log_file, int size_of_elem,  int size);
int Start (char* Input_file_name, FILE* CMD_ENG, char* Input_buf, char* Output_buf, FILE* log_file);

enum Commands
    {
    CMD_PUSH   = 1,
    CMD_ADD    = 2,
    CMD_MULT   = 3,
    CMD_SUB    = 4,
    CMD_DIV    = 5,
    CMD_MOD    = 6,
    CMD_PRINTF = 7,
    CMD_SCANF  = 8,
    CMD_PUSH_R = 9,
    CMD_EXIT   = 11,
    CMD_POP_R  = 12,
    CMD_JMP    = 13,
    CMD_JMPB   = 14,
    CMD_JMPA   = 15,
    CMD_JMPE   = 16,
    CMD_JBE    = 17,
    CMD_JAE    = 18,
    CMD_JNE    = 19,
    CMD_RAX    = 20,
    CMD_RBX    = 21,
    CMD_RCX    = 22,
    CMD_RDX    = 23

    };