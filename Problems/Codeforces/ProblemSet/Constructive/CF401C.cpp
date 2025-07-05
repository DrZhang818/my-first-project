#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
 

//https://codeforces.com/problemset/problem/401/C
/*
    构造

*/
void solve(){
    int n, m;
    cin >> m >> n;
    if(m == n + 1){
        cout << 0;
        m -= 1;
    }
    if(n >= 2 * m + 3 || m > n){
        cout << -1 << "\n";
        return;
    }
    for(int i = 0; i < m; i++){
        if(n > (m - i)){
            cout << "110";
            n -= 2;
        }else{
            cout << "10";
            n -= 1;
        }
    }
    while(n--){
        cout << 1;
    }
    cout << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;  
}