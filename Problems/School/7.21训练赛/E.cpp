#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m, q, k;
    cin >> n >> m >> q >> k;
    vector<int> r(n + 1), c(m + 1);
    while(q--) {
        int op, x;
        cin >> op >> x;
        if(op == 1) {
            r[x] = (r[x] + 1) % k;
        } else {
            c[x] = (c[x] + 1) % k;
        }
    }
    vector<int> r_cnt(k), c_cnt(k);
    for(int i = 1; i <= n; i++) {
        r_cnt[r[i]]++;
    }
    for(int i = 1; i <= m; i++) {
        c_cnt[c[i]]++;
    }
    ll ans = 0;
    for(int s = 0; s < k; s++) {
        ans += 1LL * r_cnt[s] * (m - c_cnt[(k - s) % k]);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
