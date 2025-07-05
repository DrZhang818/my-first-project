#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

class Solution {
public:
    int countPartitions(vector<int>& a, int k) {
        int n = a.size(), l = 1;
        a.insert(a.begin(), 0);
        deque<int> mn, mx;
        vector<int> dp(n + 1);
        dp[0] = 1;
        ll sum = 0;
        for(int i = 1; i <= n; i++) {
            int x = a[i];
            sum += dp[i - 1];
            while(!mn.empty() && x <= a[mn.back()]) {
                mn.pop_back();
            }
            mn.push_back(i);
            while(!mx.empty() && x >= a[mx.back()]) {
                mx.pop_back();
            }
            mx.push_back(i);
            while(a[mx.front()] - a[mn.front()] > k) {
                sum -= dp[l - 1];
                l++;
                if(mn.front() < l) mn.pop_front();
                if(mx.front() < l) mx.pop_front();
            }
            dp[i] = sum % MOD;
        }
        return dp[n];
    }
};


// class Solution {
// public:
//     int countPartitions(vector<int>& a, int k) {
//         int n = a.size();
//         a.insert(a.begin(), 0);
//         vector<ll> dp(n + 1), pre(n + 1);
//         dp[0] = pre[0] = 1;
//         map<int,int> mp;
//         int l = 1;
//         for(int i = 1; i <= n; i++) {
//             mp[a[i]]++;
//             while(mp.rbegin()->first - mp.begin()->first > k) {
//                 if(--mp[a[l]] == 0) {
//                     mp.erase(a[l]);
//                 }
//                 l++;
//             }
//             dp[i] = (pre[i - 1] - (l == 1 ? 0 : pre[l - 2]) + MOD) % MOD;
//             pre[i] = (pre[i - 1] + dp[i]) % MOD;
//         }
//     }
// };