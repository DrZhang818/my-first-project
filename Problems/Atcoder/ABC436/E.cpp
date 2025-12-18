#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;


void solve() {  
    int n;
    cin >> n;
    vector<int> p(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    vector<int> vis(n + 1);
    auto dfs = [&](this auto &&self, int u) {
        if(vis[u]) return 0;
        vis[u] = 1;
        return 1 + self(p[u]);
    };
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        if(!vis[i]) {
            int v = dfs(i);
            ans += 1LL * v * (v - 1) / 2;
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
