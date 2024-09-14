#include <stdexcept>
#include <unordered_map>
#include <vector>

class Solution 
{
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) 
    {
        // Use a hash to store for a given value, in what position is located.
        std::unordered_map<int, int> position_by_value;

        for (std::size_t i = 0; i < nums.size(); ++i)
        {
            int x = nums[i];

            // See if we have in the hash the number that results in target when added to x.
            auto it = position_by_value.find(target - x);

            if (it == position_by_value.end())
            {
                // Such number has not been found, so just push the current number to the hash.
                position_by_value.emplace(x, i);
            }
            else
            {
                // We have found the number, so we have a solution. Nothing else to be done, just return it.
                return {it->second, static_cast<int>(i)};
            }
        }

        // According to the statement, this case is not possible, so throw if we ever reach it.
        throw std::runtime_error("twoSum: Invalid input! It does not contain a valid solution.");
    }
};