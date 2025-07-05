#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://codeforces.com/contest/2005/problem/C
/*
    DP || 贪心
    题意:
        给定N个字符串, 每个字符串长度固定为M
        你需要从这N个字符串中挑选若干个(可以为0), 并按输入顺序拼接在一起, 记为S
        现有两人Alice和Bob,
        Alice需要从S中选出尽可能多的不重叠子序列"narek", 得分为5 * 选出的个数
        Bob的得分为S中不在Alice子序列中的{'n','a','r','e','k'}的个数
        要求计算出Alice最多能比Bob多几分? 即最大化Score(A) - Score(B)
        范围: N,M∈[1,1e3]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        对题目做简化处理: 下文讨论的字符∈"narek", 因为其它字符对A和B的贡献都是0
        首先思考暴力做法, 枚举所有拼接方式并逐一计算, 复杂度为O(2^n * n * m), 超时
        瓶颈在于枚举拼接方案, 于是我们思考能否通过DP或贪心, 直接从之前的最优解推出当前最优解
        我们考虑能否使用增益数组贪心, 如果当前字符是tar, 得分+1, 否则得分-1
        按照得分正负决定选或不选
        很明显是不正确的, 如 n* | a* | r* | eaaa | k*, 我们会舍弃掉eaaa, 但事实上选上更优
        这说明简单的贪心不能运作, 我们需要从全局(整个决策树)中获得答案, 这就需要设计DP了
        对于匹配循环字符串的问题, 我们有个经典思路就是设计状态机DP
        dp[i][j] := 考虑前i个字符串, 下个目标字符为t[j]的最优方案
        初始状态为dp[0][0] = 0, dp[0][1~4] = -inf
        在转移时可以采用贪心策略:
            对于每个字符串, 从前往后只要是当前的tar就选, 这样一定最优
        考虑如何转移:
            我们遍历x : 0 ~ 4, 以五种初始目标遍历当前字符串, tar状态记为y, 出发时y = x
            每次遇到目标字符, 我们就让y++, 如果y = 5, 说明有了一组匹配的子序列, 贡献+5同时y归0
            从状态x出发, 得到的贡献为res, 结束时下一个要匹配的状态为y
            那么有转移方程为: dp[i][y] = max(dp[i][y], dp[i - 1][y], dp[i - 1][x] + res)
            不难发现, 转移方程还是经典的继承 + 发展, 这是最标准的DP转移方程
            格外要注意的是, 这种转移方式只对可能出现的y进行了正确转移, 而y不一定覆盖0~4
            所以会出现漏掉继承的情况, 解决方法是转移之前先用pre覆盖cur, 确保全部继承
        在写代码时, 我们可以把第一维优化掉, 使用滚动数组来进行更新
*/
constexpr int inf = 1000000000;
void solve() { 
    int n, m;
    cin >> n >> m;
    string t = "narek";
    vector<vector<int>> dp(2, vector<int>(5, -inf));
    dp[0][0] = 0;
    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        auto &cur = dp[i % 2], &pre = dp[(i + 1) % 2];
        cur = pre;
        for(int x = 0; x < 5; x++) {
            int y = x, res = 0;
            for(auto c : s) {
                if(c == t[y]) {
                    y++;
                    if(y == 5) {
                        y = 0;
                        res += 5;
                    }
                } else if(t.find(c) != -1) {
                    res -= 1;
                }
            }
            cur[y] = max(cur[y], pre[x] + res);
        }
    }
    int ans = 0;
    for(int i = 0; i < 5; i++) {
        ans = max(ans, dp[n % 2][i] - i);
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
