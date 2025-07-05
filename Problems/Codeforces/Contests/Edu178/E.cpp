#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2104/problem/E
/*
    DP || 贪心 || 子序列自动机
    题意:
        给定一个长度为N的字符串s和一个整数k, 一个字符是合法的, 当且仅当该字符是
        字母表中前k个字母之一, 已知字符串每个字符都是合法字符
        接下来有Q次询问, 每次询问给定一个由合法字符组成的字符串t, 回答至少需要
        追加几个合法字符才能使t不是s的子序列
        范围: N∈[1,1e6], k∈[1,26], Q∈[1,2e5], ∑len(t) <= 1e6
    关键思考:
        本题为决策||数据结构类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先分析题目性质, 由于追加的合法字符无数量约束, 我们可以贪心地每次都选距离
        当前位置最远的合法字符, 这样追加的效率最高
        因此我们需要知道:
        (1)t在s中的结束位置
        (2)结束位置 + 1选哪个字符迈出的步子最大
        持续进行操作(2)向后跳, 直到离开字符串s
        核心问题是如何解决(1), 这可以用子序列自动机实现
        非常简单, 我们用nxt[i][c]表示从第i个位置出发, 最近的字符c的位置
        状态转移如下:
        继承: nxt[i] = nxt[i + 1]
        发展: nxt[i][s[i]-'a'] = i
        由于查询次数很多, 我们考虑用DP预处理从第i个位置出发需要跳几步离开s
        定义dp[i] := 从位置i离开字符串s所需要的最小追加字符数量
        初值: dp[n+1] = 1, dp[n+2] = 0
        状态转移: 
            令m = max{nxt[i]}, 表示第i个位置跳一次最远到位置m
            则dp[i] = 1 + dp[m + 1]
*/
void solve() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    s = "#" + s;
    vector<vector<int>> nxt(n + 2, vector<int>(k, n + 1));
    vector<int> dp(n + 3);
    dp[n + 1] = 1;
    for(int i = n; i >= 1; i--) {
        nxt[i] = nxt[i + 1];
        nxt[i][s[i] - 'a'] = i;
        int m = *max_element(nxt[i].begin(), nxt[i].end());
        dp[i] = 1 + dp[m + 1];
    }    
    int q;
    cin >> q;
    while(q--) {
        string t;
        cin >> t;
        int cur = 0;
        for(int i = 0; i < t.size(); i++) {
            cur = nxt[cur + 1][t[i] - 'a'];
            if(cur == n + 1) break;
        }
        cout << dp[cur + 1] << "\n";
    }
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
