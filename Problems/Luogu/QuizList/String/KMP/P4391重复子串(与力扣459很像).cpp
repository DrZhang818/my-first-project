#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://www.luogu.com.cn/problem/P4391
/*
    本题与力扣459思路很像，可以结合学习
    
*/
void solve(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> lps(n);
    int cur = 0;
    for(int i = 1; i < n; i++){
        while(cur > 0 && s[i] != s[cur]){
            cur = lps[cur - 1];
        }
        if(s[i] == s[cur]){
            lps[i] = ++cur;
        }
    }
    cout << n - lps[n - 1] << "\n"; 
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    solve();
    return 0;    
}
