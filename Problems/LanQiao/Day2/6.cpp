#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;
typedef pair<char,int> PCI;


//https://www.lanqiao.cn/problems/5373/learning/?contest_id=236
/*
    动态规划 || 滑动窗口优化
    题意:
        给定一个字符串, 你最多可以进行k次操作, 操作后将字符串划分成若干段, 求出最多能
        有几段长度为d且全部为1
        op: 选定一个字符, 将其变为1
    关键思考:
        最开始可能会想到使用最小堆来贪心, 因为单次操作的贡献只可能是0/1
        因此能否有这种贪心策略: 从左到右遍历同时将连续0个个数加入最小堆, 这样把堆顶变为1是最优的
        思考这个例子: 1011110111 k=1, d=4
        显然并不是能变就变这么简单, 还与"连续1的个数有关", 因此贪心复杂性变高, 考虑DP
        思考dp最重要的是状态设计和状态转移
        定义dp[i][j] := 前i个字符在操作次数最多为j时的最大值
        状态转移:
                当i < d时, dp[i][j]一定为0
                当i >= d时
                    如果 (i-d, i]间的0的个数 <= j
                        则dp[i][j] = max(dp[i-d][j-c0]+1, dp[i-1][j]);
                    否则
                        dp[i][j] = dp[i-1][j];
        空间优化:
            由于dp[i][j]只会用到最多i-d的值, 因此可以使用模运算来做滚动数组优化
            这个技巧十分方便, 不会涉及各种遍历序的问题
        时间优化:
            想要知道某个位置下(i-d, i]的0的个数, 显然可以使用定长滑窗解决
    时空复杂度:
        时间复杂度: O(n * k)
        空间复杂度: O(n + d * k)
*/

//优化做法
void solve1(){
    int k, d;
    cin >> k >> d;
    string s;
    cin >> s;
    int n = s.size();
    vector<int> zeros(n, 0);
    int c0 = 0;
    for(int i = 0; i < n; i++){
        if(s[i] == '0') {
            c0++;
        }
        if(i >= d && s[i - d] == '0'){
            c0--;
        }
        if(i >= d - 1){
            zeros[i] = c0;
        }
    }
    const int mod = d + 1;
    vector<vector<int>> dp(d + 1, vector<int>(k + 1));
    for(int i = d; i <= n; i++){
        for(int j = 0; j <= k; j++){
            dp[i%mod][j] = dp[(i-1+mod)%mod][j];
            int c_0 = zeros[i - 1];
            if(c_0 <= j){
                dp[i%mod][j] = max(dp[(i-d+mod)%mod][j - c_0] + 1, dp[i%mod][j]);
            }
        }
    }
    cout << dp[n%mod][k] << "\n";
}
//比赛时做法
void solve(){
    int k, d;
    cin >> k >> d;
    string s;
    cin >> s;
    int n = s.size();
    vector<vector<int>> dp(n + 1, vector<int>(k + 1));
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= k; j++){
            dp[i][j] = dp[i - 1][j];
            if(i - d >= 0){
                int c0 = 0;
                for(int p = i - d; p < i; p++){
                    if(s[p] == '0'){
                        c0++;
                    }
                }
                cout << c0 << " ";
                if(c0 <= j){
                    dp[i][j] = max(dp[i - d][j - c0] + 1, dp[i][j]);
                }
            }
            
        }
    }
    cout << dp[n][k] << "\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        solve1();
    }
    return 0;
}