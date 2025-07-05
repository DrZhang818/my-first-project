#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://leetcode.cn/problems/path-existence-queries-in-a-graph-ii/
class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& a, int k, vector<vector<int>>& Q) {
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), [&](auto &x, auto &y) {
            return a[x] < a[y];
        });
        sort(a.begin(), a.end());
        const int N = log2(n);
        vector<vector<int>> dp(n, vector<int>(N + 1));
        for(int i = 0, j = 0; i < n; i++) {
            while(j < n && a[j] - a[i] <= k) j++;
            dp[i][0] = j - 1;
        }   
        for(int s = 1; s <= N; s++) {
            for(int i = 0; i < n; i++) {
                dp[i][s] = dp[dp[i][s - 1]][s - 1];
            }
        }
        vector<int> mp(n);
        for(int i = 0; i < n; i++) {
            mp[idx[i]] = i;
        }
        vector<int> ans(Q.size());
        for(int i = 0; i < Q.size(); i++) {
            int p1 = Q[i][0], p2 = Q[i][1];
            if(p1 == p2) {
                ans[i] = 0;
                continue;
            }
            p1 = mp[p1], p2 = mp[p2];
            if(p1 > p2) swap(p1, p2);
            int res = 0;
            for(int s = N; s >= 0; s--) {
                if(dp[p1][s] < p2) res += (1 << s), p1 = dp[p1][s];
            }
            if(dp[p1][0] >= p2) ans[i] = res + 1;
            else ans[i] = -1;
        }
        return ans;
    }
};