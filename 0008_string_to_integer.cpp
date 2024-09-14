#include <limits>
#include <string>

class Solution 
{
public:
    int myAtoi(std::string s) 
    {
        std::int64_t integer = 0;

        bool negative = false;
        bool reading_digits = false;

        std::int64_t overflow_limit = std::numeric_limits<std::int64_t>::max() / 100;

        // According to the statement, we will receive a possibly empty sequence of whitespaces,
        // then either +, - or nothing, then the digits (maybe none), then some non-digit character or the end of the string.
        // We will iterate the string, distinguishing if we have reached the first digit or not.
        for (char c : s)
        {
            if (reading_digits)
            {
                if (!std::isdigit(c))
                    break;
                
                // Make sure the number fits in 64-bit. If it does not, assign the max value of a 32-bit
                // integer and we will detect the overflow later.
                if (integer > overflow_limit)
                    integer = std::numeric_limits<std::int32_t>::max();

                integer *= 10;
                integer += c - '0';
            }
            else
            {
                // We have not received the digits yet, so we can receive spaces, the sign or a digit.
                // If we receive something else, that means that there will be no digits and we need to stop reading.
                if (c == '-' || c == '+')
                {
                    negative = c == '-';
                    reading_digits = true;
                }
                else if (std::isdigit(c))
                {
                    reading_digits = true;
                    integer = c - '0';
                }
                else if (c != ' ')
                    break;
            }
        }

        // Change the sign if the number is negative.
        if (negative)
            integer = -integer;

        // Make it fit into a 32-bit signed integer.
        if (integer > std::numeric_limits<std::int32_t>::max())
            integer = std::numeric_limits<std::int32_t>::max();
        else if (integer < std::numeric_limits<std::int32_t>::min())
            integer = std::numeric_limits<std::int32_t>::min();

        return static_cast<std::int32_t>(integer);
    }
};