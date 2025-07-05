#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://codeforces.com/problemset/problem/1372/C
/*
    构造 || 贪心
    题意:
        给定一个长度为n的排列, 你可以进行以下操作
        op: 

*/
void solve(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int ans = 0;
    for(int i = 1; i <= n; i++){
        if(a[i - 1] != i) {
            ans++;
            for(; a[i - 1] != i && i <= n; i++);
        }
    }
    if(ans >= 2){
        cout << 2 << "\n";
    }else{
        cout << ans << "\n";
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
