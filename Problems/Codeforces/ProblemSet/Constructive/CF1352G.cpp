#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;

//https://codeforces.com/problemset/problem/1352/G
/*
    构造
    

*/
void solve(){
    int n;
    cin >> n;
    if(n < 4){
        cout << -1 << "\n";
        return;
    }
    if(n == 4){
        cout << "3 1 4 2\n";
        return;
    }
    int i = 1;
    for(; i <= n; i += 2){
        cout << i << " ";
    }
    int p = i - 5;
    cout << p << " ";
    for(i = (n%2==0?n:n-1); i >= 2; i -= 2){
        if(i == p) continue;
        cout << i << " ";
    }
    cout << "\n";
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