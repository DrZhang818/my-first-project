#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://leetcode.cn/problems/partition-to-k-equal-sum-subsets/
/*
    状压DP
    
*/
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& a, int k) {
        int n = a.size();
        int tar = accumulate(a.begin(), a.end(), 0);
        if(tar % k) return false;
        tar /= k;
        sort(a.rbegin(), a.rend());
        vector<int> memo(1 << n, -1);
        auto dfs = [&](this auto&& dfs, int msk, int len) -> bool {
            if(msk == (1 << n) - 1) return len == tar;
            if(len > tar) return false;
            if(len == tar) dfs(msk, 0);
            int &res = memo[msk];
            if(res != -1) return res;
            res = 0;
            for(int i = 0; i < n; i++){
                if((msk & (1 << i)) == 0) {
                    res |= dfs(msk | (1 << i), len + a[i]);
                    if(res == 1) break;
                }
            }
            return res;
        };
        return dfs(0, 0);
    }
};