#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2130/problem/C
/*
    构造 || 贪心
    题意: 
        对于一组数对S = {(a1,b1), (a2,b2), ..., (am,bm)}, ∀i∈[1,m], ai < bi
        定义f(S), g(S)如下:
        f(S): 将每个(ai,bi)视为数轴上的线段, f(S)表示这些线段的并集长度
        g(S): 将每个(ai,bi)视为图中的无向边, g(S)表示图中至少位于一个边数不少于3的简单环上的节点数量
        给定N个互不相同的数对, 你需要从中选出一个子集S', 使得f(S') - g(S')最大化
        输出所选数对的索引
        范围: N∈[1,3000], 1 <= ai < bi <= 2N
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先我们思考什么时候会出现环?
        就是有了x1 -> ... -> xk, 又有一条不同的xk -> ... -> x1
        我们发现, 完全可以删除xk -> ... -> x1, 这并不会减少f(S'), 但会让g(S')减少
        这个结论可以推广到所有点对
        如果我们发现(ai, bi)已经连通, 就不能加入这条边, 否则加入这条边
        上述讨论已经证明, 删除某条冗余边不会减少f(S'), 这保证了答案是最优的
*/
vector<int> fa;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) { u = find(u), v = find(v); if(u != v) fa[u] = v; }
bool same(int u, int v) { return find(u) == find(v); }
void solve() {
    int n;
    cin >> n;
    fa.resize(2 * n + 1);
    iota(fa.begin(), fa.end(), 0);
    vector<int> ans;
    for(int i = 1; i <= n; i++) {
        int l, r;
        cin >> l >> r;
        if(!same(l, r)) {
            ans.push_back(i);
            merge(l, r);
        }
    }
    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " \n"[i == ans.size() - 1];
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
