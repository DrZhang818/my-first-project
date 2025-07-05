#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://www.lanqiao.cn/problems/3503/learning/
/*
    DP
    题意:
        给定一个长度为N的数字字符串, 你可以选择一段子串并将其反转, 要求翻转后得到的数字
        严格小于原数字, 问有多少种合法的操作方案
        范围: N∈[1,5000]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        首先观察合法方案的性质, 不难发现问题等价于寻找字符串中有多少个子串满足r(T) < T
        r(T)表示将T反转
        显然, 对于区间[L,R], 若s[L] < s[R] 或者s[L] > s[R], 我们都很容易求解
        这个问题可以用状态机DP来做
        问题在于如果s[L] = s[R], 应该怎么去做?
        不难发现, 此时等价于判断S[L+1:R-1]是否满足r(T) < T
        此时问题就变成了规模更小的子问题, 并且这个问题与区间左右端点均有关
        因此可以设计区间DP来求解这个问题
        (1)定义dp[i][j] := 区间[i,j]是否合法
        (2)接着考虑如何进行状态转移
            1.若s[i] < s[j], 不合法 dp[i][j] = 0
            2.若s[i] > s[j], 合法   dp[i][j] = 1
            3.若s[i] = s[j], dp[i][j] = dp[i+1][j-1]
        (3)考虑状态初值
            长度为2的区间是base case, 因为直接判断一次即可
            即dp[i][i + 1] = s[i] > s[i + 1] ? 1 : 0
        (4)汇总答案
            遍历所有的[i,j], ans = ∑∑dp[i][j], i∈[1,N],j∈[i+1,N]
*/
//正解: 区间DP
void solve1() {
    string s;
    cin >> s;
    int n = s.size();
    s = "#" + s;
    vector<vector<bool>> dp(n + 1, vector<bool>(n + 1));
    for(int i = 1; i <= n - 1; i++) dp[i][i + 1] = s[i] > s[i + 1];
    for(int len = 3; len <= n; len++) {
        for(int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            if(s[i] == s[j]) dp[i][j] = dp[i + 1][j - 1];
            else dp[i][j] = s[i] > s[j];
        }
    } 
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            ans += dp[i][j];
        }
    }
    cout << ans << "\n";
}



//赛时做法: 状态机DP + 双指针(容易超时)
void solve() { 
    string s;
    cin >> s;
    int n = s.size();
    s = "#" + s;
    vector<ll> dp(10);
    vector<vector<int>> pos(10);
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        int x = s[i] - '0';
        for(int j = x + 1; j <= 9; j++) {
            ans += dp[j];
        }
        for(int j = 0; j < pos[x].size(); j++) {
            int l = pos[x][j], r = i;
            bool ok = false;
            while(l < r) {
                if(s[l] > s[r]) {
                    ok = true;
                    break;
                }
                if(s[l] < s[r]) {
                    break;
                }
                l++;
                r--;
            }
            if(ok) {
                ans++;
            }
        }
        dp[x]++;
        pos[x].push_back(i);
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
    
