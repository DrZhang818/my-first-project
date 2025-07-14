#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

/*
    DP || 双指针 || 数学
    题意:
        给定无限大二维平面上的N个点, 每个点用(x,y,s)描述, x,y为其坐标, s为其属性
        定义两点(xi,yi,si)和(xj,yj,sj)的距离为:
        如果si = sj, 则距离为-1
        如果si ≠ sj, 则距离为|xi-xj| + |yi-yj|
        请你求出平面上两点间的最大距离
        范围: N∈[1,2e5], x,y∈[-1e9,1e9], s∈[1,1e9]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        对于决策类题目, 我们首先将题目初步拆解为 局面 + 问题
        局面: 当前考虑到的i个点
        问题: 这i个点间的最大距离
        接下来, 我们不妨头脑风暴一下, 尽可能挖掘出问题的性质:
        (1)问题为从数组中选出一个2元集合, 与顺序无关, 因此可以对数组做任意排序
        (2)问题满足重叠子问题 + 最优子结构 + 无后效性
        (3)问题的值域不一定连续
        (4)问题的求解涉及绝对值函数, 可以通过分类讨论分解为四个独立的子问题
        本题的dp状态设计部分很简单
        dp[i] := 考虑前i个点, 得到的最大距离
        但这样转移是O(n)的, 我们考虑使用性质(4), 拆为四个问题
        dp1[i] := 考虑前i个点, xi-xj + yi-yj的最大值
        dp2[i] := 考虑前i个点, xi-xj + yj-yi的最大值
        dp3[i] := 考虑前i个点, xj-xi + yi-yj的最大值
        dp4[i] := 考虑前i个点, xj-xi + yj-yi的最大值
        则dp[i] = max(dp1[i], dp2[i], dp3[i], dp4[i])
        对于每个dpx, 如何进行状态转移呢
        考虑将问题进行变形, 以dp1为例
        (xi+yi) + (-xj-yj)
        我们只需要维护(-xj-yj)的最大值即可
        这可以通过再套一个dp'来完成

        如何处理属性s呢?
        由性质(1), 我们可以按照s对数组进行排序, 让相同的s在一个块内
        然后利用双指针, 计算出一整个块的dpx, 然后再进行dp'x
*/
struct info {
    ll x, y, s;
    friend bool operator < (const info &a, const info &b) {
        return a.s < b.s;
    }
};
void solve1() {
    int n;
    cin >> n;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y;
    }
    for(int i = 1; i <= n; i++) {
        cin >> a[i].s;
    }
    sort(a.begin() + 1, a.end());
    ll v1 = -inf, v2 = -inf, v3 = -inf, v4 = -inf, ans = -1;
    for(int l = 1, r = 1; l <= n; l = r + 1) {
        while(r < n && a[r + 1].s == a[l].s) r++;
        for(int i = l; i <= r; i++) {
            ans = max(ans, v1 - a[i].x - a[i].y);
            ans = max(ans, v2 - a[i].x + a[i].y);
            ans = max(ans, v3 + a[i].x - a[i].y);
            ans = max(ans, v4 + a[i].x + a[i].y);
        }
        for(int i = l; i <= r; i++) {
            v1 = max(v1, a[i].x + a[i].y);
            v2 = max(v2, a[i].x - a[i].y);
            v3 = max(v3, -a[i].x + a[i].y);
            v4 = max(v4, -a[i].x - a[i].y);
        }
    }
    cout << ans << "\n";
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve1();
    }
    return 0;
}
