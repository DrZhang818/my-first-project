#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://codeforces.com/contest/2049/problem/B
/*
    思维题 || 集合论
    题意:
        给定一个字符串pattern, 其中某些位置为's'或'p'
        现在需要判断能否构造一个排列满足parrten
        pattern的要求为：
            pattern[i]=='s'要求i以后的子数组为一个合法排列
            pattern[i]=='p'要求i以前的子数组为一个合法排列
    关键思考:
        pattern本质是对1~n的分布做了限制
        考虑以下情况:
            ..s......p..
              __________
            __________
              ________              
        假设交集部分长度为K, 左端点为L, 右端点为R
        那么要求1~K分布在交集部分
        那么K+1既要在R右面, 又要在L左边, 显然不存在
        当且仅当交集左端点在0或右端点在n - 1时, 可以构造
*/
void solve1(){
    int n;
    string s;
    cin >> n >> s;
    int l = 0, r = n - 1;
    for(int i = 0; i < n; i++){
        if(s[i] == 's') l = i;
        else if(s[i] == 'p' && r == n - 1) r = i;
    }
    cout << (l == 0 || r == n - 1 ? "YES\n" : "NO\n");
}
//比赛时写法
void solve(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    int l = -1, r = n;
    for(int i = 0; i < n; i++){
        if(s[i] == 's'){
            l = i;
        }
        else if(s[i] == 'p' && r == n){
            r = i;
        }
    }
    int need = min(n - l, r + 1);
    if(l == -1 || r == n || (l < r && (r - l + 1) >= need)){
        cout << "YES\n";
    }
    else{
        cout << "NO\n";
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int t;
    cin >> t;
    while(t--){
        solve1();
    }
    return 0;
}
