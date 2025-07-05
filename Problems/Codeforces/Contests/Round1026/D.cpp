#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000007;

//https://codeforces.com/contest/2110/problem/D
/*
    最短路 || 二分 || 贪心 || DP
    题意: 
        给定一个N个节点M条边的有向带权图, 保证每条边都是从编号小的节点指向编号大的节点
        每个节点i有点权w[i], 表示在该点可以收集0~w[i]点能量
        你需要从节点1走到节点N, 只有当能量大于等于边权时候你才能经过这条边, 经过后能量不改变
        初始时你的能量为0, 求解到达节点N时的能量最小是多少? 无法到达输出-1
        范围: n∈[2,2e5], m∈[0,3e5], w∈[0,1e9], 边权∈[1,1e9]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先观察题目性质, 我们发现答案明显有单调性, 这启发我们可以从二分答案角度切入问题
        假设我们钦定答案是x, 如何检查x是否合法呢?
        由于能量不会衰减, 这意味着我们在任意时刻存储的能量不能超过x
        而显然存储的能量越大越有机会到达节点N, 并且越早越好, 这样有机会经过更多的边
        因此我们就得到了一个贪心策略: 最大化到达每个节点时的能量, 并且不能超过x, 以这个值
        向它的邻居扩散
        这件事显然可以用dijkstra来完成, 但本题的边都是从编号小的指向编号大的, 这意味着得到的
        图必然是个有向无环图, 并且拓扑序就是从小到大, 这时可以直接沿着拓扑序做DP来完成转移
        dp时间复杂度为O(N + M), 比dijk更为高效
*/
struct info {
    int v, w;
};
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<vector<info>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
    auto ck = [&](int x) -> bool {
        vector<int> dp(n + 1, -1);
        dp[1] = min(x, a[1]);
        for(int u = 1; u <= n; u++) {
            for(auto [v, w] : adj[u]) {
                if(w <= dp[u]) {
                    dp[v] = max(dp[v], min(x, dp[u] + a[v]));
                }
            }
        }
        return dp[n] != -1;
    };
    int l = 0, r = inf;
    while(l + 1 < r) {
        int mid = l + r >> 1;
        if(ck(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    if(r == inf) {
        cout << -1 << "\n";
    } else {
        cout << r << "\n";
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
