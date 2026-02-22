#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m;
    cin >> n >> m;
    ll h;
    cin >> h;
    vector<ll> p(m + 1), f(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> p[i] >> f[i];
    }

    auto ck = [&](int x) -> bool {
        vector<ll> d1(n + 5), d2(n + 5);

        auto add = [&](int l, int r, ll a1, ll d) {
            d2[l] += a1;
            d2[l + 1] += d - a1;
            d2[r + 1] -= a1 + (r - l + 1) * d;
            d2[r + 2] += a1 + (r - l) * d;
        };

        for(int i = 1; i <= x; i++) {
            int L = max(1LL, p[i] - f[i] + 1);
            int R = p[i];
            if(L <= R) {
                add(L, R, f[i] - (p[i] - L), 1);
            }

            L = R + 1;
            R = min((ll)n, p[i] + f[i] - 1);
            if(L <= R) {
                add(L, R, f[i] - 1, -1);
            }
        }

        for(int i = 1; i <= n; i++) {
            d2[i] += d2[i - 1];
        }

        for(int i = 1; i <= n; i++) {
            d2[i] += d2[i - 1];
        }

        for(int i = 1; i <= n; i++) {
            if(d2[i] > h) {
                return true;
            }
        }

        return false;
    };

    int l = 0, r = m + 1;
    while(l + 1 < r) {
        int mid = l + r >> 1;
        if(ck(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    if(r == m + 1) {
        cout << "No\n";
    } else {
        cout << "Yes\n";
        cout << r << "\n";
    }
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
