#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

constexpr int MOD = 1000000007;

void solve() {  
    int n, m;
    cin >> n >> m;
    set<int> r, c;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        r.insert(x);
    }
    for(int j = 1; j <= m; j++) {
        int x;
        cin >> x;
        c.insert(x);
    }
    if(r.size() < n || c.size() < m) {
        cout << 0 << "\n";
        return;
    }
    int ans = 1;
    for(int x = n * m; x >= 1; x--) {
        auto it1 = r.find(x);
        auto it2 = c.find(x);
        if(it1 != r.end() && it2 != c.end()) {
            r.erase(x);
            c.erase(x);
        } else if(it1 != r.end()) {
            r.erase(x);
            ans = 1LL * ans * (m - c.size()) % MOD;
        } else if(it2 != c.end()) {
            c.erase(x);
            ans = 1LL * ans * (n - r.size()) % MOD;
        } else {
            ll y = x;
            y -= (n - r.size()) * c.size();
            y -= (m - c.size()) * r.size();
            y -= r.size() * c.size();
            y = (y % MOD + MOD) % MOD;
            ans = 1LL * ans * y % MOD;
        }
        if(ans == 0) {
            break;
        }
    }
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
