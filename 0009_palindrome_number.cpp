#include <cstdint>

class Solution 
{
public:
    bool isPalindrome(int x) 
    {
        // A negative number cannot be a palindrome.
        if (x < 0)
            return false;

        // Reverse the number and check if it matches the original. 
        // Use 64-bit integers to avoid overflows when reversing.
        std::int64_t original = x;
        std::int64_t reverse = 0;

        while (x > 0)
        {
            reverse *= 10;
            reverse += x % 10;
            x /= 10;
        }

        return reverse == original;
    }
};