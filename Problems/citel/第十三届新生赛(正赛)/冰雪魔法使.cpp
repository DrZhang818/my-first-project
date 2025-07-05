#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;



void solve(){
    ll a, b;
    cin >> a >> b;
    ll lo = 1;
    ll t = b - a;
    while(lo < b){
        lo *= 6;
    }
    while((b + lo - 1) / lo - (a + lo - 1) / lo == 0){
        lo /= 6;
    }
    cout << (b + lo - 1) / lo - (a + lo - 1) / lo + 1 << "\n";
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