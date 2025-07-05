#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    ll n, a, b, c;
    cin >> n >> a >> b >> c;
    ll sum = a + b + c;
    ll p = n % sum;
    ll cur = n / sum;
    if(p == 0) {
        cout << 3 * cur << "\n";
        return ;
    }
    if(p <= a){
        cout << 3 * cur + 1 << "\n";
        return;
    }
    p -= a;
    if(p <= b){
        cout << 3 * cur + 2 << "\n";
        return;
    }
    cout << 3 * cur + 3 << "\n";

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
