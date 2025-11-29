#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr int MOD = 1000000007;
constexpr int N = 100000;

int pow_10[N + 1];
auto init = []() {
    pow_10[0] = 1;
    for(int i = 1; i <= N; i++) {
        pow_10[i] = 1LL * pow_10[i - 1] * 10 % MOD;
    }
    return 1;
} ();

class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& Q) {
        int n = s.size();
        s = "#" + s;
        vector<int> pre(n + 1), sum(n + 1), cnt(n + 1); 
        for(int i = 1; i <= n; i++) {
            int x = s[i] - '0';
            pre[i] = pre[i - 1];
            sum[i] = sum[i - 1];
            cnt[i] = cnt[i - 1];
            if(x > 0) {
                pre[i] = (1LL * pre[i - 1] * 10 + x) % MOD;
                sum[i] += x;
                cnt[i] += 1;
            }
        }
        int q = Q.size();
        vector<int> res(q);
        for(int i = 0; i < q; i++) {
            int l = Q[i][0], r = Q[i][1] + 1;
            int ans = ((pre[r] - 1LL * pre[l] * pow_10[cnt[r] - cnt[l]] % MOD) % MOD + MOD) % MOD;
            ans = 1LL * ans * (sum[r] - sum[l]) % MOD;
            res[i] = ans;
        } 
        return res;
    }
};