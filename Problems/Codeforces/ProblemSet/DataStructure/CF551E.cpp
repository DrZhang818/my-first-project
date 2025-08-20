#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    ll val;
    int pos;
    friend bool operator < (const info &a, const info &b) {
        if(a.val != b.val) return a.val < b.val;
        return a.pos < b.pos;
    }
};
void solve() {
    int n, q;
    cin >> n >> q;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int block = ceil(sqrt((db)n / 5));
    if(block == 0) block = 1;
    int sz = (n + block - 1) / block;
    vector<vector<info>> sorted_a(sz + 1);
    vector<ll> d(sz + 1);
    vector<int> id(n + 1);
    for(int i = 1; i <= sz; i++) {
        int L = (i - 1) * block + 1, R = min(n, i * block);
        for(int j = L; j <= R; j++) {
            id[j] = i;
            sorted_a[i].emplace_back(a[j], j);
        }
        sort(sorted_a[i].begin(), sorted_a[i].end());
    }
    auto update = [&](int bid, int L, int R, int x) {
        int l = (bid - 1) * block + 1;
        for(int i = (bid - 1) * block + 1; i <= bid * block && i <= n; i++) {
            a[i] += d[bid];
            if(L <= i && i <= R) {
                a[i] += x;
            }
            sorted_a[bid][i - l].val = a[i];
            sorted_a[bid][i - l].pos = i;
        }
        d[bid] = 0;
        sort(sorted_a[bid].begin(), sorted_a[bid].end());
    };

    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            int lbid = id[l], rbid = id[r];
            for(int i = lbid + 1; i < rbid; i++) {
                d[i] += x;
            }
            update(lbid, l, min(r, lbid * block), x);
            if(rbid != lbid) {
                update(rbid, (rbid - 1) * block + 1, r, x);
            }
        } else {
            int y;
            cin >> y;
            int l = inf, r = -inf;
            for(int i = 1; i <= sz; i++) {
                ll bias = d[i];
                auto it = lower_bound(sorted_a[i].begin(), sorted_a[i].end(), info(y - bias, -1)) - sorted_a[i].begin();
                if(it < 0 || it >= sorted_a[i].size() || sorted_a[i][it].val != y - bias) continue;
                l = sorted_a[i][it].pos;
                break;
            }
            if(l == inf) {
                cout << -1 << "\n";
                continue;
            }
            for(int i = sz; i >= 1; i--) {
                ll bias = d[i];
                auto it = lower_bound(sorted_a[i].begin(), sorted_a[i].end(), info(y - bias + 1, -1)) - sorted_a[i].begin() - 1;
                if(it < 0 || it >= sorted_a[i].size() || sorted_a[i][it].val != y - bias) continue;
                r = sorted_a[i][it].pos;
                break;
            }
            cout << r - l << "\n";
        }
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
    