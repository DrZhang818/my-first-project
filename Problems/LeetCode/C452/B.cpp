#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


class Solution {
public:
    vector<vector<int>> minAbsDiff(vector<vector<int>>& a, int k) {
        int n = a.size(), m = a[0].size();
        vector ans(n - k + 1, vector<int>(m - k + 1));
        for(int i = 0; i < n - k + 1; i++) {
            for(int j = 0; j < m - k + 1; j++) {
                vector<int> cur;
                for(int u = i; u < i + k; u++) {
                    for(int v = j; v < j + k; v++) {
                        cur.push_back(a[u][v]);
                    }
                }
                sort(cur.begin(), cur.end());
                int res = inf;
                for(int o = 1; o < k * k; o++) {
                    if(cur[o] != cur[o - 1]) {
                        res = min(res, cur[o] - cur[o - 1]);
                    }
                }
                ans[i][j] = res == inf ? 0 : res;
            }
        }
        return ans;
    }
};