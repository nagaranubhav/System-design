#include <vector>     
#include <algorithm>  
#include <cmath>
using namespace std;

class Solution {
public:
    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
        
        // This will store angles of each point relative to location
        vector<double> angles;
        
        // Count points that are exactly at the same location
        int sameLocation = 0;

        // ---------- STEP 1: Convert points to angles ----------
        for (auto &p : points) {
            
            int dx = p[0] - location[0];  
            int dy = p[1] - location[1];

            // If point is exactly at location, it is always visible
            if (dx == 0 && dy == 0) {
                sameLocation++;
                continue;
            }

            // atan2 gives direction of (dx, dy)
            // It returns radians, so convert to degrees
            double a = atan2(dy, dx) * 180.0 / M_PI;

            angles.push_back(a);
        }

        // ---------- STEP 2: Sort angles ----------
        // Sorting makes close directions come together
        sort(angles.begin(), angles.end());

        int n = angles.size();

        // ---------- STEP 3: Duplicate for circular window ----------
        // Circle → line conversion
        // Every angle is added again with +360
        for (int i = 0; i < n; i++) {
            angles.push_back(angles[i] + 360);
        }

        // ---------- STEP 4: Sliding Window ----------
        int l = 0;
        int maxVisible = 0;

        for (int r = 0; r < angles.size(); r++) {

            // If window becomes invalid, shrink from left
            while (angles[r] - angles[l] > angle) {
                l++;
            }

            // Update max window size
            maxVisible = max(maxVisible, r - l + 1);
        }

        // Same location points are always visible
        return maxVisible + sameLocation;
    }
};
