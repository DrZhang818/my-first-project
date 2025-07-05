#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1e18 + 5;

//https://codeforces.com/gym/105386/problem/E
/*
    数论 || 贪心
    题意:
        给定一个长度为N的数组a和一个整数k, 你可以进行至多一次以下操作:
        op: 选择一段区间[l,r], 对于每个i∈[l,r], 将a[i]变为a[i] + k
        要求最大化整个数组的gcd, 输出最大值
        范围: n∈[1,3e5], k∈[1,1e18], a[i]∈[1,1e18]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先思考暴力方法, 总共有O(n^2)种操作方案, 时间复杂度为O(n^2 * logM), 超时
        我们发现这属于状态爆炸型优化问题, 解决这种问题有两种常见方法:
        (1)寻找等价类, 利用某种等价关系压缩状态, 使得具有相同性质的状态值计算一次
        (2)贪心剪枝, 避免访问一定不优的状态
        对于方法(1)在这里是很难实行的, 因为我们对于不同的[l,r]我们很难找到一种合适的性质来说
        [l1,r1]和[l2,r2]是等价的, 当然可以用最终得到的gcd来划分, 但这没意义
        我们把重心放在方法(2), 看看能否找到贪心策略跳过不优的状态
        引理: 一个长为n的数组的前缀gcd的不同取值只有O(logM)种
        想象这样一个场景: 利用前缀gcd把数组分成logn块
        _____,___,____,____
        对于分块后的数组, 我们思考下左端点l放在哪里是合适的
        显然放在一个块的开头是最优的, 我们可以把被区间分割后的数组的三块gcd记为G1,G2,G3
        l在同一个块内部的时候, G1是固定的
        gcd有一个关键性质: gcd(G1,G2,G3) <= G1
        我们可以感性地理解一下: G1原本是完整的一个块, 结果硬生生在块中的一个部分整体+k
        那这样带来的结果一定是劣的, 所得到的结果一定比完整保留G1整块带来的结果差
        因此我们发现了关键的贪心剪枝策略: 左端点l只放置在每个块个开头, 接着暴力扩展右端点r
        我们可以预处理出前缀gcd和后缀gcd, 这样就有了G1和G3, G2则在枚举r的过程中获得
        总时间复杂度为O(n * logM * logM)
*/
void solve() {
    int n;
    ll k;
    cin >> n >> k;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<ll> pre(n + 1), suf(n + 1);
    pre[1] = a[1];
    suf[n] = a[n];
    for(int i = 2; i <= n; i++) {
        pre[i] = __gcd(pre[i - 1], a[i]);
    }
    for(int i = n - 1; i >= 1; i--) {
        suf[i] = __gcd(suf[i + 1], a[i]);
    }
    ll ans = 1;
    for(int i = 0; i <= n; i++) {
        while(i < n && pre[i + 1] == pre[i]) i++;
        if(i == n) {
            ans = max(ans, pre[i]);
            break;
        }
        ll mid = a[i + 1] + k;
        for(int r = i + 1; r < n; r++) {
            mid = __gcd(mid, a[r] + k);
            if(i == 0) {
                ans = max(ans, __gcd(mid, suf[r + 1]));
            } else {
                ans = max(ans, __gcd(__gcd(pre[i], mid), suf[r + 1]));
            }
        }
        if(i == 0) {
            ans = max(ans, __gcd(mid, a[n] + k));
        } else {
            ans = max(ans, __gcd(pre[i], __gcd(mid, a[n] + k)));
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
        solve();
    }
    return 0;
}
