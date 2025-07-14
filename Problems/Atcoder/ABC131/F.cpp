#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc131/tasks/abc131_f
/*
    并查集 || 思维
    题意:
        在无限大平面上有N个点, 第i个点为(x_i, y_i), 你可以进行以下操作:
        op: 选择四个整数a,b,c,d(a≠c∧b≠d), 满足坐标(a,b),(a,d),(c,b),(c,d)中恰好有三个点
            然后在剩下的一个坐标上添加一个点
        求出最多能进行多少次操作
        范围: N∈[1,1e5], x,y∈[1,1e5], 数据保证没有两个相同坐标的点
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先观察题目性质, 假设有了点(a,b),(a,d),(c,b), 我们能推出点(c,d)存在
        这是一个典型的满足"传递性"的条件, 因此事实上本题是一道求解传递闭包的题目
        下面考虑进行图论建模:
        我们可以把一个点(x,y)拆成点x和点y, 为作区分, 把y添加偏移量, 变成点y+N
        这样我们就得到一个二分图, 其中包括X和Y两部分
        对于点(x,y), 将x与y+N连一条无向边
        利用并查集我们就能轻松求出连通块, 进而得出传递闭包的势
        接下来考虑对于每一个连通块如何进行计数:
        二分图<X,Y>上, 每条边都对应平面上的一个点
        我们把一个连通块表示为: x1,x2,...,xn,y1,y2,...,ym
        在传递闭包中, 对于i∈[1,n],j∈[1,m], xi和yj都有连边
        因此该连通分量中的总点数为n * m
        那么我们统计出所有连通分量的点数, 再减去原有的N个点, 得到的就是新增的点数
*/
const int N = 100000;
int fa[2 * N + 1], r[2 * N + 1], c[2 * N + 1];
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) { fa[find(u)] = find(v); }
void solve() {
    int n;
    cin >> n;
    for(int i = 1; i <= 2 * N; i++) fa[i] = i;
    for(int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        merge(x, y + N);
    }
    for(int i = 1; i <= N; i++) {
        r[find(i)]++;
        c[find(i + N)]++;
    }
    ll ans = 0;
    for(int i = 1; i <= 2 * N; i++) {
        ans += 1LL * r[i] * c[i];
    }
    cout << ans - n << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
