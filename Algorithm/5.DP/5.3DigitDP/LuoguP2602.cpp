#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://www.luogu.com.cn/problem/P2602
/*
    DP 
    题意:
        给定两个整数a,b, 求在[a,b]范围内每个数码的出现次数
        范围: a,b∈[1,1e12] 
    关键思考:
        本题是计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        首先考虑暴力方法, 枚举a->b的所有数并逐一累加, 时间复杂度是O(nlogn), 需要优化
        优化的思路来源于贡献法, 即从枚举每个数出现了哪些数位 -> 枚举每个数位在多少数中出现
        这可以用数位DP来实现
        数位DP的核心就在于通过不断分治, 把含有lim限制的数拆解为不含lim的部分和含lim的部分
        而对于不含lim的部分, 往往会容易求得
        另一个很重要的点是前导零我们需要判断, 因为前导零是不能算作0的个数的
        为方便理解和写代码, 我们采用记忆化搜索来写数位DP, 这是常用技巧
        我们定义dp[i][j] := 考虑前i个数位, 有sum个tar的方案数
        边界条件: i = 0时, 以为着所有数位都固定为num对应的数位值, 此时就看sum含有几个tar
        而dfs里的lead和lim就是是否有前导0和是否有数值限制的标志, 我们可以按照
        有前导0/没有前导0, 有数值限制/没有数值限制来分类讨论, 分别写出转移方程
        数值限制这个状态很好转移, 如果当前没有限制, 下一状态肯定也没有限制
                                如果当前有限制, 那就看当前位是否等于上界up
        前导0的转移也很好思考, 只有当前有前导0, 并且当前位仍旧填0的情况下, 才会继承下去
        注意这里的一个细节:
            只有lead和lim都为假的时候, 我们才去记忆化, 有以下解读
            前导零 (lead)：
        当存在前导零时，当前位的选择可能影响后续统计。
        例如，前导零阶段的 0 不计入数码统计，而非前导零阶段的 0 会被计数。
        若lead为真, 即使pos和sum相同, 后续可能因前导零状态不同而产生不同结果, 故不能复用。
            数值限制 (lim)：
        当存在数值限制时，当前位的最大可选值受原始数位的限制。
        例如，若原始数位为 5，则当前位只能选 0-5。
        若 lim 为真，后续数位可能继续受限制，导致相同pos和sum对应不同的后续分支，无法复用结果。
        只有当这两个状态均为假时，表明当前处于"完全自由"的状态: 
        无前导零: 所有数字均有效，统计逻辑一致。
        无数值限制: 后续数位可自由选择 0-9，无需考虑原始数值。  
        此时，pos 和 sum 能唯一确定后续所有可能性，故可安全记忆化，避免重复计算，提高效率。
*/
constexpr int N = 15;
vector<vector<ll>> dp(N, vector<ll>(N, -1));
vector<int> num(N);
ll now;
ll dfs(int pos, int sum, bool lead, bool lim) {
    if(pos == 0) return sum;
    if(!lead && !lim && dp[pos][sum] != -1) return dp[pos][sum];
    ll ans = 0;
    int up = (lim ? num[pos] : 9);
    for(int i = 0; i <= up; i++) {
        if(i == 0 && lead) ans += dfs(pos - 1, sum, true, lim && i == up);
        else if(i == now) ans += dfs(pos - 1, sum + 1, false, lim && i == up);
        else if(i != now) ans += dfs(pos - 1, sum, false, lim && i == up);
    }
    if(!lead && !lim) dp[pos][sum] = ans;
    return ans;
}
ll work(ll x) {
    int len = 0;
    while(x) {
        num[++len] = x % 10;
        x /= 10;
    }
    for(int i = 0; i < N; i++) for(int j = 0; j < N; j++) dp[i][j] = -1;
    return dfs(len, 0, true, true);
}
void solve() { 
    ll a, b;
    cin >> a >> b;
    for(int i = 0; i < 10; i++) {
        now = i;
        cout << work(b) - work(a - 1) << " \n"[i == 9];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
