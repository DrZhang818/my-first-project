#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://leetcode.cn/problems/minimum-operations-to-make-elements-within-k-subarrays-equal/description/
/*
    DP || 对顶set

*/
constexpr ll inf = 1e18;
class Solution {
public:
    multiset<ll> st1, st2;
    ll s1 = 0, s2 = 0;
    void adjust() {
        int sz = st1.size() + st2.size();
        int a = sz / 2, b = sz - a;
        while(st1.size() < a) {
            ll t = *(st2.begin());
            st1.insert(t), s1 += t;
            st2.erase(st2.begin()), s2 -= t;
        }
        while(st2.size() < b) {
            ll t = *prev(st1.end());
            st2.insert(t), s2 += t;
            st1.erase(prev(st1.end())), s1 -= t;
        }
    }
    void add(ll x) {
        if(!st2.empty() && x >= *(st2.begin())) st2.insert(x), s2 += x;
        else st1.insert(x), s1 += x;
        adjust();
    }
    void del(ll x) {
        auto it = st1.find(x);
        if(it != st1.end()) st1.erase(it), s1 -= x;
        else st2.erase(st2.find(x)), s2 -= x;
        adjust();
    }
    ll query() {
        int mid = *(st2.begin());
        return (st1.size() * mid - s1) + (s2 - st2.size() * mid);
    }
    ll minOperations(vector<int>& a, int x, int k) {
        int n = a.size();
        a.insert(a.begin(), 0);
        vector dp(n + 1, vector<ll>(k + 1, inf));
        for(int i = 0; i <= n; i++) dp[i][0] = 0;
        for(int i = 1; i <= n; i++) {
            add(a[i]);
            if(i > x) del(a[i - x]); 
            for(int j = 1; j <= k; j++) {
                if(i >= x) dp[i][j] = min(dp[i - 1][j], dp[i - x][j - 1] + query());
            }
        }
        return dp[n][k];
    }
};
