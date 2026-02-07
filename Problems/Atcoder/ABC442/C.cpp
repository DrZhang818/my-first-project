#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<int> deg(n + 1, n - 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        deg[u]--;
        deg[v]--;
    }
    for(int i = 1; i <= n; i++) {
        ll v = deg[i];
        ll res = v * (v - 1) * (v - 2) / 6;
        cout << res << " \n"[i == n];
    }
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
