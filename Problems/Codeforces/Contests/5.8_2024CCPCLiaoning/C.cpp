#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 2);
    vector<ll> w(n + 2);
    w[1] = 2200;
    for(int i = 2; i <= n + 1; i++) {
        int fa;
        cin >> fa >> w[i];
        adj[fa + 1].push_back(i);
        adj[i].push_back(fa + 1);
    }
    vector<ll> a, b;
    bool ok = true;
    auto dfs = [&](this auto &&self, int u, int fa) -> ll {
        ll tot = 0, son = 0;
        for(int v : adj[u]) {
            if(v == fa) continue;
            son += 1;
            tot += self(v, u);
        }   
        if(son == 0) {
            tot += w[u];
        } else if(u != 1) {
            a.push_back(tot);
            b.push_back(w[u]);
        } else {
            ok = tot <= w[u];
        }
        return tot;
    };
    dfs(1, 0);
    if(!ok) {
        cout << "NO\n";
        return;
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for(int i = 0; i < a.size(); i++) {
        if(a[i] > b[i]) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
