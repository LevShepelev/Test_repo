#include <stdio.h>
#include <sys/stat.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
const int Label_name_size = 20;
const int labels_size = 16;
const int max_pointer = 8;
const int log_size = 2000;
typedef struct mark {int pointer; char* name;} mark_t;
int assemb(mark_t* labels, const char* bufin, char* bufout, int stat, FILE* log_file, int assemb_level);
void Finishing(FILE* CMD_MACHINE, FILE* CMD_ENG, FILE* log_file, mark_t* labels, char* bufout, char* bufin);
int Jumping(const char* bufin, char* bufout, mark_t* labels, FILE* log_file, int jump_type, int* i, int* j, int line_counter, int assemb_level)
;
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
    CMD_JNE    = 19
    };