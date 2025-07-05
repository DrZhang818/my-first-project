#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc408/tasks/abc408_e
//拓展: 与运算可以求最大值
/*
    最短路 || 试填法 || 并查集
    题意:
        给定一个N个节点M条边的无向带权连通图, 定义一条路径的权值为: 路径上所有权值的OR和
        求所有1->N的路径中的最小权值
        范围: N∈[2,2e5], M∈[N-1, 2e5], w∈[0,2^30)
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先思考暴力方法, 遍历所有初等路径并计算答案, 时间复杂度为O(路径个数 * 路径长度)
        这样做毫无疑问是超时的, 问题在于路径个数太多, 即状态量爆炸
        解决这种问题我们有两个思路: (1)贪心剪枝   (2)划分等价类
        位运算中有个很重要的性质: 2^i > ∑2^j, j∈[0,i-1]
        这意味着我们可以逐位贪心, 优先考虑高位为0的情况
        假设我们枚举到了第i位, 则我们可用的边权需要满足:
        (1)前面i-i位中为0的位置必须为0
        (2)当前第i位必须为0
        如果只用符合条件的边可以保持连通性, 说明第i位可以为0
        否则第i位必须为1
*/
vector<int> fa;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) {
    u = find(u);
    v = find(v);
    fa[u] = v;
}
bool same(int u, int v) { return find(u) == find(v); }
struct info {
    int u, v, w;
};
void solve() {
    int n, m;
    cin >> n >> m;
    vector<info> e(m);
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        e.emplace_back(u, v, w);
    }
    int x = (1 << 30) - 1;
    auto ck = [&]() -> bool {
        fa.assign(n + 1, 0);
        iota(fa.begin(), fa.end(), 0);
        for(auto &[u, v, w] : e) {
            if((w | x) == x) {
                merge(u, v);
            }
        }
        return same(1, n);
    };
    for(int i = 29; i >= 0; i--) {
        x &= ~(1 << i);
        if(!ck()) x |= 1 << i;
    }
    cout << x << "\n";
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
