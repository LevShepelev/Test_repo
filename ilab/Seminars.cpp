#include <cstdio>
#include <stdio.h>
#include <iostream>

class Stack {

    public:
    Stack* data;
    int size;
    int capacity;
    int hash;

    public:
    explicit Stack () : data(nullptr), size (0), capacity (0), hash (0)
        {
        printf("default constuctor was called\n");
        }

    Stack (int _capacity) : data(nullptr), size (), capacity (_capacity), hash(0)//конструткор копирования
        {
        data = new Stack [capacity];// или  new Stack(10)
        printf("capacity was called\n");
        }

    Stack (Stack const& obj) : data(nullptr), size (obj.size), capacity (obj.size), hash (obj.size)
        {
        data = new Stack[capacity];
        for (int i = 0; i < capacity; i++) data[i] = obj.data[i];
        }   

    Stack (Stack&& obj) :  data(nullptr), size (obj.size), capacity (obj.size), hash (obj.size)
        {
        printf("move\n");
        obj.data = 0;
        }

    Stack operator=(Stack const& obj)
        {
        return Stack (obj);
        }

    ~Stack ()
        {
        printf("Destructor was called\n");
        delete [] data;
        }
};

void f (Stack const& s)
    {
    getchar();
    }

void swap (Stack& s1, Stack& s2)
    {
    Stack t = s1;
    s1 = s2;
    s2 = t;
    }

int main()
    {
    //Stack stk(1);
    //Stack stk2;
    //stk2 = Stack (10); //временный объект
    Stack stk1 (1);
    Stack stk2 (1);
    swap (stk1, stk2);
    }

