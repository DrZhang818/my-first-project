#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc116/tasks/abc116_d
/*
    枚举 || 贪心 || 数据结构
    题意:
        有N块寿司, 每块寿司有两个参数, 配料种类t[i]和美味度d[i], 你需要从这N块寿司中选择K块吃掉
        满意度计算方法如下:
        (1)满意度是"基础总美味度"和"多样性奖励"的总和
        (2)基础总美味度是你所吃的寿司的美味度之和
        (3)多样性奖励是x * x, 其中x是你所吃的寿司中不同配料种类的数量
        请你求出最大满意度是多少
        范围: N∈[1,1e5], K∈[1,N], t[i]∈[1,N], d[i]∈[1,1e9]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        对于二维决策问题, 我们首先思考能否枚举其中一个维度
        不难发现, 枚举不同种类数量x是可行的, 因为这最多有K种状态
        通过枚举一个维度, 我们就把二维决策转变为了一维决策问题, 即:
        保证至少有x个不同配料种类, 能获得的最大满意度, 此时等价于最大化基础总美味度
        我们先考虑如何满足至少有x个不同配料种类
        贪心地想, 我们肯定要按美味度从大到小选x个, 这是显然的
        下面问题就是自由地选k - x个, 显然还是要贪心地从大到小选
        如果我们钦定必选的物品恰好在前k - x大里面, 那无需调整
        如果不在前k - x大里面, 我们强行钦定选这件, 就要从前面删掉一个不是必选的物品
        随x增大, k - x减小, 我们可以用双指针来维护
*/
struct info {
    int t, d;
    friend bool operator < (const info &a, const info &b) {
        return a.d > b.d;
    }
};
void solve() {
    int n, k;
    cin >> n >> k;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].t >> a[i].d;
    }
    sort(a.begin() + 1, a.end());
    vector<int> pos(n + 1, inf);
    int sz = 0;
    for(int i = 1; i <= n; i++) {
        auto [t, _] = a[i];
        if(pos[t] == inf) {
            pos[t] = i;
            sz++;
        }
    }
    sz = min(sz, k);
    sort(pos.begin() + 1, pos.end());
    ll ans = 0, sum = 0;
    for(int i = 1; i <= k; i++) {
        sum += a[i].d;
    }
    vector<int> vis(n + 1);
    for(int x = 1, r = k; x <= sz; x++) {
        vis[pos[x]] = true;
        if(pos[x] > r) {
            sum += a[pos[x]].d;
            while(vis[r]) r--;
            sum -= a[r--].d;
        }
        ans = max(ans, sum + 1LL * x * x);
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
