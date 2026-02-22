#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void fwhq(vector<ll>& a, auto combine) {
    int n = a.size();
    for(int i = 1; i < n; i <<= 1) {
        for(int j = 0; j < n; j += i << 1) {
            for(int k = 0; k < i; k++) {
                combine(a[j + k], a[j + i + k]);
            }
        }
    }
}

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            char c;
            cin >> c;
            a[i][j] = c - '0';
        }
    }

    const int N = 1 << n;

    vector<ll> cnt(N);
    for(int j = 0; j < m; j++) {
        int s = 0;
        for(int i = 0; i < n; i++) {
            s |= a[i][j] << i;
        }
        cnt[s]++;
    }

    vector<ll> w(N);
    for(int i = 0; i < N; i++) {
        int t = __builtin_popcount(i);
        w[i] = min(t, n - t);
    }

    auto f = [](auto& x, auto &y) {
        auto u = x, v = y;
        x = u + v;
        y = u - v;
    };

    auto g = [](auto& x, auto& y) {
        auto u = x, v = y;
        x = (u + v) / 2;
        y = (u - v) / 2;
    };

    fwhq(cnt, f);
    fwhq(w, f);

    vector<ll> dp(N);
    for(int s = 0; s < N; s++) {
        dp[s] = w[s] * cnt[s];
    }

    fwhq(dp, g);

    ll ans = *min_element(dp.begin(), dp.end());

    cout << ans << "\n";
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
