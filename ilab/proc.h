#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "stack.h"
//#include "stack_pointer.h"


typedef struct cpu {char* buf; int buf_size; int ID; long long int reg[16]; mystack* stack; mystack* stack_pointer;} cpu_t;
const int data_size = 4;
const int byte_size = 8;
void starting(cpu_t* c1, char* file_name);
void execution(cpu_t* c1);
void jump_handling(cpu_t* c1);


enum Commands
    {
    CMD_PUSH   = 1,
    CMD_ADD    = 2,
    CMD_MUL    = 3,
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
    CMD_CALL   = 20,
    CMD_RET    = 21,
    CMD_DEBUG  = 22,
    rax        = 0,
    rbx        = 1,
    rcx        = 2,
    rdx        = 3,
    rsi        = 4,
    rdi        = 5
    };