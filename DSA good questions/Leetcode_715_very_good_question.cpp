#include <bits/stdc++.h>
using namespace std;

/*
===========================
 LeetCode 715 - Range Module
===========================

We DO NOT store individual numbers.
We store continuous ranges as intervals:

    [l, r)

Using:
    map<int,int> mp;

Meaning:
    mp[l] = r   ---> interval [l, r)

Properties:
- map is always sorted by key (l)
- intervals never overlap
- intervals are always merged

Think in pictures on number line.
Add = paint
Remove = erase
Query = check paint
*/

class RangeModule {
public:

    // Stores intervals as: start -> end
    map<int,int> mp;

    RangeModule() {}

    /*
    ======================
        ADD RANGE
    ======================

    addRange(left, right)
    Means: add [left, right)

    Idea:
    - Find overlapping intervals
    - Merge them
    - Delete old ones
    - Insert merged interval

    Picture:
        old:   [5----10)   [15----20)
        add:          [8---------18)

        result: [5---------------20)
    */
    void addRange(int left, int right) {

        // Find first interval whose start >= left
        auto it = mp.lower_bound(left);

        // Maybe previous interval overlaps with left
        // Example:
        //   [5----15)
        // add(10,20)
        // prev.second = 15 >= 10 -> overlap
        if(it != mp.begin() && prev(it)->second >= left) {
            it = prev(it);
        }

        // Merge all overlapping intervals
        while(it != mp.end() && it->first <= right) {
            // Expand current new interval
            left  = min(left,  it->first);
            right = max(right, it->second);

            // Remove old interval and move iterator
            it = mp.erase(it);
        }

        // Insert merged interval
        mp[left] = right;
    }

    /*
    ======================
        QUERY RANGE
    ======================

    queryRange(left, right)
    Means: check if [left, right) is fully covered

    Idea:
    - Find the interval just before left
    - Check if its end >= right

    Picture:
        [10----20)
           [12---18] -> true

        [10----20)   [30----40)
           [12-----------35] -> false
    */
    bool queryRange(int left, int right) {

        // First interval with start > left
        auto it = mp.upper_bound(left);

        // If no interval before left
        if(it == mp.begin()) return false;

        // Move to previous interval
        --it;

        // Check coverage
        return it->second >= right;
    }

    /*
    ======================
        REMOVE RANGE
    ======================

    removeRange(left, right)
    Means: remove [left, right)

    Idea:
    - Find overlapping intervals
    - For each interval [a,b):
         left part  = [a, left)
         right part = [right, b)
    - Save these parts
    - Delete old interval
    - Insert saved parts

    Core concept:
        REMOVE = CUT THE INTERVAL AND KEEP LEFTOVERS

    Picture:
        [10--------------40)
              remove [18----25)

        result:
        [10----18)    [25----40)
    */
    void removeRange(int left, int right) {

        // Find first interval whose start >= left
        auto it = mp.lower_bound(left);

        // Maybe previous interval overlaps with left
        // Example:
        //   [5----15)
        // remove(10,12)
        // prev.second = 15 > 10 -> overlap
        if(it != mp.begin() && prev(it)->second > left) {
            it = prev(it);
        }

        // Will store remaining safe pieces
        vector<pair<int,int>> todo;

        // Process all overlapping intervals
        while(it != mp.end() && it->first < right) {

            int a = it->first;
            int b = it->second;

            /*
            Current interval = [a, b)
            Remove interval  = [left, right)

            We CUT:

                [a -------- left -------- right -------- b)

            Safe parts:
                Left  part -> [a, left)
                Right part -> [right, b)
            */

            // -------- LEFT SAFE PART --------
            // If a < left, means something exists before left
            if(a < left) {
                // Keep [a, left)
                todo.push_back({a, left});
            }

            // -------- RIGHT SAFE PART --------
            // If b > right, means something exists after right
            if(b > right) {
                // Keep [right, b)
                todo.push_back({right, b});
            }

            // Delete old interval [a,b)
            it = mp.erase(it);
        }

        // Insert remaining safe pieces back
        for(auto &p : todo) {
            mp[p.first] = p.second;
        }
    }
};

/*
===========================
 IMPORTANT NOTES TO REMEMBER
===========================

1) We never store numbers, only intervals.
2) addRange -> merge overlaps.
3) queryRange -> check full coverage.
4) removeRange -> cut and keep leftovers.
5) erase(it) returns next iterator (safe looping).
6) Always imagine number line while coding.

===========================
 REMOVE RANGE MENTAL MODEL
===========================

Current interval: [a ----- b)
Remove interval :      [l --- r)

Check:
- If a < l -> keep [a,l)
- If b > r -> keep [r,b)
- Delete [a,b)

===========================
 INTERVIEW ONE LINER
===========================

"I maintain sorted non-overlapping intervals. 
Add merges overlaps, query checks coverage, 
and remove splits intervals into leftover parts."

===========================
*/
