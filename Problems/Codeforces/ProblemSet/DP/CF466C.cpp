#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://codeforces.com/problemset/problem/466/C
/*
    DP
    题意:
        给定一个长度为n的数组, 求把数组分成三段等和子数组的方案数
        范围: n∈[1,5e5], a[i]∈[-1e9,1e9]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        首先思考暴力方法, 暴力枚举两个分割点并进行验证, 时间复杂度为O(n^2), 超时
        观察题目, 我们会发现一个很显然的性质, 每个子数组的和必须恰好是总和的1/3
        因此总和必须是3的倍数, 三个子数组的和也是固定的
        这便可以使用dp来求解了
        定义dp[i][j] := 前i个元素中, 能划分出j个和为sum/3的子数组的方案数
        (1)接着考虑如何进行状态转移:
        可以从左到右按顺序填写dp表
        继承: 
            dp[i][j] = dp[i - 1][j]
        发展: 
            若遇到pre[i] = sum/3*2时, dp[i][2] += dp[i-1][1] 
            若遇到pre[i] = sum/3时, dp[i][1] += 1
        由于第i个位置的更新只涉及到i-1, 因此可以优化掉第一个维度
        注意更新顺序即可
        (2)考虑状态初值
            dp[i][j] = 0
        (3)最终的答案就是dp[n][2]
        这里用到了一个技巧, 如果某个我们不需要管dp[i][3]如何转移
        因为只要划分出了2个和为sum/3的子数组, 剩下的数必然也是sum/3
*/
void solve() { 
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] += a[i - 1];
    }
    ll tot = a[n], cnt = 0, ans = 0;
    if(tot % 3 != 0) {
        cout << 0 << "\n";
        return;
    }
    for(int i = 1; i < n; i++) {
        if(a[i] == tot / 3 * 2) {
            ans += cnt;
        }   
        if(a[i] == tot / 3) {
            cnt++;
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
