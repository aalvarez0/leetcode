/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution 
{
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
    {
        ListNode* result;

        ListNode* current_result_node = nullptr;
        int carry = 0;

        // Iterate until both of the given numbers have been finished (no more digits)
        // and until the carry is zero.
        while (l1 || l2 || carry != 0)
        {
            if (current_result_node)
            {
                current_result_node->next = new ListNode;
                current_result_node = current_result_node->next;
            }
            else
            {
                // First digit, set the pointer for the result.
                current_result_node = new ListNode;
                result = current_result_node;
            }

            // Set the value depending on which numbers have a digit on this position.
            if (l1 && l2)
            {
                current_result_node->val = l1->val + l2->val + carry;
                l1 = l1->next;
                l2 = l2->next;
            }
            else if (l1)
            {
                current_result_node->val = l1->val + carry;
                l1 = l1->next;
            }
            else if (l2)
            {
                current_result_node->val = l2->val + carry;
                l2 = l2->next;
            }
            else
                current_result_node->val = carry;

            // Update the carry, notice there is no need to use modulo since the value
            // will always be smaller than 20.
            if (current_result_node->val >= 10)
            {
                current_result_node->val -= 10;
                carry = 1;
            }
            else
                carry = 0;
        }

        return result;
    }
};