#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "stackCpp.h"
#include <math.h>
#define number_of_registers 16
class CPU
        {
        char* buf; 
        int buf_size; 
        int ID; 
        double reg[number_of_registers]; 
        Stack* stack; 
        Stack* stack_pointer; 
        void* RAM;
        public:
        CPU(char* Commands_file_name);
        ~CPU();
        void execution();
        void decryption_number_to_rdi();
        void jump_handling();
        void push_handling();
        };
const int data_size = 8;
const int byte_size = 8;
const unsigned RAM_size = 0x100000; //1 Мб

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
    CMD_divD   = 27,
    CMD_SQRT   = 28,

    CMD_PUSH_RAM_REG = 23,
    CMD_POP_RAM_REG  = 24,
    CMD_PUSH_RAM_NUM = 25,
    CMD_POP_RAM_NUM  = 26,

    rax          = 0,
    rbx          = 1,
    rcx          = 2,
    rdx          = 3,
    rsi          = 4,
    rdi          = 5
    };