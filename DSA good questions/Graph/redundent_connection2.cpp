#include<vector>
using namespace std;

class Solution {
public:
    vector<int> parentUF;

    int find(int x) {
        if (parentUF[x] == x) return x;
        return parentUF[x] = find(parentUF[x]);
    }

    bool unite(int u, int v) {
        int pu = find(u);
        int pv = find(v);
        if (pu == pv) return false;
        parentUF[pv] = pu;
        return true;
    }

    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        
        vector<int> parent(n+1, 0);
        vector<int> cand1, cand2;

        // Step 1: find two parents
        for (auto &e : edges) {
            int u = e[0], v = e[1];
            if (parent[v] == 0) {
                parent[v] = u;
            } else {
                cand1 = {parent[v], v};
                cand2 = {u, v};
                e[1] = 0; // mark invalid
            }
        }

        // Step 2: union find
        parentUF.resize(n+1);
        for (int i = 1; i <= n; i++) parentUF[i] = i;

        for (auto &e : edges) {
            if (e[1] == 0) continue;
            int u = e[0], v = e[1];

            if (!unite(u, v)) {
                if (cand1.empty()) return e;
                return cand1;
            }
        }

        return cand2;
    }
};
