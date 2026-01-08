#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, q;
    cin >> n >> q;
    const int N = __lg(n) + 1;

    vector<PII> Q(q + 1);
    for(int i = 1; i <= q; i++) {
        cin >> Q[i].first >> Q[i].second;
    }

    vector<ll> a(n + 1), d1(n + 5), d2(n + 5);
    vector<ll> ans(n + 1);
    for(int s = 0; s < N; s++) {
        ll st = (1 << s) - 1;
        ll len = 1 << s + 1;
        ll a1 = 1LL << 2 * s;
        ll d = 1LL << 2 * s + 1;
        for(int i = 1; i <= q; i++) {
            auto [l, r] = Q[i];
            int L = l + st;
            if(L > r) continue;
            int k = (r - L + len) / len;
            int R = L + k * len;
            d2[L] += a1;
            if(L + len <= n) {
                d2[L + len] += d - a1;
            }
            if(R <= n) {
                d2[R] -= a1 + k * d;
            }
            if(R + len <= n) {
                d2[R + len] += a1 + (k - 1) * d;
            }
        }
        for(int i = 1; i <= n; i++) {
            d1[i] = d2[i];
            if(i - len >= 1) {
                d1[i] += d1[i - len];
            }
        }
        for(int i = 1; i <= n; i++) {
            a[i] = d1[i];
            if(i - len >= 1) {
                a[i] += a[i - len];
            }
            ans[i] += a[i];
        }
        for(int i = 1; i <= n; i++) {
            a[i] = 0;
            d1[i] = 0;
            d2[i] = 0;
        }
    }

    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
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
