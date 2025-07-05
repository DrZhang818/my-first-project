#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<ll> d(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> d[i];
    }
    map<ll,int> mp1, mp2;
    vector<vector<int>> adj(2 * n + 1);
    for(int i = 1; i <= n; i++) {
        ll rem = (a[i] + d[i]) % k;
        if(mp1.count(rem)) {
            adj[i].push_back(mp1[rem] + n);
        }
        mp1[rem] = i;
    }
    for(int i = n; i >= 1; i--) {
        ll rem = ((d[i] - a[i]) % k + k) % k;
        if(mp2.count(rem)) {
            adj[i + n].push_back(mp2[rem]);
        }
        mp2[rem] = i;
    }
    vector<int> dfn(2 * n + 1), low(2 * n + 1), scc(2 * n + 1), c(2 * n + 1);
    int timer = 0, cnt = 0;
    stack<int> stk;
    auto dfs = [&](this auto &&self, int u) -> void {
        dfn[u] = low[u] = ++timer;
        stk.push(u);
        for(int v : adj[u]) {
            if(!dfn[v]) {
                self(v);
                low[u] = min(low[u], low[v]);
            } else if(!scc[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if(dfn[u] == low[u]) {
            ++cnt;
            while(1) {
                int v = stk.top(); stk.pop();
                scc[v] = cnt;
                c[cnt]++;
                if(v == u) break;
            }
        }
    };
    for(int i = 1; i <= n; i++) {
        if(!dfn[i]) {
            dfs(i);
        }
    }
    map<ll,set<int>> mp;
    for(int i = 1; i <= n; i++) {
        ll rem = ((a[i] - d[i]) % k + k) % k;
        mp[rem].insert(i);
    }
    int q;
    cin >> q;
    while(q--) {
        ll x, y;
        cin >> x;
        y = x % k;
        int i = lower_bound(a.begin() + 1, a.end(), x) - a.begin();
        if(mp[y].size() == 0) {
            cout << "YES\n";
        } else {
            auto it = mp[y].lower_bound(i);
            if(it == mp[y].end() || c[scc[*it]] == 1) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }

}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
