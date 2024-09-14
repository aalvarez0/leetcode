#include <string>
#include <vector>

class Solution 
{
public:
    std::string convert(std::string s, int numRows) 
    {
        if (numRows == 1)
            return s;

        std::string result(s.size(), '-');
        std::size_t result_index = 0;

        // Iterate over the rows, then use the formula for the jumps we do on every row.
        for (int i = 0; i < numRows; ++i)
        {
            int index = i;
            int parity = 0;
    
            while (index < static_cast<int>(s.size()))
            {
                result[result_index++] = s[index];
                index += GetIncrement(i, numRows, parity);
                parity = 1 - parity;
            }
        }

        return result;
    }

private:
    /// Returns the next jump for the index in a row.
    /// To compute them, just notice that there are two cases: going down and going up.
    /// Except for the first and the last row, each row has the two different cases,
    /// so we just need to distinguish the three cases and compute the corresponding formulae.
    ///
    /// @pre num_rows > 1
    int GetIncrement(int row, int num_rows, int parity)
    {
        if (row == 0 || row == num_rows - 1)
            return 2 * num_rows - 2;
        return parity == 0 ? 2 * (num_rows - row) - 2 : 2 * row;
    }
};