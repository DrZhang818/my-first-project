#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

void solve(){
    ll n;
    cin >> n;
    ll count = 1;
    while(n >= 4){
        count <<= 1;
        n /= 4;
    }
    cout << count << "\n";
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
