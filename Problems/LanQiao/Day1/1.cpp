#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://www.lanqiao.cn/problems/5785/learning/?contest_id=235
/*
    DP || 分治 || 组合数学
    题意:
        给你一个长度为n的字符串和一个整数k, 你需要统计在字符串重复k次之后, 有多少个"ab"子序列
    关键思考:
        首先思考单个字符串怎么计算
            只需要从左到右枚举, 并更新a和b的出现频率即可
        接着思考多个字符串怎么计算
            可以视为新的字符串拼接在当前字符串前面
            这样新的答案就是 旧答案 + 单个答案 + ca * tb (tb表示后面的所有的b, 是cb的倍数)
        即 ans = ans + single + ca * cb * t (t = 1, 2, ..., k - 1)
        整理后即
            ans = k * single + ca * cb * k * (k - 1) / 2
*/
//优化解法
void solve1(){
    int n, k;
    string s;
    cin >> n >> k >> s;
    ll ans = 0, ca = 0, cb = 0;
    for(auto c : s){
        if(c == 'a'){
            ca++;
        }
        else if(c == 'b'){
            cb++;
            ans += ca;
        }
    }
    ans = k * ans + ca * cb * k * (k - 1) / 2;
    cout << ans << "\n";
}
void solve(){
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    ll ans = 0;
    vector<ll> dp(n);
    ll ca, cb;
    ca = cb = 0;
    for(int i = 0; i < n; i++){
        if(i != 0){
            dp[i] = dp[i - 1];
        }
        if(s[i] == 'b'){
            dp[i] += ca;
        }
        ca += s[i] == 'a';
        cb += s[i] == 'b';
    }
    ans = dp[n - 1];
    ll ta = ca, tb = cb, p = dp[n - 1];
    while(k > 1){
        ans = ans + p + ta * cb;
        cb += tb;
        k -= 1;
    }   
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve1();
    return 0;
}