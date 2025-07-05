#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://www.luogu.com.cn/problem/SP685
/*
    数据结构优化DP || 二分
    题意:
        给定一个长度为N的数组和一个整数K, 你需要把数组划分成恰好K段, 使得最大子段和最小
        求出最小值
        范围: N∈[1,15000], a[i]∈[-3e4, 3e4], K∈[1,N]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先分析状态数量, 由于是划分子段问题, 由组合数学可知总状态数为C[n-1][k-1]
        暴力做法时间复杂度为O(n * C[n-1][k-1]), 需要优化
        正向求解需要压缩状态数量, 通过划分等价类或贪心等方式来减少搜索空间
        我们可以很容易地设计出一种DP做法: 
        dp[i][j] := 把前i个数字划分成j段能得到的最小值, 时间复杂度为O(n^2 * k)
        显然还是超时, 此时已经到达正向求解的瓶颈了, 因为状态无法再进行压缩了
        由于答案显然具有单调性, 我们往二分答案上进行思考:
        本题最难的点就在于check函数非常难想, 数组有负权, 划分要求恰好K段, 这都是很难处理的
        负权意味着我们不能贪心地进行划分, 恰好K段意味着合法性判断更为严格
        此时我们只能定义dp[i][j] := 前i个数字能否恰好划分成j段, 且每段和小于等于x
        但这样显然还是nk的状态, 无法通过
        下面是本题的核心trick: 利用介值定理判断合法性
        定义dp1[i] := 前i个数字最少划分出的子段数量
            dp2[i] := 前i个数字最多划分出的子段数量
            这里的子段要满足子段和小于等于x
        为什么要这样转化? 这牵扯到一个核心思想: min和max往往是好维护的, 不大不小的由于自身
        缺乏性质难以维护, 那么可以考虑介值定理, 利用minmax确定中间值是否合法
        由于可以把分组看成分割区间, 最大分割必然可以通过最小分割逐步扩展得到
        因此我们的组数可以取遍[min,max]中的所有整数
        现在的关键问题是如何转移
        以维护dp1为例子
        f[i] = min{f[j]} + 1 (j < i && s[i] - s[j] <= x)
        首先对数据进行离散化, 然后用权值树状数组维护
        把id(s[j] + x)看作点, f[j]看作点权, 问题就变成查询[0,id(s[i])]的最小值
*/
inline int lowbit(int o) { return o & -o; }
class BIT {
    vector<int> tr;
    int n;
public:
    BIT(int x, int tag) : n(x), tr(x + 1, tag ? -inf : inf) {}
    void modify(int o, int d, int tag) {
        for(; o > 0; o -= lowbit(o)) {
            if(tag == 0) {
                tr[o] = min(tr[o], d);
            } else {
                tr[o] = max(tr[o], d);
            }
        }
    }
    int query(int o, int tag) {
        int res = tag ? -inf : inf;
        for(; o <= n; o += lowbit(o)) {
            if(tag == 0) {
                res = min(res, tr[o]);
            } else {
                res = max(res, tr[o]);
            }
        }
        return res;
    }
};
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + a[i];
    }
    auto ck = [&](int x) -> bool {
        vector<int> val;
        val.reserve(n + 1);
        for(int i = 0; i <= n; i++) {
            val.push_back(pre[i]);
            val.push_back(pre[i] + x);
        }
        sort(val.begin(), val.end());
        val.erase(unique(val.begin(), val.end()), val.end());
        int sz = val.size();
        BIT tr1(sz + 1, 0), tr2(sz + 1, 1);
        vector<int> dp1(n + 1), dp2(n + 1);
        dp1[0] = dp2[0] = 0;
        int px = lower_bound(val.begin(), val.end(), x) - val.begin() + 1;
        tr1.modify(px, 0, 0), tr2.modify(px, 0, 1);
        for(int i = 1; i <= n; i++) {
            int pos = lower_bound(val.begin(), val.end(), pre[i]) - val.begin() + 1;
            dp1[i] = tr1.query(pos, 0) + 1;
            dp2[i] = tr2.query(pos, 1) + 1;
            pos = lower_bound(val.begin(), val.end(), pre[i] + x) - val.begin() + 1;
            tr1.modify(pos, dp1[i], 0);
            tr2.modify(pos, dp2[i], 1);
        }
        return dp1[n] <= k && k <= dp2[n];
    };
    int l = -inf, r = inf;
    while(l + 1 < r) {
        int mid = l + (r - l) / 2;
        if(ck(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << r << "\n";
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
