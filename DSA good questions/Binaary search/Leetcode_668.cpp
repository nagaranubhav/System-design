#include<algorithm>
#include <climits>

class Solution {
public:
    int findKthNumber(int m, int n, int k) {

        /*
        ============================
        INTERVIEW NOTES (LC 668)
        ============================

        We have a multiplication table:
            table[i][j] = i * j

        Rows = m, Columns = n

        We need the k-th smallest number in this table.

        Problem:
        - m * n can be very large (up to 9e8).
        - We cannot generate and sort all values.

        So instead of finding the element directly,
        we SEARCH the ANSWER SPACE using Binary Search.

        -----------------------------------------
        KEY IDEA: Binary Search on Answer
        -----------------------------------------

        Smallest possible value = 1
        Largest possible value  = m * n

        For any guessed value 'mid', we ask:
            "How many numbers in the table are <= mid ?"

        If count(mid) >= k:
            mid is big enough to include the k-th number,
            so try smaller values (move left).

        Else:
            mid is too small,
            so move right.

        -----------------------------------------
        HOW TO COUNT <= mid ?
        -----------------------------------------

        Each row i looks like:
            i*1, i*2, i*3, ..., i*n

        We want:
            i * j <= mid

        Solve for j:
            j <= mid / i

        That means in row i,
        at most (mid / i) elements are <= mid.

        BUT:
        Each row has only n columns.

        So actual count from row i is:
            min(n, mid / i)

        We sum this for all rows.

        -----------------------------------------
        Time Complexity:
        -----------------------------------------
        Counting = O(m)
        Binary search = log(m*n)

        Total = O(m * log(m*n))
        */

        long long left = 1;
        long long right = (long long)m * n;
        int answer = 0;

        while (left <= right) {

            // mid is our guessed answer value
            long long mid = left + (right - left) / 2;

            long long count = 0;

            // Count how many numbers <= mid exist in table
            for (int i = 1; i <= m; i++) {

                /*
                Row i contains:
                    i*1, i*2, i*3 ... i*n

                We need:
                    i*j <= mid
                =>  j <= mid / i

                So row contributes:
                    mid / i elements

                But max columns = n

                Hence:
                    min(n, mid / i)
                */

                count += min((long long)n, mid / i);
            }

            /*
            Now we compare count with k.

            If count >= k:
                There are already k or more numbers <= mid,
                so mid might be our answer.
                Try smaller values -> move left.

            Else:
                Not enough numbers <= mid,
                so mid is too small -> move right.
            */

            if (count >= k) {
                answer = mid;
                right = mid - 1;
            } 
            else {
                left = mid + 1;
            }
        }

        return answer;
    }
};
