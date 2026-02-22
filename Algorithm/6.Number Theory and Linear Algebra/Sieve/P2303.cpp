#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    ll n;
    cin >> n;
    vector<ll> fac;
    for(ll i = 1; i * i <= n; i++) {
        if(n % i) continue;
        fac.push_back(i);
        if(i != n / i) {
            fac.push_back(n / i);
        }
    }
    sort(fac.begin(), fac.end());
    int m = fac.size();
    vector<ll> dp(m);
    for(int i = 0; i < m; i++) {
        dp[i] = n / fac[i];
    }
    for(int i = m - 1; i >= 0; i--) {
        for(int j = i + 1; j < m; j++) {
            if(fac[j] % fac[i] == 0) {
                dp[i] -= dp[j];
            }
        }
    }
    ll ans = 0;
    for(int i = 0; i < m; i++) {
        ans += fac[i] * dp[i];
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
