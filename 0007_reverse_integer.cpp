#include <cmath>
#include <limits>

class Solution 
{
public:
    int reverse(int x) 
    {
        int result = 0;

        int abs_max_number_divided_by_10 = x > 0 ? std::numeric_limits<int>::max() / 10 : -(std::numeric_limits<int>::min() / 10);

        do 
        {
            if (std::abs(result) > abs_max_number_divided_by_10)
                return 0;

            result *= 10;
            result += x % 10;
            x /= 10;
        } while (x != 0);

        return result;
    }
};