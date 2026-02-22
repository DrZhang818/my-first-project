#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void chmax(ll& x, ll y) {
    if(x < y) {
        x = y;
    }
}

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<vector<ll>> a(n + 1, vector<ll>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    vector<vector<ll>> pre(n + 2, vector<ll>(m + 2));
    vector<vector<ll>> suf(n + 2, vector<ll>(m + 2));

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(i == 1 && j == 1) {
                pre[i][j] = a[i][j];
            } else if(i == 1) {
                pre[i][j] = pre[i][j - 1] + a[i][j];
            } else if(j == 1) {
                pre[i][j] = pre[i - 1][j] + a[i][j];
            } else {
                pre[i][j] = max(pre[i - 1][j], pre[i][j - 1]) + a[i][j];            
            }
        }
    }

    for(int i = n; i >= 1; i--) {
        for(int j = m; j >= 1; j--) {
            if(i == n && j == m) {
                suf[i][j] = a[i][j];
            } else if(i == n) {
                suf[i][j] = suf[i][j + 1] + a[i][j];
            } else if(j == m) {
                suf[i][j] = suf[i + 1][j] + a[i][j];
            } else {
                suf[i][j] = max(suf[i][j + 1], suf[i + 1][j]) + a[i][j];
            }
        }
    }

    vector<vector<ll>> pre_max(n + 1, vector<ll>(m + 1));
    vector<vector<ll>> suf_max(n + 1, vector<ll>(m + 1));

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            pre_max[i][j] = pre[i][j] + suf[i][j] - a[i][j];
            if(j >= 2) {
                chmax(pre_max[i][j], pre_max[i][j - 1]);
            }
        }
        for(int j = m; j >= 1; j--) {
            suf_max[i][j] = pre[i][j] + suf[i][j] - a[i][j];
            if(j < m) {
                chmax(suf_max[i][j], suf_max[i][j + 1]);
            }
        }
    }


    ll ans = numeric_limits<ll>::max();

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            ll cur = pre[i][j] + suf[i][j] - 3 * a[i][j];
            if(i + 1 <= n && j >= 2) {
                cur = max(cur, pre_max[i + 1][j - 1]);
            }
            if(i - 1 >= 1 && j + 1 <= m) {
                cur = max(cur, suf_max[i - 1][j + 1]);
            }
            ans = min(ans, cur);
        }
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
