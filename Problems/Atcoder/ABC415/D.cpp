#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc415/tasks/abc415_d
/*
    贪心
    题意:
        共有M家商店, 起初你有N瓶可乐, 0个空瓶, 0个贴纸, 你可以进行任意次以下操作:
        op1: 喝掉1瓶可乐, 持有的可乐数量-1, 空瓶数量+1
        op2: 选择一家商店, 向商店交出a[i]个空瓶, 换取b[i]瓶可乐和1张贴纸
        每一时刻必须保证持有的可乐和空瓶数量为非负整数
        请你求出最多能获得多少个贴纸
        范围: N∈[1,1e18], M∈[1,2e5], 1 <= b[i] < a[i] <= 1e18
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先我们发现, 可乐留在手中是没有用的, 我们可以用op1把手中的可乐全部转化成空瓶
        接下来的问题就是, 应该选择哪些商店进行兑换, 能够最大化贴纸数量
        显然, 如此庞大的数据范围是不允许我们dp的, 我们考虑贪心策略
        由于所有商店的单次操作都是获得一张贴纸, 因此决策与贴纸无关
        那么, 当前手中持有的空瓶数量cur会影响决策吗?
        我们容易想到, cur会导致那些a[i] > cur的商店不能选, 但对于a[i] <= cur的商店, 它们的选择会
        有一个固定的顺序, 这个顺序与cur无关
        如何证明这一点呢? 这就需要我们挖掘op2的性质
        我们考虑满足a[i] <= cur的商店, 当进行完op2后, 发生了哪些变化呢?
        (1)空瓶数量 cur -> cur - a[i] + b[i]
        (2)贴纸数量 + 1
        事实上, 带来的作用就是把空瓶数量减掉了 a[i] - b[i]
        那么显然手中剩余空瓶数量越多越好, 因此我们的最优决策一定是选择a[i] - b[i]最小的商店
        这一决策与cur无关
        因此整个数组的排序方式其实是确定的, 我们只需要按a[i] - b[i]的值进行排序即可
        那么如何计算在第i个商店能进行多少次操作呢
        这就用到解方程的思想
        我们设最多能进行t次操作, 那么第t - 1次操作必然是最后一个满足cur > a[i]的值
            cur - (t - 1) * (a[i] - b[i]) >= a[i]
            移项得 t <= (a[i] - cur) / (a[i] - b[i]) + 1
            那么t的最大值就是t = (a[i] - cur) // (a[i] - b[i]) + 1
    idea:
        本题的核心思想是“固定收益，不同成本”的资源消耗型循环过程，
        并采取“优先选择单位成本最低的操作”的贪心策略。
        当问题具有可以量化的单位效益的时候, 我们可以考虑类似"分数背包"的贪心策略
*/
struct info {
    ll x, y;
    friend bool operator < (const info &a, const info &b) {
        return a.x - a.y < b.x - b.y;
    }
};
void solve() {
    ll n;
    int m;
    cin >> n >> m;
    vector<info> a(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> a[i].x >> a[i].y;
    }
    sort(a.begin() + 1, a.end());
    ll ans = 0, cur = n;
    for(int i = 1; i <= m; i++) {
        if(cur < a[i].x) continue;
        ll t = (cur - a[i].x) / (a[i].x - a[i].y) + 1;
        ans += t;
        cur -= (a[i].x - a[i].y) * t;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
