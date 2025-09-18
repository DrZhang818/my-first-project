#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

struct info {
    int l, r;
};
void solve() {
    int n;
    cin >> n;
    ll ans = 0;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        int l, r;
        cin >> l >> r;
        ans += r - l;
        a[i].l = l;
        a[i].r = r;
    }
    sort(a.begin() + 1, a.end(),
        [&](auto x, auto y) {
            return -x.l - x.r > -y.l - y.r;
        });
    vector<ll> preL(n + 1), preR(n + 1);
    for(int i = 1; i <= n; i++) {
        preL[i] = preL[i - 1] + a[i].l;
        preR[i] = preR[i - 1] + a[i].r;
    }
    if(n % 2 == 0) {
        ans += preR[n] - preR[n / 2] - preL[n / 2];
    } else {
        ll mx = 0;
        for(int i = 1; i <= n; i++) {
            ll cur = 0;
            if(i <= n / 2) {
                cur -= preL[n / 2 + 1] - a[i].l;
                cur += preR[n] - preR[n / 2 + 1];
            } else {
                cur -= preL[n / 2];
                cur += preR[n] - preR[n / 2] - a[i].r;
            }
            mx = max(mx, cur);
        }
        ans += mx;
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
