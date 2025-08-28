#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> a(n + 1), b(m + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= m; i++) {
        cin >> b[i];
    }
    sort(a.begin() + 1, a.end());
    sort(b.begin() + 1, b.end());

    auto ck = [&](int mid, int x, int y, int z) -> bool {
        int c1 = lower_bound(a.begin() + 1, a.end(), mid) - a.begin();
        int c2 = lower_bound(b.begin() + 1, b.end(), mid) - b.begin();
        c1 = min(n - c1 + 1, x);
        c2 = min(m - c2 + 1, y);
        return c1 + c2 >= z;
    };

    vector<ll> sufa(n + 2), sufb(m + 2);
    for(int i = n; i >= 1; i--) {
        sufa[i] = sufa[i + 1] + a[i];
    } 
    for(int i = m; i >= 1; i--) {
        sufb[i] = sufb[i + 1] + b[i];
    }

    while(q--) {
        int x, y, z;
        cin >> x >> y >> z;
        int l = 0, r = inf + 1;
        while(l + 1 < r) {
            int mid = l + r >> 1;
            if(ck(mid, x, y, z)) {
                l = mid;
            } else {
                r = mid;
            }
        }
        int c1 = upper_bound(a.begin() + 1, a.end(), l) - a.begin();
        int c2 = upper_bound(b.begin() + 1, b.end(), l) - b.begin();
        c1 = max(c1, n - x + 1);
        c2 = max(c2, m - y + 1);
        ll ans = sufa[c1] + sufb[c2];
        int rem = z - (n - c1 + 1) - (m - c2 + 1);
        ans += 1LL * l * rem;
        cout << ans << "\n";
    }
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
