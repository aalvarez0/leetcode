#include <barrier>
#include <functional>
#include <semaphore>

class H2O 
{
public:
    H2O() 
    {
        
    }

    void hydrogen(std::function<void()> releaseHydrogen) 
    {
        m_hydrogen_blocker.acquire();
        m_barrier.arrive_and_wait();

        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();

        m_hydrogen_blocker.release();
    }

    void oxygen(std::function<void()> releaseOxygen) 
    {
        m_oxygen_blocker.acquire();
        m_barrier.arrive_and_wait();

        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();

        m_oxygen_blocker.release();
    }

private:
    std::counting_semaphore<2> m_hydrogen_blocker{2};    
    std::counting_semaphore<1> m_oxygen_blocker{1};
    std::barrier<> m_barrier{3};    
};