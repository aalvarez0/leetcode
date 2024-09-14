#include <limits>
#include <optional>
#include <string>
#include <vector>

class Solution 
{
public:
    int lengthOfLongestSubstring(std::string s) 
    {
        // Create a vector in which we will store the last seen position of a character.
        std::vector<std::optional<std::size_t>> last_seen_position(std::numeric_limits<char>::max());

        std::size_t max_length = 0;
        std::size_t current_substring_start_position = 0;

        for (std::size_t i = 0; i < s.size(); ++i)
        {
            char c = s[i];

            // If the current character is within our current substring, shift the substring so that it starts
            // just after the last position in which we found it.
            if (last_seen_position[c] && *last_seen_position[c] >= current_substring_start_position)
                current_substring_start_position = *last_seen_position[c] + 1;
            
            // Update the last seen position for this character.
            last_seen_position[c] = i;

            // Check if the current substring is better than our current best.
            max_length = std::max(max_length, i - current_substring_start_position + 1);
        }

        return max_length;
    }
};