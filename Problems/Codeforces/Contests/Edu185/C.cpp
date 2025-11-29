#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    int n;
    ll k;
    cin >> n >> k;
    vector<ll> q(n + 1), r(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> q[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> r[i];
    }
    sort(q.begin() + 1, q.end());
    sort(r.begin() + 1, r.end());
    int ans = 0;
    for(int i = n, j = 1; i >= 1; i--) {
        if(j > n) {
            break;
        }
        if(q[i] * (r[j] + 1) + r[j] <= k) {
            ans++;
            j++;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
