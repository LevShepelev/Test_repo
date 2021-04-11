#include <cstdio>
#include <stdlib.h>
#include <assert.h>
#include <cstddef>
#define poison -666
#define canary 0xDEADBEEFBEEFDEAD
typedef double data;

class Stack
        {
        unsigned long long canary_left_;
        unsigned long long hash_guard_;
        int top_;
        int capacity_; 
        data* arr_; 
        unsigned long long canary_right_;
        public:
        const data& operator[] (int n) const;    
        void push(data inp);
        int  verification();
        Stack(int Stsize);
        ~Stack();
        data pop();
        void Dump();
        void clear_stack();
        data get();
        };
void* mycalloc (int size_of_elem, int size);

