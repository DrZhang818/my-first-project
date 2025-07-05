#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int n;
bool work(vector<vector<int>> &a, int k) {
    vector<vector<int>> adj(2 * n);
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            int x = (a[i][j] >> k & 1);
            if(i % 2 == 1 && j % 2 == 1) {
                if(x == 0) {
                    adj[i + n].push_back(i);
                    adj[j + n].push_back(j);
                } else {
                    adj[i].push_back(j + n);
                    adj[j].push_back(i + n);
                }
            } else if(i % 2 == 0 && j % 2 == 0) {
                if(x == 0) {
                    adj[i + n].push_back(j);
                    adj[j + n].push_back(i);
                } else {
                    adj[i].push_back(i + n);
                    adj[j].push_back(j + n);
                }
            } else {
                if(x == 0) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                    adj[i + n].push_back(j + n);
                    adj[j + n].push_back(i + n);
                } else {
                    adj[i].push_back(j + n);
                    adj[j].push_back(i + n);
                    adj[i + n].push_back(j);
                    adj[j + n].push_back(i);
                }
            }
        }
    }
    vector<int> dfn(2 * n), low(2 * n), scc(2 * n);
    int timer = 0, cnt = 0;
    stack<int> stk;
    function<void(int)> dfs = [&](int u) -> void {
        dfn[u] = low[u] = ++timer;
        stk.push(u);
        for(int v : adj[u]) {
            if(!dfn[v]) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if(!scc[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if(low[u] == dfn[u]) {
            ++cnt;
            while(1) {
                int v = stk.top(); stk.pop();
                scc[v] = cnt;
                if(v == u) break;
            }
        }
    };
    for(int i = 0; i < 2 * n; i++) {
        if(!dfn[i]) {
            dfs(i);
        }
    }
    for(int i = 0; i < n; i++) {
        if(scc[i] == scc[i + n]) {
            return false;
        }
    }
    return true;
}
void solve() {
    vector<vector<int>> a(n, vector<int>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    for(int i = 0; i < 32; i++) {
        if(!work(a, i)) {
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

    while(cin >> n) {
        solve();
    }
    return 0;
}
