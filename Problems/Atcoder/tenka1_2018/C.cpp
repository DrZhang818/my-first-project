#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr ll inf = ll(1E18);

void solve() {  
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }    
    sort(a.begin() + 1, a.end());
    ll ans = 0;
    for(int i = 1; i <= n / 2; i++) {
        ans -= 2 * a[i];
    }
    for(int i = n - n / 2 + 1; i <= n; i++) {
        ans += 2 * a[i];
    }

    if(n % 2 == 0) {
        ans -= abs(a[n / 2] - a[n / 2 + 1]);
    } else {
        ans -= min(abs(a[n / 2] - a[n / 2 + 1]), abs(a[n / 2 + 1] - a[n / 2 + 2]));
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
