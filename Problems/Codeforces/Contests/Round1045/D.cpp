#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2134/problem/D
/*
    构造
    题意:
        给定一棵N个顶点的树, 你可以进行以下操作:
        op: 选出三个不同的顶点a,b,c, 其中b直接连接着a和c
            然后, 对于b的每个邻居d(不包括a和c), 把边b-d删除, 改为直接连接d-c
        你需要用最少的操作把树变成一条直链, 可以证明一定可以做到
        你只需要输出第一步操作, 如果树已经是一条链, 输出-1
        范围: N∈[1,2e5]
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        首先观察题目性质, 

*/
void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    bool ok = true;
    for(int i = 1; i <= n; i++) {
        if(adj[i].size() > 2) {
            ok = false;
            break;
        }
    }
    if(ok) {
        cout << -1 << "\n";
        return;
    }
    int mx = 0, x = 1, y;
    vector<int> p(n + 1), son(n + 1), dep(n + 1);
    auto dfs = [&](this auto &&self, int u, int fa, int d, int &o) -> void {
        p[u] = fa;
        dep[u] = d;
        if(d > mx) {
            mx = d;
            o = u;
        }
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(v, u, d + 1, o);
        }
    };
    dfs(1, 0, 0, x);
    mx = 0, y = x;
    dfs(x, 0, 0, y);
    int pre = 0;
    for(int o = y; o; o = p[o]) {
        son[o] = pre;
        if(adj[o].size() >= 3) {
            int a = pre, b = o;
            for(int c : adj[o]) {
                if(c != a && c != p[o]) {
                    cout << a << " " << b << " " << c << "\n";
                    return;
                }
            }
        }
        pre = o;
    }
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
