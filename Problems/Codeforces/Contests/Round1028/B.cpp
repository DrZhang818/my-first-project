#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

const ll MOD = 998244353;
ll power_pow(ll a, ll b){
    ll res = 1;
    a %= MOD;
    while(b > 0){
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
void solve() {
    int n;
    cin >> n;
    vector<ll> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> b[i];
    ll idx1 = 1, idx2 = 1, mx1 = -1, mx2 = -1;
    vector<ll> ans(n + 1);
    for(int i = 1; i <= n; i++) {
        if(a[i] > mx1) idx1 = i, mx1 = a[i];
        if(b[i] > mx2) idx2 = i, mx2 = b[i];
        ll t1 = (power_pow(2, a[idx1]) + power_pow(2, b[i - idx1 + 1])) % MOD;
        ll t2 = (power_pow(2, b[idx2]) + power_pow(2, a[i - idx2 + 1])) % MOD;
        if(a[idx1] > b[idx2]) {
            ans[i] = t1;
        } else if(a[idx1] < b[idx2]) {
            ans[i] = t2;
        } else if(a[idx1] + b[i - idx1 + 1] > b[idx2] + a[i - idx2 + 1]) {
            ans[i] = t1;
        } else {
            ans[i] = t2;
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
