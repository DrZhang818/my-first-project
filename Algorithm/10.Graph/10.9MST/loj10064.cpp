#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://loj.ac/p/10064
/*
    最短路 || 生成树
    题意:
        给定一个N个节点M条边的无向有权图G, 记D[i]表示第i个节点到第1个节点的最短路
        一个G的生成树被认为是合法的, 当且仅当生成树中求得的D数组与原图的G数组相同
        求G的合法生成树数量, 结果对2^31 - 1取模
        范围: N∈[1,1000], M∈[1,N(N-1)/2], 边权∈[1,200]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        首先观察题目性质, 由于边权为正, 且涉及单源最短路, 我们自然往dijk上思考
        由树的性质可知, 任意两个节点只有一条路径
        则对于有向边(u,v,w), 必有D[v] = D[u] + w
        这个重要性质告诉我们, 在保证D'[u] = D[u]的前提下, 能否连接(u,v), 取决于
        D'[v] = D'[u] + w是否等于D[v], 如果等于, 则说明节点v的父节点可以设置为u
        我们最终要做的计数工作, 就是把每个节点可以设置的父节点数量累乘起来
        为什么这样是对的? 因为我们保证了以下两个事情:
        (1)每个节点都一定能通过父节点到达节点1, 因为生成树是连通的, 不需要管父节点
           是怎么选择父节点的父节点的, 这样就保证了各个节点的选择是互不影响的
           有了这个性质, 我们就可以直接应用乘法原理
        (2)由于边权为正, 意味着不可能出现互为父子的选择, 这意味着我们给节点2~N
           分配好父节点后, 形成的一定是一个生成树
        下面思考如何实现, 我们可以从节点1出发利用dijk来扩展子节点
        如果我们发现cnt[u] = 0, 意味着这是第一次访问该节点, 由dijk性质可知这一定是
        节点u到节点1的一个最短路, 此时把dist设置为w, 并从该节点向外扩展子节点, 如果
        w + nw <= dist[v]表示该节点有望成为v的父节点, 那么就把{v,w+nw}入堆
        如果cnt[u] >= 1, 意味着已经从该节点扩展过一次了, 此时无需再从该节点出发扩展,
        只需要判断w是否等于dist[u], 如果等于, 代表找到了u的一个新的父节点
*/

const ll MOD = (1LL << 31) - 1;
int n, m;
struct info {
    int v, w;
    friend bool operator < (const info &a, const info &b) {
        return a.w > b.w;
    }
};
void solve() {
    cin >> n >> m;  
    vector<vector<info>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    priority_queue<info> q;
    q.push({1, 0});
    vector<int> cnt(n + 1), dist(n + 1, inf);
    while(!q.empty()) {
        auto [u,w] = q.top(); q.pop();
        if(!cnt[u]) {
            dist[u] = w, cnt[u]++;
            for(auto [v,nw] : adj[u]) {
                if(w + nw <= dist[v]) {
                    dist[v] = w + nw;
                    q.push({v, w + nw});
                }
            }
        } else if(w == dist[u]) {
            cnt[u]++;
        }
    }

    ll ans = 1;
    for(int i = 2; i <= n; i++) {
        ans = ans * cnt[i] % MOD;
    }
    cout << ans << "\n";
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
