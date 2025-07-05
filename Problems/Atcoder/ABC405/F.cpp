#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc405/tasks/abc405_f
/*
    离线二维数点
    题意:
        给定2N个点和M条边, 这2N个点均匀地位于一个圆上, 每条边连接着两个不同的偶数点
        接下来有Q次询问, 每次询问给出两个奇数点u,v, 回答连接u,v的线段穿过了几条边
        范围: N∈[2,1e6], M∈[1,min(N//2, 2e5)], Q∈[1,2e5]
    关键思考:
        本题为数据结构类题目, 常用思考方式为: 读请题目要求, 选用合适的算法和数据结构维护信息
        首先思考如何判断两条线段相交, 这本是计算几何的问题, 但在本题中可以进行简化
        对于询问(u,v), 我们查询有多少条边的两个端点位于u,v两侧, 假设u < v
        即一个端点位于(u,v), 另一个端点位于(v,2N]∪(1,u)
        可以把答案拆为两部分统计: 统计第一个端点位于(u,v)且第二个端点位于(v,2N]的答案
        以及第一个端点位于(u,v)且第二个端点位于(1,u)的答案
        我们可以把第一个端点位置放在x轴上, 第二个端点位置放在y轴上
        这样查询操作就变成了统计矩形区域内点的数量, 这是经典的离线二维数点问题
        我们把点和查询放在一起并按x轴排序, x相同时先点再查询
        这样排序的好处在于, 进行第i个查询时, 仅有坐标M<=i
*/
int n, m;
vector<int> tr;
int lowbit(int o) { return o & -o; }
void add(int o, int d) { 
    for(; o <= n; o += lowbit(o)) {
        tr[o] += d;
    }
}
int query(int o) {
    int res = 0;
    for(; o > 0; o -= lowbit(o)) { 
        res += tr[o];
    }
    return res;
}
struct info {
    int x, y, id, d;
    friend bool operator < (const info &a, const info &b) {
        if(a.x != b.x) return a.x < b.x;
        return a.id < b.id;
    }
};
void solve() {
    cin >> n >> m;
    n *= 2;
    tr.resize(n + 1);
    vector<info> a;
    for(int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        a.push_back({x, y, -1, 1});
        a.push_back({y, x, -1, 1});
    }
    int q;
    cin >> q;
    vector<int> ans(q + 1);
    for(int i = 1; i <= q; i++) {
        int x, y;
        cin >> x >> y;
        a.push_back({y, x, i, 1});
        if(x - 1 >= 1) a.push_back({x - 1, x, i, -1});
        a.push_back({y, n, i, 1});
        if(y - 1 >= 1) a.push_back({y, y - 1, i, -1});
        if(x - 1 >= 1) a.push_back({x - 1, n, i, -1});
        if(x - 1 >= 1 && y - 1 >= 1) a.push_back({x - 1, y - 1, i, 1});
    }
    sort(a.begin(), a.end());
    for(auto &[x, y, id, d] : a) {
        if(id == -1) {
            add(y, d);
        } else {
            ans[id] += d * query(y);
        }
    }
    for(int i = 1; i <= q; i++) {
        cout << ans[i] << "\n";
    }
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
