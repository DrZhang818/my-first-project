#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://atcoder.jp/contests/dp/tasks/dp_f
/*
    经典线性DP —— LCS
    思路: dp[i][j]:= s的前i个字符与t的前j个字符的最长公共子序列的长度
    LCS的构建:
        构建只能使用二维DP表, 采用回溯双指针法构建, 本质是模拟了一遍DP决策树
*/
//LCS计算大小
void solve(){
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    vector<int> dp(m + 1);
    for(int i = 1; i <= n; i++){
        for(int j = 1, pre = 0; j <= m; j++){
            int temp = dp[j];
            if(s[i - 1] == t[j - 1]){
                dp[j] = pre + 1;
            }
            else{
                dp[j] = max(dp[j], dp[j - 1]);
            }
            pre = temp;
        }
    }
    cout << dp[m];
}

//LCS构建
void solve1(){
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(s[i - 1] == t[j - 1]){
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else{
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    string lcs = "";
    int i = n, j = m;
    while(i > 0 && j > 0){
        if(s[i - 1] == t[j - 1]){
            lcs += s[i - 1];
            i--;
            j--;
        }
        else{
            if(dp[i - 1][j] > dp[i][j - 1]){
                i--;
            }
            else{
                j--;
            }
        }
    }
    reverse(lcs.begin(), lcs.end());
    cout << lcs << "\n";
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve1();
    return 0;
}