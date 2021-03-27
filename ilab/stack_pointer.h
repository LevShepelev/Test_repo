#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define poison -666
#define canary 0xDEADBEEFBEEFDEAD
typedef double data_double;

typedef struct str_stack_pointer {unsigned long long canary_left; unsigned long long hash_guard; int top; int capacity; data_double* arr; unsigned long long canary_right;} mystack_double;

void double_stack_push(mystack_double* s1, data_double inp);
int double_verification(mystack_double* s1);
void double_stack_construct(mystack_double* s1, int Stsize);
void double_stack_destruct(mystack_double* s1);
data_double double_stack_pop(mystack_double* s1);
void double_print_stack(mystack_double* s1);
void double_clear_stack(mystack_double* s1);
data_double double_stack_get(mystack_double* s1);
