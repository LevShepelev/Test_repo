#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define poison -666
#define canary 0xDEADBEEFBEEFDEAD
typedef double data;

typedef struct str_stack {unsigned long long canary_left; unsigned long long hash_guard; int top; int capacity; data* arr; unsigned long long canary_right;} mystack;

void stack_push(mystack* s1, data inp);
int verification(mystack* s1);
void stack_construct(mystack* s1, int Stsize);
void stack_destruct(mystack* s1);
data stack_pop(mystack* s1);
void print_stack(mystack* s1);
void clear_stack(mystack* s1);
data stack_get(mystack* s1);
void* mycalloc (int size_of_elem, int size);

