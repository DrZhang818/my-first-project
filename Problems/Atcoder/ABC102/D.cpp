#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E15;

//https://atcoder.jp/contests/abc102/tasks/arc100_b
/*
    贪心 || 双指针
    题意:
        给定一个长度为N的数组, 你需要将数组划分成四个非空的子数组
        设四个子数组的和依次为P,Q,R,S, 你需要最小化P,Q,R,S中最大值和最小值的绝对差
        范围: N∈[4,2e5], a[i]∈[1,1e9]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        对于本题, 我们可能首先会想到划分型DP, 定义dp[i][j] := 考虑前i个数分成j段得到的最小极差
        但是我们很快发现, 这样的状态是无法转移的, 因为我们枚举划分点就已经是O(n)的操作了, 同时由于
        "极差"不仅与当前段有关, 还与前面分出的j-1段的max和min有关, 时间无法接受且需要额外状态
        二分答案也是一个常见误区, 因为check函数根本无法写, 此时需要写的check函数是:
            给定x, 判断能否把数组分成四段, 使得极差≤x
        这个问题是无法ck出来的
        常用手段都无法解决了, 我们不妨回归到暴力解法, 看看有没有入手点
        考虑枚举法, 枚举P,Q,R的右端点, 利用前缀和优化我们可以在O(n^3)的时间内解决问题
        这里有个隐蔽的贪心优化点:
            当我们Q确定的时候, P,R是可以贪心地确定下来的
        我们枚举Q的右端点, 此时数组被划分成了两段
            [   ][   ]
              1    2
        贪心地想, 当这四段的极差最小时, 1,2两个大段中各自的两个小段的极差必然也要最小
        这是由极差的性质易得的, 极差就是要求分出的子段尽可能地平均
        可以用反证法简单做个证明:
            假设某一个大段的极差不是最小的, 那么带来的结果是, P,Q,R,S的最大值只会更大
            最小值只会更小, 显然是劣的
        由于数组元素为正, 因此决策具有单调新, 我们可以用双指针在O(n)的时间内做完这道题
*/
void solve() {
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        a[i] += a[i - 1];
    }
    ll ans = inf;
    for(int i = 1, j = 2, k = 3; j <= n - 2; j++) {
        while(i < j - 1 && abs(a[i]-(a[j]-a[i])) > abs(a[i+1]-(a[j] - a[i+1]))) i++;
        while(k < n - 1 && abs(a[k]-a[j]-(a[n]-a[k])) > abs(a[k+1]-a[j]-(a[n]-a[k+1]))) k++;
        ll mn = min({a[i], a[j] - a[i], a[k] - a[j], a[n] - a[k]});
        ll mx = max({a[i], a[j] - a[i], a[k] - a[j], a[n] - a[k]});
        ans = min(ans, mx - mn);
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
