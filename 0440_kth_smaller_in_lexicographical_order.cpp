#include <string>
#include <vector>

class Solution 
{
public:
    int findKthNumber(int n, int k) 
    {
        // First obtain the cumulative amount of numbers that can be generated using a certain amount of digits.
        std::vector<int> cumulative_amount_of_numbers = GenerateCumulativeAmountOfNumbers();

        // Convert the given n to string, as it will be easier to do some checks.
        std::string limit = std::to_string(n);

        // Obtain the modulos of n for each power of 10.
        std::vector<int> n_modulo_power_of_10;
        n_modulo_power_of_10.reserve(limit.size());
        for (int power = 10; power <= n; power *= 10)
            n_modulo_power_of_10.push_back(n % power);
        n_modulo_power_of_10.push_back(n);

        // Store in a variable if the number we are currently generating is already smaller than the limit.
        // This is used to compute how many numbers we can generate with the same order of magnitude than the limit.
        bool generated_number_is_already_smaller = false;

        int result = 0;

        // Now iterate over the digits of the answer, we know it can have at most as many as n.
        for (std::size_t digit_position = 0; digit_position < limit.size(); ++digit_position)
        {
            int candidate_digit = digit_position == 0 ? 1 : 0;

            int numbers_to_skip_per_digit = 
                ComputeNumbersAvailable(digit_position + 1, limit, generated_number_is_already_smaller || limit[digit_position] - '0' > candidate_digit, 
                                        limit[digit_position] - '0' < candidate_digit, n_modulo_power_of_10, cumulative_amount_of_numbers);
            
            while (k > numbers_to_skip_per_digit)
            {
                ++candidate_digit;
                k -= numbers_to_skip_per_digit;

                numbers_to_skip_per_digit = 
                    ComputeNumbersAvailable(digit_position + 1, limit, generated_number_is_already_smaller || limit[digit_position] - '0' > candidate_digit, 
                                            limit[digit_position] - '0' < candidate_digit, n_modulo_power_of_10, cumulative_amount_of_numbers);
            }

            result *= 10;
            result += candidate_digit;

            // Now check if we can mark the current number as already smaller.
            if (!generated_number_is_already_smaller)
            {
                // Unless the new digit matches the one of the limit, we will mark the number as smaller.
                // If the digit is smaller, the reason is obvious. Otherwise, it means the digit is bigger,
                // so that implies the resulting number will have to use fewer digits than the limit, meaning it will be smaller.
                // In that second case, we increment the digit_position to simplify the computations, as if leaving a blank at front.
                if (candidate_digit != limit[digit_position] - '0')
                    generated_number_is_already_smaller = true;
                if (candidate_digit > limit[digit_position] - '0')
                    ++digit_position;
            }

            // If we have reached k == 1, we have our number, so stop. Otherwise, subtract 1 as we ignore finishing the number here.
            if (k == 1)
                break;

            --k;
        }

        return result;
    }

private:
    /// Returns a std::vector that in position i contains the amount of numbers that can be formed using i digits or less.
    std::vector<int> GenerateCumulativeAmountOfNumbers()
    {
        // We will only fill the first 9 positions, as according to the statement, we will not need anything else.
        std::vector<int> result(9);

        // Initialize the first element. With zero digits there is only one option.
        result[0] = 1;

        int current_power_of_ten = 1;
        for (std::size_t i = 1; i < result.size(); ++i)
        {
            current_power_of_ten *= 10;
            result[i] = result[i - 1] + current_power_of_ten;
        }

        return result;
    }

    /// Computes how many numbers can be generated starting at the given @p digit_position, and considering if the previous
    /// digits imply that the number is already smaller or not.
    int ComputeNumbersAvailable(std::size_t digit_position, std::string const& limit, bool generated_number_is_already_smaller, 
                                bool new_digit_is_bigger, std::vector<int> const& limit_modulo_power_of_10, 
                                std::vector<int> const& cumulative_amount_of_numbers)
    {
        // If the number we are generating was not already smaller but the given digit is bigger than the equivalent at the limit,
        // that makes it mandatory to make the number shorter, so we recursively call the same function incrementing the index
        // and marking the number as smaller.
        if (!generated_number_is_already_smaller && new_digit_is_bigger)
        {
            return ComputeNumbersAvailable(digit_position + 1, limit, /*generated_number_is_already_smaller*/ true, 
                                           new_digit_is_bigger, limit_modulo_power_of_10, cumulative_amount_of_numbers);
        }

        // If we are adding the last number, the only option is finishing.
        if (digit_position == limit.size())
            return 1;

        // If the number is smaller, we can use the remaining digits however we want.
        if (generated_number_is_already_smaller)
            return cumulative_amount_of_numbers[limit.size() - digit_position];

        // Otherwise, we can use all of them but one (this way it will be smaller) and then count how many options
        // using all the available digits.
        int result = digit_position != limit.size() ? cumulative_amount_of_numbers[limit.size() - digit_position - 1] : 0;
        return result + limit_modulo_power_of_10[limit.size() - digit_position - 1] + 1;
    }
};
