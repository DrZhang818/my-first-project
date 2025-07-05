#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
constexpr int inf = 1000000000;


class Solution {
public:
    int minCost(vector<int>& a) {
        int n = a.size();
        vector memo(n + 1, vector<int>(n + 1, -1));
        auto dfs = [&](auto &&dfs, int i, int j) -> int {
            if(j == n - 1) return max(a[i], a[j]);
            if(j >= n && i < n) return a[i];
            if(i >= n) return 0;
            int &res = memo[i][j];
            if(res != -1) return res;
            int ans = 0;
            ans = max(ans, dfs(dfs, j + 1, j + 2) + max(a[i], a[j]));
            ans = max(ans, dfs(dfs, i, j + 2) + max(a[j], a[j + 1]));
            ans = max(ans, dfs(dfs, j, j + 2) + max(a[i], a[j + 1]));
            return res = ans;
        };
        return dfs(dfs, 0, 1);
    }
};