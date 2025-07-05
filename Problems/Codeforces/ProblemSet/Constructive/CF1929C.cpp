#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    ll k, x, a;
    cin >> k >> x >> a;
    ll need = 1;
    for(int i = 2; i <= x + 1; i++) {
        need += need / (k - 1) + 1;
        if(need > a) break;
    }    
    if(a >= need) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main()  
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
