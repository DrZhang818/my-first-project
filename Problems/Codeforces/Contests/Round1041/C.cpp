#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

//https://codeforces.com/contest/2127/problem/C
/*
    贪心 || 博弈
    题意:
        Alice和Bob在两个长为N的数组数组a,b上玩游戏, 游戏将持续k轮, 每轮流程如下:
        (1)Alice选择两个下标i和j (1 <= i < j <= n)
        (2)Bob可以任意重新排列a[i],a[j],b[i],b[j]
        完成k轮后, 游戏的价值定义为v = ∑ |a[i] - b[i]|
        Alice希望最小化v, Bob希望最大化v
        假设双方以最优策略进行, 求v是多少
        范围: N∈[2,2e5], k∈[1,N], a[i],b[i]∈[1,1e9]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        观察题目性质, Bob是真正控制v的人, Bob希望最大化v, 因此最终的v一定 >= 初始的v
        Alice需要找一对i,j, 使得Bob重排后增加的价值尽量小, 由于可以重复选, 因此可以断定Alice的
        最优策略是: 这k轮游戏都选择最优的i,j
        那么本题和k就无关了, 我们只需要找到哪一对i,j重排后可增加的价值最小即可
        我们知道, 对于四个数a,b,c,d, a <= b <= c <= d来说, 能得到的最大的绝对差之和为:
            (c + d) - (a + b)
        次大之和为:
            (b + d) - (a + c)
        我们可以让所有a[i] >= b[i], 这样在任意一对i,j中, a[i],a[j]扮演c,d或b,d
        Alice要做的, 就是找到扮演c,d的a[i],a[j], 这样Bob就无法通过重排顺序使得权值增大
        如果找不到这样一对i,j, 我们要选取c + d - a - b - b - d + a + c = 2c - 2b最小的一组
        我们可以按照a降序排列
        枚举到i时, a[i]扮演b或c
        (1)如果前面1~i-1中, 有某个b[j] <= a[i]
        那么选取这一对, a[i]就成功扮演了c的角色
        (2)如果所有b[j] > a[i], 我们取其中最小的一个
        选取这一对, a[i]扮演b, b[j]扮演c, 就满足2c - 2b最小
        因此只需维护前缀min即可
*/
struct info {
    ll x, y;
    friend bool operator < (const info &a, const info &b) {
        return a.x > b.x;
    }
};
void solve() {
    int n, k;
    cin >> n >> k;
    vector<info> a(n + 1);
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i].x;
    }
    for(int i = 1; i <= n; i++) {
        cin >> a[i].y;
        if(a[i].x < a[i].y) {
            swap(a[i].x, a[i].y);
        }
        ans += a[i].x - a[i].y;
    }
    sort(a.begin() + 1, a.end());
    ll mn = inf, d = inf;
    for(int i = 1; i <= n; i++) {
        d = min(d, max(0LL, 2 * mn - 2 * a[i].x));
        mn = min(mn, a[i].y);
    }
    cout << ans + d << "\n";
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
