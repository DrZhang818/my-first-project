#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

vector<int> fa;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) {
    u = find(u), v = find(v);
    if(u == v) return;
    fa[u] = v;
}
struct info {
    ll x, y, r;
};
ll cal(ll x, ll y) {
    return x * x + y * y;
}
bool ck(ll x1, ll y1, ll x, ll y, ll r) {
    return cal(x1 - x, y1 - y) == r * r;
}
void solve() {
    int n;
    cin >> n;
    int sx, sy, tx, ty;
    cin >> sx >> sy >> tx >> ty;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y >> a[i].r;
    }
    fa.resize(n + 1);
    iota(fa.begin(), fa.end(), 0);
    int sid = -1, tid = -1;
    for(int i = 1; i <= n; i++) {
        auto [x1, y1, r1] = a[i];
        if(ck(sx, sy, x1, y1, r1)) {
            sid = i;
        }
        if(ck(tx, ty, x1, y1, r1)) {
            tid = i;
        }
        for(int j = i + 1; j <= n; j++) {
            auto [x2, y2, r2] = a[j];
            ll dis = cal(x1 - x2, y1 - y2);
            db d = sqrt(dis);
            ll up = (r1 + r2) * (r1 + r2);
            if(dis + 2 * r1 * d + r1 * r1 >= r2 * r2 && dis + 2 * r2 * d + r2 * r2 >= r1 * r1 && dis <= up) {
                merge(i, j);
            }
        }
    }
    if(find(sid) == find(tid)) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
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
