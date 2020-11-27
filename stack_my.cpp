#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int data;
typedef struct str_stack mystack;
struct str_stack {int top; int capacity; data* arr;};

int verifacation(mystack* s1)
    {
    if (s1 -> top > 0) return 0;
    else
        {
        printf("stack overflow");
        return 1;
        }
    }

void stack_construct(mystack* s1, int Stsize)
    {
    s1 -> arr = (data*) calloc (Stsize, sizeof(data));
    s1 -> top = Stsize;
    s1 -> capacity = Stsize;
    }
void stack_destruct(mystack* s1)
    {
    free(s1 -> arr);
    }

void stack_push(mystack* s1, data inp)
    {
    assert(!verifacation(s1));
    (s1 -> top) --;
    *((s1 -> arr) + (s1 -> top)) = inp;
    }

data stack_pop(mystack* s1)
    {
    data temp;
    if (s1 -> top < s1 -> capacity - 1)
        {
        temp = *((s1 -> arr) + (s1 -> top));
        (s1 -> top) ++;
        return temp;
        }
    else printf("stack is empty");
    }

void print_stack(mystack* s1)
    {
    if (s1 -> top == s1 -> capacity - 1)
        printf("Stack is empty");
    else
        {
        printf("Stack adress = %p\nStack capacity = %d\ntop = %d\narray adress = %p\nstack contains:\n", s1, s1 -> capacity, s1 -> top, s1 -> arr);
        for (int i = s1 -> top; i < s1 -> capacity; i++)
            printf("array[%d] = %d\n", i, *(s1 -> arr + i));
        }
    }
void clear_stack(mystack* s1)
    {
    for (int i = s1 -> top; i < s1 -> capacity; i++)
        *(s1 -> arr + i) = 0;
    }
data stack_get(mystack* s1)
    {
    return *((s1 -> arr) + (s1 -> top));
    }

int main()
    {
    mystack s1;
    stack_construct(&s1, 10);
    for (int i = 0; i < 5; i++)
        stack_push(&s1, i);
    print_stack(&s1);
    printf("pop has made %d\n", stack_pop(&s1));
    }
