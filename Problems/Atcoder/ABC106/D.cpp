#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

inline int lowbit(int o) { return o & -o; }
vector<int> tr;
int n;
void add(int o, int d) {
    for(; o <= n; o += lowbit(o)) {
        tr[o] += d;
    }
}
int query(int o) {
    int res = 0;
    for(; o > 0; o -= lowbit(o)) {
        res += tr[o];
    }
    return res;
}
struct info {
    int l, r, id = 0;
    friend bool operator < (const info &a, const info &b) {
        return a.l < b.l;
    }
};
void solve() {
    int m, q;
    cin >> n >> m >> q;
    tr.resize(n + 1);
    vector<info> a(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> a[i].l >> a[i].r;
    }
    vector<info> Q(q + 1);
    for(int i = 1; i <= q; i++) {
        cin >> Q[i].l >> Q[i].r;
        Q[i].id = i;
    }
    sort(a.begin() + 1, a.end());
    sort(Q.begin() + 1, Q.end());
    int pos = m;
    vector<int> ans(q + 1);
    for(int i = q; i >= 1; i--) {
        auto [L, R, id] = Q[i];
        while(a[pos].l >= L) {
            add(a[pos].r, 1);
            pos--;
        }
        ans[id] = query(R);
    }
    for(int i = 1; i <= q; i++) {
        cout << ans[i] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
