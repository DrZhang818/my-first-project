#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    string s;
    cin >> s;
    
    s = "#" + s;
    vector<int> d(n + 1);
    for(int i = 2; i <= n; i++) {
        d[i] = s[i] != s[i - 1];
    }

    auto get = [&](int p) -> vector<int> {
        vector<int> val;
        val.reserve(n / k);
        for(int i = p; i <= n; i += k) {
            val.push_back(d[i]);
        }
        int sz = val.size();
        int V = min(m, sz);
        vector<array<int,2>> dp(V + 1, {-inf,-inf});
        if(p == 1) {
            for(int j = 0; j <= V; j++) {
                dp[j][0] = dp[j][1] = 0;
            }
        } else {
            for(int j = 0; j <= V; j++) {
                dp[j][0] = 0;
                dp[j][1] = 1;
            }            
        }

        bool ok = p % k == (n + 1) % k;
    
        for(int i = 1; i < sz; i++) {
            int x = val[i];
            vector<array<int,2>> ndp(V + 1, {-inf,-inf});
            for(int j = 0; j <= V; j++) {
                ndp[j][0] = dp[j][val[i - 1]];
                ndp[j][1] = dp[j][val[i - 1]] + 1;
                if(j > 0) {
                    ndp[j][0] = max(ndp[j][0], dp[j - 1][val[i - 1] ^ 1] + 1);
                    ndp[j][1] = max(ndp[j][1], dp[j - 1][val[i - 1] ^ 1]);
                }
            }
            swap(dp, ndp);
        }

        if(ok) {
            auto ndp = dp;
            int x = val[sz - 1];
            for(int j = 1; j <= V; j++) {
                ndp[j][x] = max(ndp[j][x], dp[j - 1][x ^ 1]);
            }
            swap(dp, ndp);
        }

        vector<int> res(V + 1);
        for(int j = 0; j <= V; j++) {
            res[j] = dp[j][val[sz - 1]];
        }

        return res;
    };

    vector<int> f(m + 1);
    for(int p = 1; p <= k; p++) {
        auto g = get(p);
        vector<int> nf(m + 1);
        for(int i = 0; i <= m; i++) {
            for(int j = 0; j < g.size() && i + j <= m; j++) {
                nf[i + j] = max(nf[i + j], f[i] + g[j]);
            }
        }
        swap(f, nf);
    }
    cout << f[m] + 1 << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
