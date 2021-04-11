#include "CPU++.h"


void CPU::push_handling()
    {
    assert(this != NULL);
    ID++;
    decryption_number_to_rdi();
    stack -> push(reg[rdi]);
    }



CPU::CPU(char* Commands_file_name)
    {
    assert(this != NULL);
    for (int s = 0; s < number_of_registers; s++)
        reg[s] = 0;
    stack = new Stack(10);
    stack_pointer = new Stack(10);
    RAM = (void*) mycalloc(RAM_size, sizeof(char));
    struct stat statistica;
    FILE* Commands = fopen(Commands_file_name, "r");
    int stat_error = stat (Commands_file_name, &statistica);
    assert(stat_error == 0);
    buf_size = statistica.st_size;
    buf = (char*) mycalloc ((buf_size + 1), sizeof(char));
    fread ((void*) buf, sizeof(char), buf_size, Commands);
    fclose(Commands);
    }


CPU::~CPU()
    {
    free(buf);
    delete stack;
    delete stack_pointer;
    }



void CPU::decryption_number_to_rdi()
    {
    reg[rdi] = *(double*)(buf + ID);
    ID += data_size - 1;
    }



void CPU::jump_handling()
    {
    assert(this != NULL);
    decryption_number_to_rdi();
    ID = (int) reg[rdi] - 1;
    }



void CPU::execution()
    {
    assert(this != NULL);
    for (ID = 0; ID < buf_size; ID++)
        {   
        //printf("buf = %d ID = %d\n", buf[ID], ID);
        switch (buf[ID])
            {
            case CMD_EXIT:
                printf("finishing program");
                return;

            case CMD_PUSH:         
                push_handling();
                break;

            case CMD_PUSH_R:
                ID++;
                stack -> push(reg[buf[ID]]);
                break;
            
            case CMD_PUSH_RAM_REG:
                ID++;
                stack -> push(((double*) RAM)[(int) reg[buf[ID]]]);
                break;
            
            case CMD_PUSH_RAM_NUM:
                ID++;
                decryption_number_to_rdi();
                stack -> push(((double*) RAM)[(int) reg[rdi]]);
                break;

            case CMD_POP_R:
                ID++;
                reg[buf[ID]] = stack -> pop();
                break;
            
            case CMD_POP_RAM_REG:
                ID++;
                ((double*) RAM)[(int) reg[buf[ID]]] = stack -> pop();
                break;

            case CMD_POP_RAM_NUM:
                ID++;
                decryption_number_to_rdi();
                ((double*) RAM)[(int) reg[rdi]] = stack -> pop();
                break;

            case CMD_ADD:
                stack -> push(stack -> pop() + stack -> pop());
                break;

            case CMD_MUL:
                stack -> push(stack -> pop() * stack -> pop());
                break;

            case CMD_SUB:
                stack -> push(stack -> pop() - stack -> pop());
                break;

            case CMD_DIV:
                stack -> push((long long int) (stack -> pop() / stack -> pop()));
                break;

            case CMD_MOD:
                stack -> push((long long int) stack -> pop() % (long long int)stack -> pop());
                break;
            
            case CMD_divD:
                stack -> push(stack -> pop() / stack -> pop());
                break;

            case CMD_SQRT:
                stack -> push(sqrt(stack -> pop()));
                break;

            case CMD_PRINTF:
                printf("%lf\n", stack -> get());
                break;

            case CMD_SCANF:
                scanf("%lf", &(reg[rdi]));
                stack -> push(reg[rdi]);
                break;

            case CMD_DEBUG:
                stack -> Dump();
                stack_pointer -> Dump();
                for (int i = 0; i < 10; i++)
                    printf("Ram = %lf\n", ((double*)RAM)[i]);
                for (int i = 0; i < 6; i++)
                    printf("reg[%d] = %lf\n", i, reg[i]);
                break;
            
            case CMD_CALL:
                ID++;
                stack_pointer -> push((ID) + data_size - 1);
                jump_handling();
                break;

            case CMD_RET:
                ID = (int) stack_pointer -> pop();
                break;

            case CMD_JMP:
                ID++;
                jump_handling();
                break;

            case CMD_JMPB:
                ID++; 
                if (stack -> pop() < reg[rsi])
                    jump_handling();
                else
                    ID += data_size - 1;
                break;

            case CMD_JMPA:
                ID++; 
                if (stack -> pop() > reg[rsi])
                    jump_handling();
                else
                    ID += data_size - 1;
                break;

            case CMD_JMPE:
                ID++; 
                if (stack -> pop() == reg[rsi])
                    jump_handling();
                else
                    ID += data_size - 1;
                break;

            case CMD_JBE:
                ID++; 
                if (stack -> pop() <= reg[rsi])
                    jump_handling();
                else
                    ID += data_size - 1;
                break;

            case CMD_JAE:
                ID++; 
                if (stack -> pop() >= reg[rsi])
                    jump_handling();
                else
                    ID += data_size - 1;
                break;

            case CMD_JNE:
                ID++; 
                if (stack -> pop() != reg[rsi])
                    jump_handling();
                else
                    ID += data_size - 1;
                break;

            default:
                //scanf("%c");
                printf("CPU ERROR\n");
            }
        }
    }



int main(int argc, char* argv[])
    {
    CPU c1(argv[1]);
    c1.execution();
    }