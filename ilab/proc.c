#include "proc.h"

int main(int argc, char* argv[])
    {
    cpu_t c1;
    int d, u;
    int j = 0;//сделать структуру процессора buf, i, stack 
    struct stat statistica;//массив регистров
    FILE* Commands = fopen(argv[1], "r");
    int stat_error = stat (argv[1], &statistica);

    assert(stat_error == 0);
    c1.buf = (char*) calloc ((statistica.st_size + 1), sizeof(char));
    fread ((void*) c1.buf, sizeof(char), statistica.st_size, Commands);
    fclose(Commands);
    stack_construct(&c1.stack, 10);
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
                c1.ID += 2;
                c1.reg[c1.buf[c1.ID - 1]] = atoi(c1.buf + c1.ID);
                while (c1.buf[c1.ID] != '\n')
                    c1.ID++;
                c1.ID--;
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
                scanf("%d", &u);
                stack_push(&c1.stack, d);
                break;
            }
        }
    stack_destruct(&c1.stack);
    }