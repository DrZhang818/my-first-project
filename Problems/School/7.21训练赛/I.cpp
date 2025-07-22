#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    sort(a.begin() + 1, a.end(), greater());
    sort(b.begin() + 1, b.end(), greater());
    auto ck = [&](int x) -> bool {
        ll tot = n + x;
        tot -= tot / 4;
        ll res1 = 0, res2 = 0;
        if(x >= tot) {
            res1 = 100 * tot;
        } else {
            res1 = 100 * x;
            for(int i = 1; i <= tot - x; i++) {
                res1 += a[i];
            }
        }
        for(int i = 1; i <= min(tot, (ll)n); i++) {
            res2 += b[i];
        }
        return res1 >= res2;
    };
    int l = -1, r = inf;
    while(l + 1 < r) {
        int mid = l + (r - l) / 2;
        if(ck(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << r << "\n";
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
