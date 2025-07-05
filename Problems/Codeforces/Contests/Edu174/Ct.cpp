#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


const int inf = 1e9;
const int MOD = 998244353;
ll power_pow(ll a, ll b, ll mod){
    ll res = 1;
    a %= mod;
    while(b > 0){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
void solve(){ 
    int n;
    cin >> n;
    vector<int> a(n + 1);
    a[0] = inf;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    ll c1 = 0, pair = 0, ans = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] == 1) {
            c1 += 1;
        } else if(a[i] == 2) {
            pair = 2 * pair + c1;
            pair %= MOD;
        } else {
            ans += pair;
            ans %= MOD;
        }
    }
    cout << ans << "\n";
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
    
