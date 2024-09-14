#include <string>
#include <vector>

class Solution 
{
public:
    bool isMatch(std::string s, std::string p) 
    {
        // We are going to apply dynamic programming to solve this problem. We will remember our current position
        // in string and pattern, since when we use '*' characters we can both decide to use it or not, even if we
        // could for that specific string character. To simplify the coding, we will swap the order of x* to *x, for any x.
        std::vector<std::vector<int>> memoization_table(s.size() + 1, std::vector<int>(p.size() + 1, -1));

        for (std::size_t i = 0; i < p.size(); ++i)
        {
            if (p[i] == '*')
                std::swap(p[i - 1], p[i]);
        }

        return Solve(0, 0, s, p, memoization_table);
    }

private:
    bool Solve(std::size_t string_index, std::size_t pattern_index, std::string const& s, std::string const& p, 
               std::vector<std::vector<int>>& memoization_table)
    {
        int& entry = memoization_table[string_index][pattern_index];
        if (entry == -1)
        {
            // This case of the DP is not computed, obtain the result. A couple cases could be unified,
            // but the code keeps them separated for clarity purposes.

            if (string_index == s.size())
            {
                // If we have finished the string, it will be a match in two cases:
                // - The pattern has been finished as well.
                // - The pattern only contains '*' until the end.
                if (pattern_index == p.size())
                    entry = 1;
                else if (p[pattern_index] == '*')
                    entry = Solve(string_index, pattern_index + 2, s, p, memoization_table);
                else
                    entry = 0;
            }
            else if (pattern_index == p.size())
            {
                // The pattern has been finished, but not the string. This cannot be a match.
                entry = 0;
            }
            else if (p[pattern_index] == '.')
            {
                // If the pattern matches any character, just move both indices and check if the rest is a match.
                entry = Solve(string_index + 1, pattern_index + 1, s, p, memoization_table);
            }
            else if (p[pattern_index] == '*')
            {
                // Here we need to decide if we use the '*' or not.
                // Explore first the path of not using it, so just move the pattern index.
                entry = Solve(string_index, pattern_index + 2, s, p, memoization_table);

                // Now check if we can use it, for that the current character of the string needs to match the next of the pattern.
                // Notice that the restrictions of the statement guarantees that accessing the next index is safe.
                if (s[string_index] == p[pattern_index + 1] || p[pattern_index + 1] == '.')
                    entry = entry || Solve(string_index + 1, pattern_index, s, p, memoization_table);
            }
            else if (s[string_index] == p[pattern_index])
            {
                // No special characters in the pattern, but the current one matches, so move the indices
                // and continue checking.
                entry = Solve(string_index + 1, pattern_index + 1, s, p, memoization_table);
            }
            else
            {
                // No match on these characters, so stop here.
                entry = 0;
            }
        }

        return entry == 1;
    }

    std::vector<std::vector<int>> memoization_table;
};

