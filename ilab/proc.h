#include <sys/stat.h>
#include <string.h>
#include "stack.h"
typedef struct cpu {char* buf; int ID; int reg[16]; mystack stack;} cpu_t;

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