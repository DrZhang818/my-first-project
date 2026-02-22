#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

int query(int k, int idx) {
    cout << "? " << k << endl;
    int q;
    cin >> q;
    int res = -1;
    for(int i = 1; i <= q; i++) {
        int x;
        cin >> x;
        if(i == idx) {
            res = x;
        }
    }
    return res;
}

void solve() {  
    int n;
    cin >> n;

    vector<PII> e;

    auto work = [&](ll L, ll R, int S) {
        if(L == R) return;
        int cur = query(L + 1, 2);
        if(cur == -1) return;
        int l = L + 1, r = R;
        while(l <= r && cur != -1) {
            ll lo = l - 1, hi = r + 1;
            int nxt = -1;
            while(lo + 1 < hi) {
                ll m = lo + hi >> 1;
                int u = query(m, 2);
                if(u == cur) {
                    lo = m;
                } else {
                    hi = m;
                    nxt = u;
                }
            }
            e.emplace_back(S, cur);
            cur = nxt;
            l = lo + 1;
        }
    };

    int l = 1;
    ll mx = numeric_limits<int>::max();
    int cur = 1;
    while(cur <= n) {
        ll lo = l - 1, hi = mx;
        while(lo + 1 < hi) {
            ll m = lo + hi >> 1;
            int res = query(m, 1);
            if(res == -1) {
                mx = m;
            }
            if(res == cur) {
                lo = m;
            } else {
                hi = m;
            }
        }
        work(l, lo, cur);
        l = lo + 1;
        cur++;
    }

    cout << "! " << e.size() << endl;
    for(auto [u, v] : e) {
        cout << u << " " << v << endl;
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
