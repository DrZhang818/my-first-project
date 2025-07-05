#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://www.acwing.com/problem/content/description/293/
/*
    状压DP || 轮廓线DP
    题意:
        给定N行M列的矩阵, 用1 × 2的砖块填充, 求有多少种填充方案
        范围: N,M∈[1,11]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        首先思考暴力方法, 每个格子由横放和竖放两种状态, 枚举的时间复杂度约为O(2^(m+n))
        考虑用状压DP来优化, 由于涉及到上下两行的状态, 我们可以巧妙的把上下两行状态压缩在一起
        对于一个状态S, 前m-j个状态是上一行[j,m-1]的状态, 后j个状态是当前行[0,j-1]的状态
        这样设计后, 我们就可以通过逐格枚举来完成状态转移, 转移过程类似一条蛇一样移动
        分别考虑(i,j)格子填或不填, 用1表示填, 用0表示不填
        (1)不填, 则要求(i-1,j)必须填, 否则将没有机会填充(i-1,j)
                但对(i,j-1)没有要求, 因为后续它可以被(i+1,j-1)进行填充(竖放)
        (2)填, 如果横放, 则要求(i,j-1)没有填 且 (i-1,j)已经填充
               如果竖放, 则要求(i-1,j)没有填
        把上述过程转化成位运算即可完成状态转移
        接下来考虑状态初值
        初始状态dp[1 << (m - 1)] = 1, 其他为0, 表示第一行的填写与上一行完全无关
        这是因为如果上一行已经完全填充好, 则当前行的填写是自由的
        最后考虑DP表的填充顺序
        很简单, 只需要逐格枚举即可, 每个格子遍历0 -> (1<<m)-1进行刷表法填充
*/
int n, m;
void solve() { 
    if(m > n) swap(n, m);
    vector<ll> dp(1 << m);
    dp[(1 << m) - 1] = 1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            vector<ll> ndp(1 << m);
            for(int k = 0; k < 1 << m; k++) {
                bool up = (k >> m - 1 & 1), left = (k & 1);
                if(up) ndp[(k << 1) & ~(1 << m)] += dp[k];
                if(i && !up) ndp[k << 1 | 1] += dp[k];
                if(j && up && !left) ndp[(k << 1 | 3) & ~(1 << m)] += dp[k];
            }
            dp = move(ndp);
        }
    }
    cout << dp[(1 << m) - 1] << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    while(cin >> n >> m && n || m) {
        solve();
    }
    return 0;
}
    
