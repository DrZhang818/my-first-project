#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://codeforces.com/contest/2050/problem/A
/*
    模拟 || 字符串
    题意: 给定n个字符串和长度限制m, 求最大的k, 使得前k个字符串长度之和小于等于m
    ∑(1 -> k) s.length <= m
*/
void solve(){
    int n, m, ans = 0, cur = 0;
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        cur += s.length();
        if(cur <= m) ans++;
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}