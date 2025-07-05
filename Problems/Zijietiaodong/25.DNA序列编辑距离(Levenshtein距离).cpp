#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://www.marscode.cn/practice/vkjwp462l6q75q?problem_id=7414004855075225644
//力扣: https://leetcode.cn/problems/edit-distance/description/
/*
    dp[i][j] := s1的前i个字符匹配s2前j个字符的最小步骤
    初始状态dp[i][0] = 0 dp[0][j] = j   
    状态转移:
        if s[i] == t[j]:
            dp[i][j] = dp[i - 1][j - 1]
        else:
            dp[i][j] = min(dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]) + 1
                              插入        删除          替换
    答案 : dp[len1][len2]
*/
void solution(string& dna1, string& dna2) {
    int len1 = dna1.length();
    int len2 = dna2.length();
    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1));
    for(int i = 0; i <= len1; i++){
        dp[i][0] = i;
    }
    for(int j = 0; j <= len2; j++){
        dp[0][j] = j;
    }
    for(int i = 1; i <= len1; i++){
        for(int j = 1; j <= len2; j++){
            if(dna1[i - 1] == dna2[j - 1]){
                dp[i][j] = dp[i - 1][j - 1];
            }
            else{
                dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
            }
        }
    }
    cout << dp[len1][len2];
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    string s1, s2;
    cin >> s1 >> s2;
    solution(s1, s2);
    return 0;
}
