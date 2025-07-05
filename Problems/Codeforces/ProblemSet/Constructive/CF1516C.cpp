#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/problemset/problem/1516/C
/*
    构造 || DP
    题意:
        给定一个长度为N的数组, 定义一个数组是合法的, 当且仅当无法把数组划分成两个子序列,
        使得两个子序列的和相同, 请你最小化以下操作次数, 使得数组变为合法数组
        op: 选择一个下标i, 删除对应元素
        范围: n∈[2,100], a[i]∈[1,2000]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先思考题目性质: 我们想一想合法数组具有什么样的条件:
        记数组总和为tot, 子序列1的和为S1, 子序列2的和为S2
        (1)如果tot为奇数, 那么数组必然是合法的, 因为在整数域内, 两个相同的数相加必为偶数
        (2)如果tot为偶数, 那么我们需要判断能否真的凑出tot / 2, 这可以用01背包来做
        如果数组不符合任何一条, 我们都可以直接说答案是0
        但如果都符合, 那么我们的操作次数一定是 >= 1, 现在考虑如何操作可以让数组合法
        这两条性质中, 显然性质(1)更强, 因为判断总和奇偶性是很容易的事情
        我们考虑能否通过删除一个奇数, 使得tot变为一个奇数
        最困难的点在于, 可能数组压根就不存在奇数
        这里就要有一个关键观察: 数组全是偶数的时候, 可以把每个元素都除以2
        整体缩小二分之一后, 我们需要证明变换前后的合法性是相同的
        这其实是非常显然的事情, 因为求和过程中只涉及到加法, 缩放系数都是相同的, 结果必然也相同
        如果变换后还全是偶数, 那么就继续递归地除下去, 直到数组中出现奇数
        此时, S1变为S1 >> k, S2变为S2 >> k, tot变为tot >> k
        由于tot = S1 + S2, 因此可以保证tot >> k仍是个偶数, 它等于S >> k - 1
        我们把这个奇数删除, 那么tot就成为了一个奇数, 不满足性质1, 因此数组合法
        由于这种变换始终维持了前后合法性相同, 因此移除这个数后原数组也合法
*/
inline int lowbit(int o) { return o & -o; }
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    int tot = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        tot += a[i];
    }
    if(tot & 1) {
        cout << 0 << "\n";
        return; 
    }
    vector<int> dp(tot + 1);
    dp[0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = tot; j >= a[i]; j--) {
            dp[j] |= dp[j - a[i]];
        }
    }
    if(!dp[tot >> 1]) {
        cout << 0 << "\n";
        return;
    }
    int idx = -1, mn = inf;
    for(int i = 1; i <= n; i++) {
        if(lowbit(a[i]) < mn) {
            mn = lowbit(a[i]);
            idx = i;
        }
    }
    cout << 1 << "\n";
    cout << idx << "\n";
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
