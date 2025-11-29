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
    vector<pair<string,int>> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    string x;
    cin >> x;
    ll ans = 0;
    for(int i = 1, ok = 0; i <= n; i++) {
        auto &[s, t] = a[i];
        if(ok) {
            ans += t;
        }
        if(!ok && s == x) {
            ok = 1;
        }
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
