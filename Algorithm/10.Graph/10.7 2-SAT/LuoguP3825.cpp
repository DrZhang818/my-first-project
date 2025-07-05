#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://www.luogu.com.cn/problem/P3825
/*

*/
vector<int> idx;
struct info {
    int u, v;
    char x, y;
};
vector<info> a;
int n, d, m;
string s;
vector<vector<int>> adj;
bool work(int msk) {
    for(int i = 1; i <= 2 * n; i++) {
        adj[i].clear();
    }
    for(int i = 0; i < d; i++) {
        if(msk >> i & 1) {
            s[idx[i]] = 'B';
        } else {
            s[idx[i]] = 'A';
        }
    }
    for(int i = 0; i < m; i++) {
        int u = a[i].u, v = a[i].v;
        char x = a[i].x, y = a[i].y;
        if(s[u] == x) continue;
        int f1, f2;
        if(s[u] == 'A') {
            if(x == 'B') f1 = 0;
            else f1 = 1;
        } else {
            if(x == 'A') f1 = 0;
            else f1 = 1;
        }
        if(s[v] == 'A') {
            if(y == 'B') f2 = 0;
            else f2 = 1;
        } else {
            if(y == 'A') f2 = 0;
            else f2 = 1;
        }
        if(s[v] == y) {
            adj[u + f1 * n].push_back(u + !f1 * n);
        } else {
            adj[u + f1 * n].push_back(v + f2 * n);
            adj[v + !f2 * n].push_back(u + !f1 * n);
        }
    }
    vector<int> low(2 * n + 1), dfn(2 * n + 1), scc(2 * n + 1);
    int timer = 0, cnt = 1;
    stack<int> stk;
    auto dfs = [&](auto &&dfs, int u) -> void {
        dfn[u] = low[u] = ++timer;
        stk.push(u);
        for(int v : adj[u]) {
            if(!dfn[v]) {
                dfs(dfs, v);
                low[u] = min(low[u], low[v]);
            } else if(!scc[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if(low[u] == dfn[u]) {
            while(1) {
                int v = stk.top(); stk.pop();
                scc[v] = cnt;
                if(v == u) break;
            }
            cnt++;
        }
    };
    for(int i = 1; i <= 2 * n; i++) {
        if(!dfn[i]) {
            dfs(dfs, i);
        }
    }
    vector<char> ans(n + 1);
    for(int i = 1; i <= n; i++) {
        if(scc[i] == scc[i + n]) {
            return false;
        }
        if(scc[i] < scc[i + n]) {
            if(s[i] == 'A') ans[i] = 'B';
            else ans[i] = 'A';
        } else {
            if(s[i] == 'C') ans[i] = 'B';
            else ans[i] = 'C';
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << ans[i];
    }
    cout << "\n";
    return true;
}
void solve() {
    cin >> n >> d;
    cin >> s;
    s = "#" + s;
    cin >> m;
    adj.resize(2 * n + 1);
    for(int i = 1; i <= n; i++) s[i] = toupper(s[i]);
    for(int i = 1; i <= n; i++) {
        if(s[i] == 'X') {
            idx.push_back(i);
        }
    }
    a.resize(m);
    for(int i = 0; i < m; i++) {
        cin >> a[i].u >> a[i].x >> a[i].v >> a[i].y;
    }
    for(int msk = 0; msk < 1 << d; msk++) {
        if(work(msk)) {
            return;
        }
    }
    cout << -1 << "\n";
    return;
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
