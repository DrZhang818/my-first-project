#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000007;

//https://atcoder.jp/contests/abc364/tasks/abc364_f
/*
    贪心 || 数据结构 || 生成树
    题意:
        给定N个点, 编号为1~N, 初始时图中没有边, 接下来有Q次操作:
        第i次操作为: 给定L,R,C, 新建一个编号为N + i的节点, 与编号在[L,R]内的点连一条权值为C的
                    无向边
        请你判断Q次操作后图是否连通, 若连通, 求出最小生成树的权值, 不连通输出-1
        范围: N∈[1,2e5], Q∈[1,2e5], L,R∈[1,N], C∈[1,1e9]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心||网络流, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先思考暴力做法, 我们按照Kruskal的思想先按照权值进行排序, 然后从小到大考虑加边
        对于边(u,v,c), 如果u,v不连通, 那么就加上这条权值为c的边
        这样对于Q次询问, 每次询问都要遍历L[i]~R[i], 总时间复杂度为O(Q * N), 超时
        思考操作性质, 由于我们的操作是对一个区间段进行连边, 因此我们可以用并查集来维护那些已经
        连通的点, 例如:
            我们要连一条(u,v)的边, 同时我们知道v,v+1,v+2,...,v+i已经连通, 那么下一次考虑
            加边时我们可以直接跳到v+i+1这个点
        维护方法很简单, 我们把v~v+i这个连通块的代表元设置为v+i即可
        这样我们每次调用find函数就能获得当前块的结尾位置p, 接下来考虑p + 1是否在R内, 如果在
        就连接(u,p+1), 并合并(p,p+1), 接着继续跳到p+1这个块的结尾...
        最后, 如何判断图是否连通呢?
        连通意味着1~N在一个连通块内, 因此我们只需判断find(1)是否等于n即可
        n+1~n+q这些点不需要考虑, 因为这些点中的每一个都至少与1~n中的一个点连了一条边
        因此若1~n连通, 则1~n+q一定连通
*/
vector<int> fa;
int find(int o) {
    while(o != fa[o]) {
        o = fa[o] = fa[fa[o]];
    }
    return o;
}
void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if(u == v) {
        return;
    }
    fa[v] = u;
}
void init(int n) {
    fa.resize(n);
    iota(fa.begin(), fa.end(), 0);
}

void solve() {
    int n, q;
    cin >> n >> q;
    init(n + 1);

    vector<int> L(q + 1), R(q + 1), C(q + 1);
    for(int i = 1; i <= q; i++) {
        cin >> L[i] >> R[i] >> C[i];
    }

    vector<int> p(q);
    iota(p.begin(), p.end(), 1);
    sort(p.begin(), p.end(),
        [&](auto i, auto j) {
            return C[i] < C[j];
        });
    ll ans = 0;
    for(int i : p) {
        ans += C[i];
        for(int x = find(L[i]); x < R[i]; x = find(x)) {
            merge(x + 1, x);
            ans += C[i];
        }
    }

    if(find(1) != n) {
        cout << -1 << "\n";
        return;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
