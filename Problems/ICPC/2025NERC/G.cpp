#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr ll inf = 1E18;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    if(n == 2) {
        cout << a[1] << "\n";
        return;
    }
    ll x = 0;
    for(int i = 1; i <= n; i++) {
        if(i & 1) {
            x += a[i];
        } else {
            x -= a[i];
        }
    }
    if(n & 1) {
        vector<int> val(n + 1);
        val[1] = x / 2;
        for(int i = 1; i < n; i++) {
            x = 2 * a[i] - x;
            val[i + 1] = x / 2;
        }
        ll sum = accumulate(val.begin() + 1, val.end(), 0LL);
        int mx = *max_element(val.begin() + 1, val.end());
        int ans = max((ll)mx, (sum + n - 2) / (n - 1));
        cout << ans << "\n";
    } else {
        ll l = 0, r = inf;
        ll pmx = 0, nmx = -inf;
        x += a[n];
        ll tx = x;
        for(int i = 1; i < n; i++) {
            if(i & 1) {
                r = min(r, x);
                nmx = max(nmx, x);
            } else {
                l = max(l, -x);
                pmx = max(pmx, x);
            }
            x = a[i] - x;
        }
        ll balance = (nmx - pmx) / 2;
        int ans = INT_MAX;
        auto upd = [&](ll v) {
            x = tx;
            vector<int> val(n + 1);
            for(int i = 1; i <= n; i++) {
                if(i & 1) {
                    val[i] = x - v;
                } else {
                    val[i] = x + v;
                }
                x = a[i] - x;
            }
            ll sum = accumulate(val.begin() + 1, val.end(), 0LL);
            int mx = *max_element(val.begin() + 1, val.end());
            ans = min((ll)ans, max((ll)mx, (sum + n - 2) / (n - 1)));
        };
        if(r <= balance) {
            upd(r);
        } else if(l > balance) {
            upd(l);
        } else {
            upd(balance);
            upd(balance + 1);
        }
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
