#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, k;
    cin >> n >> k;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> d(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> d[i];
    }
    vector<vector<int>> adj(2 * n + 1);
    for(int i = 1; i <= n; i++) {
        for(int j = i - 1; j >= 1; j--) {
            ll dis = a[i] - a[j];
            if((dis + d[i]) % k == d[j]) {
                adj[i].push_back(j + n);   
                break;             
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            ll dis = a[j] - a[i];
            if((dis + d[i]) % k == d[j]) {
                adj[i + n].push_back(j);
                break;
            }
        }
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

    int q;
    cin >> q;
    while(q--) {
        ll x;
        cin >> x;
        bool ok = true;
        int i = lower_bound(a.begin() + 1, a.end(), x) - a.begin();
        for(; i <= n; i++) {
            ll dis = a[i] - x;
            if(dis % k == d[i]) {
                if(c[scc[i]] > 1) {
                    ok = false;
                }
                break;
            }
        }
        if(ok) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
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
