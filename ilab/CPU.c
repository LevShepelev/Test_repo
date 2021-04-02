#include "proc.h"
char debug;

void push_handling(cpu_t* c1)
    {
    assert(c1 != NULL);
    c1 -> ID++;
    decryption_number_to_rdi(c1);
    stack_push(c1 -> stack, c1 -> reg[rdi]);
    }



void starting(cpu_t* c1, char* file_name)
    {
    assert(c1 != NULL);
    for (int s = 0; s < number_of_registers; s++)
        c1 -> reg[s] = 0;
    c1 -> RAM = (void*) mycalloc(RAM_size, sizeof(char));
    struct stat statistica;
    FILE* Commands = fopen(file_name, "r");
    int stat_error = stat (file_name, &statistica);
    assert(stat_error == 0);
    c1 -> buf_size = statistica.st_size;
    c1 -> buf = (char*) mycalloc ((c1 -> buf_size + 1), sizeof(char));
    stack_construct(c1 -> stack_pointer, 10);
    fread ((void*) c1 -> buf, sizeof(char), c1 -> buf_size, Commands);
    stack_construct(c1 -> stack, 10);
    fclose(Commands);
    }



void decryption_number_to_rdi(cpu_t* c1)
    {
    c1 -> reg[rdi] = *(double*)(c1 -> buf + c1 -> ID);
    c1 -> ID += data_size - 1;
    }



void jump_handling(cpu_t* c1)
    {
    assert(c1 != NULL);
    decryption_number_to_rdi(c1);
    c1 -> ID = (int) c1 -> reg[rdi] - 1;
    }



void execution(cpu_t* c1)
    {
    assert(c1 != NULL);
    for (c1 -> ID = 0; c1 -> ID < c1 -> buf_size; c1 -> ID++)
        {   
        //printf("buf = %d ID = %d\n", c1 -> buf[c1 -> ID], c1 -> ID);
        switch (c1 -> buf[c1 -> ID])
            {
            case CMD_EXIT:
                printf("finishing program");
                return;

            case CMD_PUSH:         
                push_handling(c1);
                break;

            case CMD_PUSH_R:
                c1 -> ID++;
                stack_push(c1 -> stack, c1 -> reg[c1 -> buf[c1 -> ID]]);
                break;
            
            case CMD_PUSH_RAM_REG:
                c1 -> ID++;
                stack_push(c1 -> stack, ((double*) c1 -> RAM)[(int) c1 -> reg[c1 -> buf[c1 -> ID]]]);
                break;
            
            case CMD_PUSH_RAM_NUM:
                c1 -> ID++;
                decryption_number_to_rdi(c1);
                stack_push(c1 -> stack, ((double*) c1 -> RAM)[(int) c1 -> reg[rdi]]);
                break;

            case CMD_POP_R:
                c1 -> ID++;
                c1 -> reg[c1 -> buf[c1 -> ID]] = stack_pop(c1 -> stack);
                break;
            
            case CMD_POP_RAM_REG:
                c1 -> ID++;
                ((double*) c1 -> RAM)[(int) c1 -> reg[c1 -> buf[c1 -> ID]]] = stack_pop(c1 -> stack);
                break;

            case CMD_POP_RAM_NUM:
                c1 -> ID++;
                decryption_number_to_rdi(c1);
                ((double*) c1 -> RAM)[(int) c1 -> reg[rdi]] = stack_pop(c1 -> stack);
                break;

            case CMD_ADD:
                stack_push(c1 -> stack, stack_pop(c1 -> stack) + stack_pop(c1 -> stack));
                break;

            case CMD_MUL:
                stack_push(c1 -> stack, stack_pop(c1 -> stack) * stack_pop(c1 -> stack));
                break;

            case CMD_SUB:
                stack_push(c1 -> stack, stack_pop(c1 -> stack) - stack_pop(c1 -> stack));
                break;

            case CMD_DIV:
                stack_push(c1 -> stack, (long long int) (stack_pop(c1 -> stack) / stack_pop(c1 -> stack)));
                break;

            case CMD_MOD:
                stack_push(c1 -> stack, (long long int) stack_pop(c1 -> stack) % (long long int)stack_pop(c1 -> stack));
                break;
            
            case CMD_divD:
                stack_push(c1 -> stack, stack_pop(c1 -> stack) / stack_pop(c1 -> stack));
                break;

            case CMD_SQRT:
                stack_push(c1 -> stack, sqrt(stack_pop(c1 -> stack)));
                break;

            case CMD_PRINTF:
                printf("%lf\n", stack_get(c1 -> stack));
                break;

            case CMD_SCANF:
                scanf("%lf", &(c1 -> reg[rdi]));
                stack_push(c1 -> stack, c1 -> reg[rdi]);
                break;

            case CMD_DEBUG:
                print_stack(c1 -> stack);
                print_stack(c1 -> stack_pointer);
                for (int i = 0; i < 10; i++)
                    printf("Ram = %lf\n", ((double*)c1 -> RAM)[i]);
                for (int i = 0; i < 6; i++)
                    printf("reg[%d] = %lf\n", i, c1 -> reg[i]);
                break;
            
            case CMD_CALL:
                c1 -> ID++;
                stack_push(c1 -> stack_pointer, (c1 -> ID) + data_size - 1);
                jump_handling(c1);
                break;

            case CMD_RET:
                c1 -> ID = (int) stack_pop(c1 -> stack_pointer);
                break;

            case CMD_JMP:
                c1 -> ID++;
                jump_handling(c1);
                break;

            case CMD_JMPB:
                c1 -> ID++; 
                if (stack_pop(c1 -> stack) < c1 -> reg[rsi])
                    jump_handling(c1);
                else
                    c1 -> ID += data_size - 1;
                break;

            case CMD_JMPA:
                c1 -> ID++; 
                if (stack_pop(c1 -> stack) > c1 -> reg[rsi])
                    jump_handling(c1);
                else
                    c1 -> ID += data_size - 1;
                break;

            case CMD_JMPE:
                c1 -> ID++; 
                if (stack_pop(c1 -> stack) == c1 -> reg[rsi])
                    jump_handling(c1);
                else
                    c1 -> ID += data_size - 1;
                break;

            case CMD_JBE:
                c1 -> ID++; 
                if (stack_pop(c1 -> stack) <= c1 -> reg[rsi])
                    jump_handling(c1);
                else
                    c1 -> ID += data_size - 1;
                break;

            case CMD_JAE:
                c1 -> ID++; 
                if (stack_pop(c1 -> stack) >= c1 -> reg[rsi])
                    jump_handling(c1);
                else
                    c1 -> ID += data_size - 1;
                break;

            case CMD_JNE:
                c1 -> ID++; 
                if (stack_pop(c1 -> stack) != c1 -> reg[rsi])
                    jump_handling(c1);
                else
                    c1 -> ID += data_size - 1;
                break;

            default:
                scanf("%c", &debug);
                printf("CPU ERROR\n");
            }
        }
    }



int main(int argc, char* argv[])
    {
    mystack st1, st2;
    cpu_t c1;
    c1.stack = &st1;
    c1.stack_pointer = &st2;
    starting(&c1, argv[1]);
    execution(&c1);
    free(c1.buf);
    stack_destruct(c1.stack);
    stack_destruct(c1.stack_pointer);
    }