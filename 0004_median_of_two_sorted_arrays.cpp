#include <algorithm>
#include <functional>
#include <vector>

class Solution 
{
public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) 
    {
        std::size_t median_position = (nums1.size() + nums2.size()) / 2;

        int ini1 = 0;
        int ini2 = 0;
        int fin1 = static_cast<int>(nums1.size()) - 1;
        int fin2 = static_cast<int>(nums2.size()) - 1;

        // Do a double binary search to find the median of the two vectors.
        while (ini1 <= fin1 || ini2 <= fin2)
        {
            // Always prune from the interval with the most elements. We will find the position of the mid element
            // inside the other vector. To handle repeated elements, we consider every element in vector 1 to be smaller 
            // than equal elements of vector 2.
            if (fin1 - ini1 > fin2 - ini2)
            {
                int mid1 = (ini1 + fin1) / 2;
                int mid2 = std::lower_bound(nums2.begin(), nums2.end(), nums1[mid1]) - nums2.begin();

                if (mid1 + mid2 <= median_position)
                {
                    ini1 = mid1 + 1;
                    ini2 = std::max(ini2, std::min(fin2 + 1, mid2));
                }
                else
                {
                    fin1 = mid1 - 1;
                    fin2 = std::min(fin2, mid2 - 1);
                }
            }
            else
            {
                int mid2 = (ini2 + fin2) / 2;
                int mid1 = std::upper_bound(nums1.begin(), nums1.end(), nums2[mid2]) - nums1.begin();

                if (mid1 + mid2 <= median_position)
                {
                    ini1 = std::max(ini1, std::min(fin1 + 1, mid1));
                    ini2 = mid2 + 1;
                }
                else
                {
                    fin1 = std::min(fin1, mid1 - 1);
                    fin2 = mid2 - 1;
                }
            }
        }

        // Now, depending on the parity, we have to retrieve the biggest or the two biggest elements before ini1 and ini2.
        // To simplify the code, we just put the four candidates in a vector and sort it.
        std::vector<int> candidates;
        candidates.reserve(4);

        for (std::size_t i = 0; i < 2 && ini1 != 0; ++i)
        {
            candidates.push_back(nums1[ini1 - 1]);
            --ini1;
        }
        for (std::size_t i = 0; i < 2 && ini2 != 0; ++i)
        {
            candidates.push_back(nums2[ini2 - 1]);
            --ini2;
        }
        std::sort(candidates.begin(), candidates.end(), std::greater<>());

        if ((nums1.size() + nums2.size()) % 2 == 0)
            return (candidates[0] + candidates[1]) / 2.0;
        return candidates[0];
    }
};