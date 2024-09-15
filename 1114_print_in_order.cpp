#include <semaphore>

class Foo 
{
public:
    Foo() 
    {
        
    }

    void first(function<void()> printFirst) 
    {
        
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();

        m_second_semaphore.release();
    }

    void second(function<void()> printSecond) 
    {
        m_second_semaphore.acquire();
        
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();

        m_third_semaphore.release();
    }

    void third(function<void()> printThird) 
    {
        m_third_semaphore.acquire();

        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }

private:
    std::binary_semaphore m_second_semaphore{0};
    std::binary_semaphore m_third_semaphore{0};
};