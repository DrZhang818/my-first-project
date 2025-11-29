#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    int minimumDistance(vector<int>& a) {
        int n = a.size();
        vector<PII> las(n + 1, {-1, -1});
        int ans = inf;
        for(int z = 0; z < n; z++) {
            auto [x, y] = las[a[z]];
            if(x != -1) {
                ans = min(ans, y - x + z - y + z - x);
            }
            las[a[z]] = {y, z};
        }
        return ans == inf ? -1 : ans;
    }
};