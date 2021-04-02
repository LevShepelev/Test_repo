#include <assert.h>
/*struct Stack
    {
    int data[10];
    int size;
    };

void StackCtor (stack* stk)
    {
    assert(stk);

    stk -> size = 0;
    for (int i = 0; i < 10; i++) stk -> data[i] = poison;
    }

    void StackDtor (stack* stk)
    {
    assert(stk);

    stk -> size = -1;
    }

void StackPush (stack* stk, int value)
    {
    assert(stack);
    stk -> data [stk -> size++] = value;
    }

int StackPop (stack* stk)
    {
    assert(stk);
    assert(stk -> size > 0);

    return stk -> data[stk -> size];
    }

int main()
    {
    Stack stk1 = {};
    Stack stk2 = {};
    tackCtor (&stk1);
    StackCtor (&stk2);

    StackPush (&stk, 10);
    StackPush (&stk, 20);

    int val = stackPop(&stk);
    StackDtor(&stk1)
    StackDtor(&stk2)
    }*/

//c++
class Stack
    {
    private://по умолчанию все элементы private
    const char* name_;
    int data_[10];
    int capacity_;//_означает принадлежность классу
    int size_;//здесь задается порядок инициализации и деструктуризации 
    public:
    Stack();
    Stack (int Size, const char* name);  // функции члена класса, компилятор сам передает указатель на объект
    ~Stack ();

    void Push (int value);
    int Pop ();
    void Print();
    };

int main()
    {
    Stack stk1;
    Stack stk2 (200);// конструтор сам вызывается
    for (auto elem : stk1.data_)
        printf("%d ", elem);
    stk1.pinrt();
    stk1.StackPush (10);
    stk2.StackPush (20);

    int val = stackPop();
    //деструторы сами вызываются
    }

Stack::Stack (int Size, const char* name) :
    data_(),//автоматическая инициализация data
    capacity_ (10),
    size_ ((printf("size\n"), 0) //печать инициализации
    {
    assert(stk);

    size = 0;
    for (int i = 0; i < 10; i++) data[i] = poison;
    }

Stack::Stack (const char* name) ://конструтор по умолчанию
    data_(),//автоматическая инициализация data
    capacity_ (10),
    size_ (0)
    {
    assert(this);
    for (int i = 0; i < 10; i++) data_ [i] = poison;
    }

Stack::~Stack ()
    {
    assert(this);

    size_ = -1;
    }

void Stack::Push (int value)
    {
    assert(this);
    data_ [size_++] = value;
    }

int Stack::Pop ()
    {
    assert(this);
    assert(size_ > 0);

    return data_ [--size_];
    }
void Stack::Print()