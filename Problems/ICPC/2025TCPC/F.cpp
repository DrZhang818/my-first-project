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
    vector<int> p(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> p[i];
    }    
    vector<int> pre(n + 1), suf(n + 2);
    for(int i = 1; i <= n; i++) {
        pre[i] = gcd(pre[i - 1], p[i]);
    }
    for(int i = n; i >= 1; i--) {
        suf[i] = gcd(suf[i + 1], p[i]);
    }
    ll ans = pre[n];
    for(int i = 2; i < n; i++) {
        ans += min(pre[i], suf[i]);
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
