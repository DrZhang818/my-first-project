#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2126/problem/F
/*
    数据结构 || 思维
    题意:
        给定一棵N个节点的树, 每个节点的初始颜色为a[i], 每条边有属性c[i]
        当边(u,v,c)满足a[u] = a[v]时, 其边权为0, 否则边权为c[i]
        接下来有Q次操作, 每次操作为:
        op: 给定u,x, 将顶点u重新染色为x
        操作结束后, 回答当前树中所有边的边权总和
        注意: 操作具有持久性, 即后续操作基于前次染色结果
        范围: N∈[1,2e5], Q∈[1,2e5], a[i]∈[1,n], c[i]∈[1,1e9], x∈[1,n]
    关键思考:
        本题为数据结构类题目, 需要读清题意, 选用合适的算法和数据结构维护题目信息, 回答询问
        我们最直接的思路是, 每个点维护一个map, 记录其颜色为s的邻居节点的边权总和
        这样的问题在于, 如果我们要修改点u
        那么我们需要将u的所有邻居节点v的map都进行修改, 更新u的最新颜色a[u]
        这样单次操作的时间复杂度就是O(deg[u])的
        考虑菊花图, max(deg[u]) = n - 1, 那么时间复杂度就是O(q * n), 超时
        我们发现, 实时维护每个邻居节点这件事是无法做到的, 因此考虑树上的Trick
        我们把边权转化为点权, 把无根树转化成有根树
        每个点的map只维护其儿子节点的信息
        这样, 每次修改点u时, 只有fa[u]的map需要更改, 时间复杂度是O(logn)
        同时我们需要一个sum数组, sum[u]记录u的儿子节点的属性总和
        这样就可以高效的利用容斥来维护答案
*/
struct info {
    int v, w;
};
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<vector<info>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    vector<int> fa(n + 1);
    vector<int> w(n + 1);
    auto dfs = [&](this auto &&self, int u) -> void {
        for(auto [v, ww] : adj[u]) {
            if(v == fa[u]) continue;
            fa[v] = u;
            w[v] = ww;
            self(v);
        }
    };
    dfs(1);
    ll ans = 0;
    vector<ll> sum(n + 1);
    vector<map<int,ll>> mp(n + 1);
    for(int i = 2; i <= n; i++) {
        if(a[i] != a[fa[i]]) {
            ans += w[i];
        }
        sum[fa[i]] += w[i];
        mp[fa[i]][a[i]] += w[i];
    }
    while(q--) {
        int u, x;
        cin >> u >> x;
        ans -= sum[u];
        if(mp[u].contains(a[u])) {
            ans += mp[u][a[u]];
        }
        if(u != 1) {
            if(a[u] != a[fa[u]]) {
                ans -= w[u];
            }
            if((mp[fa[u]][a[u]] -= w[u]) == 0) {
                mp[fa[u]].erase(a[u]);
            }
        }
        a[u] = x;
        if(u != 1) {
            if(a[u] != a[fa[u]]) {
                ans += w[u];
            }
            mp[fa[u]][a[u]] += w[u];
        }
        ans += sum[u];
        if(mp[u].contains(a[u])) {
            ans -= mp[u][a[u]];
        }
        cout << ans << "\n";
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
