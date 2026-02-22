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
    vector<ll> val {0};
    for(ll x = 1; x <= n; x *= 2) {
        for(ll y = 1; x * y <= n; y *= 5) {
            val.push_back(x * y);
        }
    }
    sort(val.begin() + 1, val.end());
    auto cal = [&](ll x) {
        return x - x / 2 - x / 5 + x / 10;
    };
    ll ans = 0;
    for(ll L = 1, R; L <= n; L = R + 1) {
        R = n / (n / L);
        auto p = lower_bound(val.begin() + 1, val.end(), (n + L) / L) - val.begin() - 1;
        ans += n / L * (cal(R) - cal(L - 1)) * p;
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
