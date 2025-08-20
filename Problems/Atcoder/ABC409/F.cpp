#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

//https://atcoder.jp/contests/abc409/tasks/abc409_f
/*
    优先队列 || 并查集
    题意:
        给定二维平面上的N个点(x,y), 编号为1~N, 定义两点间距离为曼哈顿距离
        定义两个连通分量A,B的距离为d(A,B) = min{d(u,v) | u∈V(A), v∈V(B)}
        你需要处理Q个询问, 询问有三种类型:
        op1: 给定x,y, 将点(x,y)加入平面中, 编号为加入后平面内点的总数
        op2: 合并所有距离最近的连通分量并输出最小距离, 如果连通分量只有1个, 输出-1
        op3: 给定u,v, 判断点u和点v是否属于同一连通分量
        起初所有点之间互不连通
        范围: N∈[2,1500], Q∈[1,1500], x,y∈[0,1e9]
    关键思考:
        本题为数据结构类题目, 需要读清题意, 选用合适的算法和数据结构维护题目信息, 回答询问
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心||网络流, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先思考暴力做法, 对于op1, 直接加入新点, 对于op2, 可以在O(N^2)时间内枚举每个点对并用并查集
        合并, 对于op3, 从并查集中查询即可, 总时间复杂度为O(Q * N^2), 超时
        瓶颈在于op2, 我们每次询问都需要遍历所有点对, 因此会涉及大量重复计算
        事实上, 每个点对我们只需要计算一次即可
        所以我们需要一个数据结构能够存储所有点对的值, 并支持查询最大值, 这显然可以用优先队列来维护
        我们在处理询问前, 先把所有点对距离加入优先队列, 每次遇到op1时把新增的点对距离也立刻加入
        由于我们要求点对属于不同连通分量, 因此需要额外记录点对中的两个点具体是谁
        然而, 我们可能在处理询问过程中, 使得一些堆中的点对从不连通变成连通, 因此要从优先队列中删除
        这可以用懒删除堆的思想解决, 我们不立刻删除连通的点对, 而是用到它的时候判断一下是否连通
        最后我们就可以在O((N + Q)^2 * log(N + Q))的时间内解决
*/
vector<int> fa;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) {
    u = find(u), v = find(v);
    if(u == v) return;
    fa[u] = v;
}
struct info {
    int u, v;
    ll d;
    friend bool operator < (const info &a, const info &b) {
        return a.d > b.d;
    }
};
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> x(n + 1), y(n + 1);
    fa.resize(n + q + 1);
    iota(fa.begin(), fa.end(), 0);
    for(int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];        
    }
    priority_queue<info> pq;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j < i; j++) {
            pq.push({i, j, abs(x[i] - x[j]) + abs(y[i] - y[j])});
        }
    }
    int cnt = n;
    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            cnt++;
            int xx, yy;
            cin >> xx >> yy;
            x.push_back(xx);
            y.push_back(yy);
            for(int i = 1; i < cnt; i++) {
                pq.push({cnt, i, abs(xx - x[i]) + abs(yy - y[i])});
            }
        } else if(op == 2) {
            while(!pq.empty() && find(pq.top().u) == find(pq.top().v)) {
                pq.pop();
            }
            if(pq.empty()) {
                cout << -1 << "\n";
                continue;
            }
            ll k = pq.top().d;
            while(!pq.empty() && pq.top().d == k) {
                auto [u, v, d] = pq.top(); pq.pop();
                merge(u, v);
            }
            cout << k << "\n";
        } else {
            int u, v;
            cin >> u >> v;
            if(find(u) == find(v)) {
                cout << "Yes\n"; 
            } else {
                cout << "No\n";
            }
        }
    }
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
