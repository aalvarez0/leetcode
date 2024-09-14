#include <string>

class Solution 
{
public:
    std::string longestPalindrome(std::string s) 
    {
        int begin_longest = 0;
        int size_longest = 0;

        // Iterate to fix the middle element of the palindrome, both for the odd and even case.
        // Then consider the biggest palindrome with that center.
        for (int i = 0; i < static_cast<int>(s.size()); ++i)
        {
            int length_odd = 2 * FindLongestPalindrome(s, i, i) - 1;
            if (length_odd > size_longest)
            {
                begin_longest = i - length_odd / 2;
                size_longest = length_odd;
            }

            int length_even = 2 * FindLongestPalindrome(s, i, i + 1);
            if (length_even > size_longest)
            {
                begin_longest = i - length_even / 2 + 1;
                size_longest = length_even;
            }
        }

        return s.substr(begin_longest, size_longest);
    }

private:
    /// Returns the maximum number of iterations that can be done moving the indices to the sides while matching the characters.
    int FindLongestPalindrome(std::string const& s, int left_index, int right_index) const
    {
        int iterations = 0;
        
        while (left_index >= 0 && right_index < s.size() && s[left_index] == s[right_index])
        {
            --left_index;
            ++right_index;
            ++iterations;
        }

        return iterations;
    }
};