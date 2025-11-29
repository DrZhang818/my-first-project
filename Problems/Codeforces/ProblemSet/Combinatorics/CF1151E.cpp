#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }    
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        ans += 1LL * a[i] * (n - a[i] + 1);
    }
    for(int i = 1; i < n; i++) {
        int l = min(a[i], a[i + 1]);
        int r = max(a[i], a[i + 1]);
        ans -= 1LL * l * (n - r + 1);
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
