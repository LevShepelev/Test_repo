#include "proc.h"

int main(int argc, char* argv[])
    {
    cpu_t c1;
    for (int s = 0; s < 16; s++)
        c1.reg[s] = 0;
    int stack_scanf = 0,  u;
    int j = 0, i = 2;
    struct stat statistica;//массив регистров
    FILE* Commands = fopen(argv[1], "r");
    int stat_error = stat (argv[1], &statistica);
    assert(stat_error == 0);

    c1.buf = (char*) calloc ((statistica.st_size + 1), sizeof(char));
    stack_construct(&c1.stack, 10);

    fread ((void*) c1.buf, sizeof(char), statistica.st_size, Commands);
    fclose(Commands);

    for (c1.ID = 0; c1.ID < statistica.st_size; c1.ID += 2)
        {   
        switch (c1.buf[c1.ID])
            {
            case CMD_EXIT:
                printf("finishing program");
                return 0;
            case CMD_PUSH:               
                c1.ID++;
                stack_push(&c1.stack, atoi(c1.buf + c1.ID));//strtod возвращает код ошибки
                while (c1.buf[c1.ID] != '\n')
                    c1.ID++;
                c1.ID--;
                break;
            case CMD_PUSH_R:
                stack_push(&c1.stack, c1.reg[c1.buf[c1.ID + 1] * 10 + c1.buf[c1.ID + 2]]);
                c1.ID += 2;
                break;

            case CMD_POP_R:
                c1.reg[c1.buf[c1.ID + 1] * 10 + c1.buf[c1.ID + 2]] = stack_pop(&c1.stack);
                c1.ID += 2;
                break;

            case CMD_ADD:
                stack_push(&c1.stack, stack_pop(&c1.stack) + stack_pop(&c1.stack));
                break;
            case CMD_MULT:
                stack_push(&c1.stack, stack_pop(&c1.stack) * stack_pop(&c1.stack));
                break;
            case CMD_SUB:
                stack_push(&c1.stack, stack_pop(&c1.stack) - stack_pop(&c1.stack));
                break;
            case CMD_DIV:
                stack_push(&c1.stack, stack_pop(&c1.stack) / stack_pop(&c1.stack));
                break;
            case CMD_MOD:
                stack_push(&c1.stack, stack_pop(&c1.stack) % stack_pop(&c1.stack));
                break;
            case CMD_PRINTF:
                printf("%d\n", stack_get(&c1.stack));
                break;
            case CMD_SCANF:
                scanf("%d", &stack_scanf);
                stack_push(&c1.stack, stack_scanf);
                break;
            case CMD_JMP:
                c1.ID++;
                c1.ID = atoi(c1.buf + c1.ID) - 2;
                break;
            case CMD_JMPB:
                c1.ID++; 
                if (stack_pop(&c1.stack) < c1.reg[15])
                    c1.ID = atoi(c1.buf + c1.ID) - 2;
                else
                    {
                    while (c1.buf[c1.ID] != '\n')
                        c1.ID++;
                    c1.ID--;
                    }
                break;
            case CMD_JMPA:
                c1.ID++; 
                if (stack_pop(&c1.stack) > c1.reg[15])
                    c1.ID = atoi(c1.buf + c1.ID) - 2;
                else
                    {
                    while (c1.buf[c1.ID] != '\n')
                        c1.ID++;
                    c1.ID--;
                    }
                break;
            case CMD_JMPE:
                c1.ID++; 
                if (stack_pop(&c1.stack) == c1.reg[15])
                    c1.ID = atoi(c1.buf + c1.ID) - 2;
                else
                    {
                    while (c1.buf[c1.ID] != '\n')
                        c1.ID++;
                    c1.ID--;
                    }
                break;
            case CMD_JBE:
                c1.ID++; 
                if (stack_pop(&c1.stack) <= c1.reg[15])
                    c1.ID = atoi(c1.buf + c1.ID) - 2;
                else
                    {
                    while (c1.buf[c1.ID] != '\n')
                        c1.ID++;
                    c1.ID--;
                    }
                break;
            case CMD_JAE:
                c1.ID++; 
                if (stack_pop(&c1.stack) >= c1.reg[15])
                    c1.ID = atoi(c1.buf + c1.ID) - 2;
                else
                    {
                    while (c1.buf[c1.ID] != '\n')
                        c1.ID++;
                    c1.ID--;
                    }
                break;
            case CMD_JNE:
                c1.ID++; 
                if (stack_pop(&c1.stack) != c1.reg[15])
                    c1.ID = atoi(c1.buf + c1.ID) - 2;
                else
                    {
                    while (c1.buf[c1.ID] != '\n')
                        c1.ID++;
                    c1.ID--;
                    }
                break;

            default:
                printf("CPU ERROR\n");
            }
        }
    free(c1.buf);
    stack_destruct(&c1.stack);
    }