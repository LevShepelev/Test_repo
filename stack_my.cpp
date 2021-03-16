#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define poison -666
#define canary 0xDEADBEEFBEEFDEAD
typedef int data;
typedef struct str_stack mystack;
struct str_stack {unsigned long long canary_left; unsigned long long hash_guard; int top; int capacity; data* arr; unsigned long long canary_right;};

void stack_push(mystack* s1, data inp);
int verification(mystack* s1);
void stack_construct(mystack* s1, int Stsize);
void stack_destruct(mystack* s1);
data stack_pop(mystack* s1);
void print_stack(mystack* s1);
void clear_stack(mystack* s1);
data stack_get(mystack* s1);


int verification(mystack* s1)
    {
    unsigned hash_check = 0;
    if (s1 -> top >= s1 -> capacity)
        {
        printf("stack overflow\n");
        return 1;
        }
    if (s1 -> arr == NULL)
        {
        printf("Stack was destructed\n");
        return 2;
        }
    if (s1 -> canary_left != canary)
        {
        printf("Stack was attacked from left\n");
        return 3;
        }
    if (s1 -> canary_right != canary)
        {
        printf("Stack was attacked from right\n");
        return 4;
        }
    for (int i = 2 * sizeof(unsigned long long); i < sizeof(s1 - 2 * sizeof(unsigned long long)); i++)
        hash_check += *((char*)(&(s1 -> top)) + i);
    for (int i = 0; i < s1 -> capacity; i++)
        hash_check += *((char*)(s1 -> arr) + i);

    if (s1 -> hash_guard != hash_check)
        {
        printf("Stack was attacked, hash was changed\n");
        return 5;
        }

    return 0;
    }

void stack_construct(mystack* s1, int Stsize)
    {
    s1 -> canary_left = canary;
    s1 -> canary_right = canary;
    s1 -> arr = (data*) calloc (Stsize, sizeof(data));
    s1 -> top = -1;
    s1 -> capacity = Stsize;
    s1 -> hash_guard = 0;
    for (int i = 0; i < Stsize; i++)
        *(s1 -> arr + i) = poison;
    for (int i = 2 * sizeof(unsigned long long); i < sizeof(s1 - 2 * sizeof(unsigned long long)); i++)
        s1 -> hash_guard += *((char*)(&(s1 -> top)) + i);
    for (int i = 0; i < s1 -> capacity; i++)
        s1 -> hash_guard += *((char*)(s1 -> arr) + i);

    }

void stack_destruct(mystack* s1)
    {
    s1 -> arr = NULL;
    s1 -> capacity = 0;
    }

void stack_push(mystack* s1, data inp)
    {
    if (verification (s1) == 0)
        {
        if (s1 -> top >= s1 -> capacity)
            {
            data* temp = s1 -> arr;
            temp = (data*) realloc (temp, (s1 -> capacity + 10)*sizeof(data));
            if (temp != NULL)
                s1 -> arr = temp;
            else
                {
                printf("failed memory reallocation");
                stack_push(s1, inp);
                return;
                }
            }
        (s1 -> top)++;
        *((s1 -> arr) + (s1 -> top)) = inp;

        s1 -> hash_guard = 0;
        for (int i = 2 * sizeof(unsigned long long); i < sizeof(s1 - 2 * sizeof(unsigned long long)); i++)
            s1 -> hash_guard += *((char*)(&(s1 -> top)) + i);
        for (int i = 0; i < s1 -> capacity; i++)
            s1 -> hash_guard += *((char*)(s1 -> arr) + i);
        }
    }

data stack_pop(mystack* s1)
    {
    if (verification (s1) == 0)
        {
        if (s1 -> top > -1)
            {
            data temp = *((s1 -> arr) + (s1 -> top));
            *(s1 -> arr + s1 -> top) = poison;
            (s1 -> top) --;

            s1 -> hash_guard = 0;
            for (int i = 2 * sizeof(unsigned long long); i < sizeof(s1 - 2 * sizeof(unsigned long long)); i++)
                s1 -> hash_guard += *((char*)(&(s1 -> top)) + i);
            for (int i = 0; i < s1 -> capacity; i++)
                s1 -> hash_guard += *((char*)(s1 -> arr) + i);

            return temp;
            }
        else 
            {
            printf("stack is empty");
            return poison;
            }
        }
    else return poison;
    }

void print_stack(mystack* s1)
    {
    if (verification(s1) == 0)
        {
        printf("Stack adress = %p\nStack capacity = %d\ntop = %d\narray adress = %p\nhash = %llu\nstack contains:\n", s1, s1 -> capacity, s1 -> top, s1 -> arr, s1 -> hash_guard);
        if (s1 -> top == -1)
            printf("Nothing, Stack is empty");
        else
        for (int i = 0; i <= s1 -> top; i++)
            printf("array[%d] = %d\n", i, *(s1 -> arr + i));
        }
    }
void clear_stack(mystack* s1)
    {
    for (int i = s1 -> top; i < s1 -> capacity; i++)
        *(s1 -> arr + i) = poison;
    s1 -> top = -1;
    s1 -> hash_guard = 0;
    for (int i = 2 * sizeof(unsigned long long); i < sizeof(s1 - 2 * sizeof(unsigned long long)); i++)
        s1 -> hash_guard += *((char*)(&(s1 -> top)) + i);
    for (int i = 0; i < s1 -> capacity; i++)
        s1 -> hash_guard += *((char*)(s1 -> arr) + i);
    }
data stack_get(mystack* s1)
    {
    if (verification (s1) == 0)
        return *((s1 -> arr) + (s1 -> top));
    else return poison;
    }

int main()
    {
    mystack s1;
    stack_construct(&s1, 5);
    printf("constructed\n");
    for (int i = 0; i < 5; i++)
        stack_push(&s1, i);
    printf("Pushed\n");
    print_stack(&s1);
    printf("pop has made %d\n", stack_pop(&s1));
    for (int i = 0; i < s1.top + 1;)
        stack_pop(&s1);
    print_stack(&s1);
    stack_destruct(&s1);
    printf("\ndone\n");
    print_stack(&s1);
    }
