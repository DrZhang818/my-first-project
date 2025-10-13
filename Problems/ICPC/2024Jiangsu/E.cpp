#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int x, id;
    friend bool operator < (const info &a, const info &b) {
        return a.x < b.x;
    }
};
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a;
    vector<int> pos {0};
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        while(x) {
            a.push_back(x);
            x >>= 1;
        }
        pos.push_back(a.size());
    }

    vector<int> L(q), R(q), K(q), ans(q);
    vector<info> Q(2 * q);

    for(int i = 0; i < q; i++) {
        cin >> L[i] >> R[i] >> K[i];
        L[i]--;
        L[i] = pos[L[i]];
        R[i] = pos[R[i]];
        K[i]++;
        Q[i << 1] = {L[i], i};
        Q[i << 1 | 1] = {R[i], i};
    }
    sort(Q.begin(), Q.end());

    int mx = ranges::max(a);
    n = a.size();
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);

    vector<int> val(q);

    auto work = [&](this auto &&self, int l, int r, int al, int ar, int ql, int qr) -> void {
        if(r - l == 1) {
            for(int i = ql; i < qr; i++) {
                ans[Q[i].id] = l;
            }
            return;
        }
        int mid = l + r >> 1;
        int am = stable_partition(p.begin() + al, p.begin() + ar, 
            [&](int i) {
                return a[i] < mid;
            }) - p.begin();

        for(int i = ql, j = am; i < qr; i++) {
            auto [x, id] = Q[i];
            while(j < ar && p[j] < x) {
                j++;
            }
            if(x == L[id]) {
                val[id] = -j;
            } else {
                val[id] += j;
            }
        }

        int qm = stable_partition(Q.begin() + ql, Q.begin() + qr, 
            [&](auto t) {
                return val[t.id] < K[t.id];
            }) - Q.begin();
        for(int i = ql; i < qm; i++) {
            auto [x, id] = Q[i];
            K[id] -= val[id];
            val[id] = 0;
        }
        self(l, mid, al, am, ql, qm);
        self(mid, r, am, ar, qm, qr);
    };

    work(0, mx + 1, 0, n, 0, 2 * q);

    for(int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
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
