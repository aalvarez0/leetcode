#include <semaphore>

class FooBar 
{
private:
    int n;

    std::binary_semaphore foo_blocker{1};
    std::binary_semaphore bar_blocker{0};

public:
    FooBar(int n) 
    {
        this->n = n;
    }

    void foo(function<void()> printFoo) 
    {
        
        for (int i = 0; i < n; i++) 
        {
            foo_blocker.acquire();
            
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();

            bar_blocker.release();
        }
    }

    void bar(function<void()> printBar) 
    {
        
        for (int i = 0; i < n; i++) 
        {
            bar_blocker.acquire();

        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();

            foo_blocker.release();
        }
    }
};