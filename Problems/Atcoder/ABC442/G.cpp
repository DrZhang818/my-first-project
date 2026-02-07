#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    ll n, c;
    cin >> n >> c;
    vector<vector<pair<ll,ll>>> a(4);
    for(int i = 1; i <= n; i++) {
        ll w, v, k;
        cin >> w >> v >> k;
        a[w].emplace_back(v, k);
    }

    for(int i = 1; i <= 3; i++) {
        sort(a[i].begin(), a[i].end(), greater());
    }

    auto calc = [&](ll x, ll y, ll z, ll c) -> ll {
        if(x + 2 * y + 3 * z > c) {
            return 0;
        }

        c -= x + 2 * y + 3 * z;

        ll res = 0;

        vector<pair<ll,ll>> b;

        auto add = [&](ll f, ll p) -> void {
            ll cur = 0, cnt = 0;
            ll sz = 6 / f;
            for(int i = 0; i < a[f].size(); i++) {
                auto [v, k] = a[f][i];
                ll t = min(p, k);
                p -= t;
                k -= t;
                res += t * v;
                
                t = min(sz - cnt, k);
                k -= t;
                cnt += t;
                cur += t * v;
                if(cnt == sz) {
                    b.emplace_back(cur, 1);
                    cur = 0;
                    cnt = 0;
                }

                if(k >= sz) {
                    ll num = k / sz;
                    b.emplace_back(v * sz, num);
                    k %= sz;
                }

                cur += v * k;
                cnt += k;
            }
        };

        add(1, x);
        add(2, y);
        add(3, z);

        sort(b.begin(), b.end(), greater());

        c /= 6;

        for(auto [v, k] : b) {
            ll t = min(c, k);
            res += v * t;
            c -= t;
            if(c == 0) {
                break;
            }            
        }

        return res;
    };

    ll ans = 0;

    for(auto x : {0, 1, 2, 3, 4, 5}) {
        for(auto y : {0, 1, 2}) {
            for(auto z : {0, 1}) {
                ans = max(ans, calc(x, y, z, c));
            }
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
