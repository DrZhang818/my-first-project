#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://leetcode.cn/problems/maximum-product-of-subsequences-with-an-alternating-sum-equal-to-k/description/

class Solution {
public:
    int maxProduct(vector<int>& a, int k, int lim) {
        int ans = -1, n = a.size(), sum = 0;
        for(int i = 0; i < n; i++) sum += a[i];
        if(sum < abs(k)) return -1;
        map<tuple<int,int,int,int,int>,int> mp;
        auto dfs = [&](this auto &&dfs, int pos, int s, int m, int flag, int empty) -> void {
            if(pos == n) { 
                if(s == k && m <= lim && !empty) {
                    ans = max(ans, m); 
                    return; 
                }
            }
            if(mp[{pos, s, m, flag, empty}]) return;
            mp[{pos, s, m, flag, empty}] = 1;
            dfs(pos + 1, s, m, flag, empty);
            if(flag) dfs(pos + 1, s + a[pos], min(m * a[pos], lim + 1), !flag, 0);
            else dfs(pos + 1, s - a[pos], min(m * a[pos], lim + 1), !flag, 0);
        };
        dfs(0, 0, 1, 1, 1);
        return ans;
    }
};