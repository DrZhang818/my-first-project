#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://www.luogu.com.cn/problem/P4779
/*
    贪心 || 图论
    题意:
        给定一个N个点M条有向边的带非负权图, 现给定一个节点s
        要求计算出s到每个节点的最短路
        范围: n∈[1,1e5], m∈[1,2e5], Σwi∈[1,1e9]
    关键思考:
        本题属于决策类题目, 常用思考方式为: 暴力->贪心||DP, 常用优化手段为: 二分、前缀和、双指针、数据结构
        回想BFS求解等权最短路, 能够实现的重要原因在于: 
            从u扩散到某个v点时, 所走过的路天然是u->v的最短路, 这样从v继续扩散时
            用到的d[v]就都是最优(小)的值, 这样就贪心地从局部最优扩展到了全局最优
        因此对于有权图, 我们也尝试能否实现"所走过的路天然是u->v的最短路",
        这样每步都是最优的情况下就能扩散到全局最优解了
        具体实现时, 我们需要一个最小堆来维护下一步该处理的节点
        堆内数据为pair类型{w,v}, 表示从源点能以w的代价走到节点v
        我们每次都选择w最小的pair, 并扩散对应的v, 这保证了:
            (1)w为s->v的最短路
            (2)v扩散出去的点延续了s->v的最短路
        最关键的点在于, 如何证明w就是s->v的最短路
        可以用反证法来证明:
            假设w不是s->v的最短路
            那么就存在路径p', 使得s沿着路径p'到达v所消耗的代价w' < w
            而由于边权非负, s到达p'上任意一点的代价均 < w
            这样由最小堆性质, 在处理{w, v}之前, 一定会优先处理路径p'上的所有点
            而一旦处理完, 我们就会得到{w', v}, 由于w' < w, 仍然优先处理{w', v}
            处理完后, 再次轮到{w, v}时会发现vis[v]已经标记, 跳过处理
            这与此时正在处理{w, v}矛盾, 因此w时s->v的最短路
        当我们处理完所有的pair后, s所能到达的点的最短路就全部求解完毕
*/
constexpr int inf = 1000000000;
void solve() { 
    int n, m, s;
    cin >> n >> m >> s;
    vector<vector<PII>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
    vector<int> d(n + 1, inf);
    vector<bool> vis(n + 1, false);
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    auto dijk = [&](int s) -> void {
        d[s] = 0;
        pq.push({0, s});
        while(!pq.empty()) {
            auto [_, u] = pq.top();
            pq.pop();
            if(vis[u]) continue;
            vis[u] = true;
            for(auto [v, w] : adj[u]) {
                if(d[v] > d[u] + w) {
                    d[v] = d[u] + w;
                    pq.push({d[v], v});
                }
            }
        }
    };
    dijk(s);
    for(int i = 1; i <= n; i++) {
        cout << d[i] << " \n"[i == n];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
