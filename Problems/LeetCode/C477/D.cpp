#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr int MOD = 1000000007;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

int pow_2[100001];
auto init = []() {
    pow_2[0] = 1;
    for(int i = 1; i <= 100000; i++) {
        pow_2[i] = 1LL * pow_2[i - 1] * 2 % MOD;
    }
    return 1;
} ();

class Solution {
public:
    int countEffective(vector<int>& a) {
        int _or = reduce(a.begin(), a.end(), 0, bit_or<>());
        int w = bit_width((uint32_t)_or);
        vector<int> dp(1 << w);
        for(int x : a) {
            dp[x]++;
        }
        for(int i = 0; i < w; i++) {
            for(int s = 0; s < 1 << w; s++) {
                if(s >> i & 1) {
                    dp[s] += dp[s ^ (1 << i)];
                }
            }
        }
        int ans = 0;
        int S = __builtin_popcount(_or);
        for(int s = _or; ; s = (s - 1) & _or) {
            int T = __builtin_popcount(s);
            if((S - T) & 1) {
                add(ans, MOD - pow_2[dp[s]]);
            } else {
                add(ans, pow_2[dp[s]]);
            }
            if(s == 0) {
                break;
            }
        }
        ans = MOD - ans;
        add(ans, pow_2[int(a.size())]);
        return ans;
    }
};