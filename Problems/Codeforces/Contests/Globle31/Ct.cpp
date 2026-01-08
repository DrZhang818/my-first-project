#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

ll dp[300][600][300];

ll solve(int n, int k) {  
    if(k & 1) {
        return 1LL * n * k;
    }
    vector<int> a(k, n), b {};
    for(int i = __lg(n) + 1; i >= 0; i--) {
        if(a.empty()) {
            if(n >> i & 1) {
                for(int j = 0; j < b.size() - 1; j++) {
                    b[j] |= 1 << i;
                }
                b.back() ^= (1 << i);
            } else {
                for(int j = 0; j < b.size(); j += 2) {
                    if(j + 1 < b.size()) {
                        b[j] |= 1 << i;
                        b[j + 1] |= 1 << i;
                    }
                }
            }
            continue;
        }

        if(n >> i & 1) {
            a.pop_back();
            for(int &x : b) {
                x |= 1 << i;
            }
            b.push_back(n ^ (1 << i));
        } else {
            for(int j = 0; j < b.size(); j += 2) {
                if(j + 1 < b.size()) {
                    b[j] |= 1 << i;
                    b[j + 1] |= 1 << i;
                }
            }
        }
    }
    ll res = 0;
    for(int i = 0; i < a.size(); i++) {
        res += a[i];
    }
    for(int i = 0; i < b.size(); i++) {
        res += b[i];
    }
    return res;
}

ll brute_force(int n, int tar, int k) {  
    if(k == 0) {
        return tar == 0 ? 0 : -inf;
    }
    if(dp[n][tar][k]) {
        return dp[n][tar][k];
    }
    ll res = 0;
    for(int i = 0; i <= n; i++) {
        res = max(res, i + brute_force(n, tar ^ i, k - 1));
    }
    return dp[n][tar][k] = res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int n = 1; n <= 300; n++) {
        for(int k = 1; k <= 300; k++) {
            if(brute_force(n, n, k) != solve(n, k)) {
                cout << n << " " << k << " : " << brute_force(n, n, k) << " " << solve(n, k) << "\n";
            }
        }
    }

    return 0;
}
