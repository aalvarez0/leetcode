#include <functional>
#include <semaphore>

class ZeroEvenOdd 
{
private:
    int n;

    std::binary_semaphore m_zero_blocker{1};
    std::binary_semaphore m_even_blocker{0};
    std::binary_semaphore m_odd_blocker{0};

public:
    ZeroEvenOdd(int n) 
    {
        this->n = n;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(std::function<void(int)> printNumber) 
    {
        for (int i = 0; i < n; ++i)
        {
            m_zero_blocker.acquire();

            printNumber(0);

            if (i % 2 == 0)
                m_odd_blocker.release();
            else
                m_even_blocker.release();
        }    
    }

    void even(std::function<void(int)> printNumber) 
    {
        for (int i = 2; i <= n; i += 2)
        {
            m_even_blocker.acquire();

            printNumber(i);

            m_zero_blocker.release();
        }    
    }

    void odd(std::function<void(int)> printNumber) 
    {
        for (int i = 1; i <= n; i += 2)
        {
            m_odd_blocker.acquire();

            printNumber(i);

            m_zero_blocker.release();
        }    
    }
};