#include "stackCpp.h"



void* mycalloc (int size_of_elem, int size)
    {
    char* mem = (char*) calloc (size, size_of_elem);
    if (mem == NULL) 
        {
        printf("Calloc error\n");
        exit (1);
        }
    return mem;
    }



const data& Stack::operator[] (int n) const
    {                                               
    assert (0 <= n && n < capacity_);

    return  (const data&) (arr_[n]);
    }



int Stack::verification()
    {
    unsigned long long hash_check = 0;
    if (this == NULL)
        {
        printf("NULL pointer");
        return 5;
        }
    if (top_ >= capacity_)
        {
        printf("stack overflow\n");
        return 1;
        }
    if (arr_ == NULL)
        {
        printf("Stack was destructed\n");
        return 2;
        }
    if (canary_left_ != canary)
        {
        printf("Stack was attacked from left\n");
        return 3;
        }
    if (canary_right_ != canary)
        {
        printf("Stack was attacked from right\n");
        return 4;
        }
    for (int i = 0; i < sizeof(Stack) - 2 * sizeof(unsigned long long); i++)
        hash_check += *((unsigned char*)(&(top_)) + i);
    for (int i = 0; i < capacity_; i++)
        hash_check += *((unsigned char*)(arr_) + i);

    if (hash_guard_ != hash_check)
        {
        printf("Stack was attacked, hash was changed\n");
        Dump();
        exit (5);
        }

    return 0;
    }



Stack::Stack(int Stsize)
    {
    assert(this != NULL);
    canary_left_ = canary;
    canary_right_ = canary;
    arr_ = (data*) mycalloc (Stsize, sizeof(data));
    top_ = -1;
    capacity_ = Stsize;
    hash_guard_ = 0;
    for (int i = 0; i < Stsize; i++)
        *(arr_ + i) = poison;

    for (int i = 0; i < sizeof(Stack) - 2 * sizeof(unsigned long long); i++)
        hash_guard_ += *((unsigned char*)(&(top_)) + i);
    for (int i = 0; i < capacity_; i++)
        hash_guard_ += *((unsigned char*)(arr_) + i);
    }



Stack::~Stack()
    {
    assert(this != NULL);
    free(arr_);
    arr_ = NULL;
    capacity_ = 0;
    }



void Stack::push(data inp)
    {
    assert(this != NULL);
    if (verification () == 0)
        {
        if (top_ >= capacity_ - 1)
            {
            data* temp = arr_;
            temp = (data*) realloc (temp, (capacity_ + 10) * sizeof(data));
            if (temp != NULL)
                {
                arr_ = temp;
                capacity_ += 10;
                }
            else
                {
                printf("failed memory reallocation\n");
                push(inp);
                return;
                }
            }
        (top_)++;
        *((arr_) + (top_)) = inp;

        hash_guard_ = 0;
        for (int i = 0; i < sizeof(Stack) - 2 * sizeof(unsigned long long); i++)
            hash_guard_ += *((unsigned char*)(&(top_)) + i);
        for (int i = 0; i < capacity_; i++)
            hash_guard_ += *((unsigned char*)(arr_) + i);
        }
    }



data Stack::pop()
    {
    assert(this != NULL);
    if (verification () == 0)
        {
        if (top_ > -1)
            {
            data temp = *((arr_) + (top_));
            *(arr_ + top_) = poison;
            (top_) --;

            hash_guard_ = 0;
            for (int i = 0; i < sizeof(Stack) - 2 * sizeof(unsigned long long); i++)
                hash_guard_ += *((unsigned char*)(&(top_)) + i);
            for (int i = 0; i < capacity_; i++)
                hash_guard_ += *((unsigned char*)(arr_) + i);

            return temp;
            }
        else 
            {
            printf("stack is empty\n");
            return poison;
            }
        }
    else return poison;
    }



void Stack::Dump()
    {
    if (verification() == 0)
        {
        printf("Stack adress = %p\nStack capacity = %d\ntop = %d\narray adress = %p\nhash = %llu\nstack contains:\n", this, capacity_, top_, arr_, hash_guard_);
        if (top_ == -1)
            printf("Nothing, Stack is empty\n");
        else
        for (int i = 0; i <= top_; i++)
            printf("array[%d] = %lf\n", i, *(arr_ + i));
        }
    }



void Stack::clear_stack()
    {
    assert(this != NULL);
    for (int i = top_; i < capacity_; i++)
        *(arr_ + i) = poison;
    top_ = -1;
    hash_guard_ = 0;
    for (int i = 0; i < sizeof(Stack) - 2 * sizeof(unsigned long long); i++)
        hash_guard_ += *((unsigned char*)(&(top_)) + i);
    for (int i = 0; i < capacity_; i++)
        hash_guard_ += *((unsigned char*)(arr_) + i);
    }



data Stack::get()
    {
    assert(this != NULL);
    if (verification () == 0)
        return *((arr_) + (top_));
    else return poison;
    }


/*int main()
    {
    Stack stk1 (20);
    stk1.push(3);
    int k = stk1[0];
    printf("%d\n", k);
    }*/












/*c++ c урока
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
    void Print() const ; обозначение что функция не меняет объект
    int& operator[] (int n)
    const int& operator[] (int n) const
    int Sum (const Stack& stk)
    };

int main()
    {
    Stack stk;
    
    stk.StackPush (20);

    int val = stk.operator[0];сделаем стек как массив или
    int value = stk[0];
    
    }

int&ref = value;

ref = 0; здесь мы обнулили value так лучше не длеать, не понятно, ссылки хороши когда они константные

int Sum (const Stack& stk)


    {

    int Sum = 0;
    for (int  = 0; size = stk.GetSize(); i < size; i++)
        sum += (*stk)[i];
    return sum;
    }

const int& stack::operator[] (int n) const  возвращает константную ссылку (избегаем копирование) ;       
    {                                               
    assert (0 <=  && n < size_); // 04.04.2021 нам нужны ссылки, чтобы компилятор сам приписывал звездочки

    return  /* &  data_[n];
    }*/
/* Перегрузка
int& stack::operator[] (int n)   возвращает ссылку ;       
    {                                               
    assert (0 <=  && n < size_); // 04.04.2021 нам нужны ссылки, чтобы компилятор сам приписывал звездочки

    return  /* &  data_[n];
    }*/
/*
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
void Stack::Print() const
    {

    }
    */