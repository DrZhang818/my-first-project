#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;
const int N = 200000;

//https://codeforces.com/contest/2127/problem/D
/*
    图论 || 组合数学 || 生成树
    题意:
        有N个房子, M座桥, 第i座桥连接房子u[i]和房子v[i](u[i] ≠ v[i]), 保证所有房子之间连通
        你需要把这N个房子排布在南岸和北岸, 并满足以下要求:
        (1)每座桥连接的两个房子分别在河的两岸
        (2)桥作为直线画出时, 彼此之间不相交
        两种排布被认为不同, 当且仅当满足以下任一条件:
        (1)存在一个房子在两种排布中分别位于不同的河岸
        (2)存在两个房子a,b, 它们在两种排布中都在同一侧, 但一种排布中a排在b前面, 而在另一种排布中
            b排在a前面
        求你有多少种不同的符合要求的排布方案, 结果对1000000007取模
        范围: N∈[2,2e5], M∈[N-1, min(N(N-1)/2, 2e5)]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        观察题目性质, 可以抽象为: 求解与图G同构的二分图数量, 二分图要满足线段不交
        此时我们应该意识到, 只有树才会同构于不交的二分图
        证明很简单, 假设我们找到了与图G同构的二分图G'
        我们取G'的任意一棵生成树, 此时二分图左右两边任取两点, 必然是连通的, 因此两点连线必然与
        某条边相交
        那么如果G'的边数 >= n, 说明必然有两个点之间的边不在生成树上, 那么加上这条边就会与其他边
        相交, 不符合要求
        下面只考虑图G为树的情况:
        有个比较明显的性质: 每个点u最多有2个非叶邻居节点
        这点也很好证, 假设有 >= 3个非叶邻居
        对任意一种排布方案, 我们取最左侧和最右侧的非叶邻居i,j
        其余非叶邻居必然在i,j之间
        而由于这些点度数 >= 2, 因此除了与对岸的u相连外, 还要与其他点相连
        但与其他点相连后, 必然穿过(u,i)或(u,j)两条边, 矛盾
        这样我们就对图G有了清晰认知了:
            图G必须是树, 且每个点至多2个非叶邻居
        排布规则为:
            对每个非叶节点u:
            (1)如果它有2个非叶节点, 那么把它的叶子节点排列在非叶节点中间
            (2)如果它有1个非叶节点, 那么把它的叶子节点放在非叶节点的另一侧
            (3)如果它有0个非叶节点, 那么图G必然是菊花图
        不难发现, (1)和(2)的计数方法是一样的, 答案都是4 * Π(u的叶子邻居数量)!
        (3)菊花图的计数失去了左右对称, 答案是2 * (N - 1)!
*/
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
int fac[N + 1];
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    vector<int> d(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        d[u]++;
        d[v]++;
    }
    if(m >= n) {
        cout << 0 << "\n";
        return;
    }
    int ans = 1;
    bool tag = true;
    for(int u = 1; u <= n; u++) {
        if(d[u] == 1) continue;
        int c = 0, leaf = 0;
        for(int v : adj[u]) {
            if(d[v] >= 2) {
                c++;
            } else {
                leaf++;
            }
        }
        if(c > 2) {
            ans = 0; 
        } else {
            ans = 1LL * ans * fac[leaf] % MOD;
            if(c != 0) {
                tag = false;
            }
        }
    }
    if(tag) {
        ans = 2LL * ans % MOD;
    } else {
        ans = 4LL * ans % MOD;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    fac[0] = 1;
    for(int i = 1; i <= N; i++) {
        fac[i] = 1LL * fac[i - 1] * i % MOD;
    }
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
