#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://leetcode.cn/problems/inverse-coin-change/description/
class Solution {
public:
    vector<int> findCoins(vector<int>& a) {
        int n = a.size();
        a.insert(a.begin(), 0);
        vector<ll> dp(n + 1);
        vector<int> ans;
        dp[0] = 1;
        for(int i = 1; i <= n; i++) {
            if(dp[i] == a[i] - 1) {
                for(int j = i; j <= n; j++) {
                    dp[j] += dp[j - i];
                }
                ans.push_back(i);
            } else if(dp[i] != a[i]) {
                return {};
            }
        }
        return ans;
    }
};