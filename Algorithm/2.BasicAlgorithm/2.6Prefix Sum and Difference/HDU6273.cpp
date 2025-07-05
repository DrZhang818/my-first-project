#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


constexpr ll MOD = 998244353;
constexpr ll inf = 1e18;
ll pow_mod(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while(b) {
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
void solve() { 
    int n, m;
    cin >> n >> m;
    vector<ll> c2(n + 2), c3(n + 2);
    while(m--) {
        int l, r, tag;
        cin >> l >> r >> tag;
        if(tag == 2) {
            c2[l]++;
            c2[r + 1]--;
        } else {
            c3[l]++;
            c3[r + 1]--;
        }
    }
    ll m2 = inf, m3 = inf;
    for(int i = 1; i <= n; i++) {
        c2[i] += c2[i - 1];
        c3[i] += c3[i - 1];
        m2 = min(m2, c2[i]);
        m3 = min(m3, c3[i]);
    }
    ll ans = pow_mod(2LL, m2) * pow_mod(3LL, m3) % MOD;
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
    
