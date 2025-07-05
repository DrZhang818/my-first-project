#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1e9 + 7;

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    vector<ll> suf(n + 2);
    ll ans = 0;
    for(int i = 0; i < 60; i++) {
        for(int j = n; j >= 1; j--) {
            suf[j] = suf[j + 1];
            if(a[j] >> i & 1) {
                suf[j] += 1;
            }
        }
        for(int j = 1; j <= n; j++) {
            if(a[j] >> i & 1) {
                ans = (ans + (1LL << i) % MOD * (n - j - suf[j + 1]) % MOD) % MOD;
            } else {
                ans = (ans + (1LL << i) % MOD * suf[j + 1] % MOD) % MOD;
            }   
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
