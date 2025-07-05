#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://acm.hdu.edu.cn/showproblem.php?pid=4115
/*
    2-SAT || SCC缩点
    题意:
        Alice和Bob在玩石头剪刀布游戏, 游戏一共会进行N轮, Alice可以准确预测出Bob每轮的出法,
        这导致游戏严重失衡。为了限制Alice的能力, Bob为Alice设定了M条约束条件, 每条约束条件
        由(u,v,x)组成, 若k=0, 则Alice在第u轮和第v轮必须出相同手势, 若k=1, 则必须出不同手势
        若Alice在某轮输掉了, 或者违反了某条约束条件, 就认为Alice输了, 否则Alice获胜
        判断Alice是否可以获胜
        范围: N∈[1,1e4], M∈[1,1e4]        

*/
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> adj(2 * n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v, x;
        cin >> u >> v >> x;
        if(a[u] > a[v]) swap(u, v);
        if(x == 0) {
            if(a[u] == a[v]) {
                adj[u].push_back(v);
                adj[u + n].push_back(v + n);
                adj[v].push_back(u);
                adj[v + n].push_back(u + n);
            } else if(a[u] == 1 && a[v] == 3) {
                adj[u + n].push_back(u);
                adj[v].push_back(v + n);
            } else {
                adj[u].push_back(u + n);
                adj[v + n].push_back(v);
            }
        } else {
            if(a[u] == a[v]) {
                adj[u].push_back(v + n);
                adj[v].push_back(u + n);
                adj[u + n].push_back(v);
                adj[v + n].push_back(u);
            } else if(a[u] == 1 && a[v] == 3) {
                adj[u].push_back(v);
                adj[v + n].push_back(u + n);
            } else {
                adj[u + n].push_back(v + n);
                adj[v].push_back(u);
            }
        }
    }
    vector<int> dfn(2 * n + 1), low(2 * n + 1), scc(2 * n + 1);
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
    for(int i = 1; i <= 2 * n; i++) {
        if(!dfn[i]) {
            dfs(i);
        }
    }
    for(int i = 1; i <= n; i++) {
        if(scc[i] == scc[i + n]) {
            cout << "no\n";
            return;
        }
    }
    cout << "yes\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    for(int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}
