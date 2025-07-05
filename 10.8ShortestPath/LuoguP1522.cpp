#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000007;

inline ll sqr(ll x) { return x * x; }
inline db dis(int x1, int y1, int x2, int y2) { 
    return sqrt(sqr(x1 - x2) + sqr(y1 - y2));
}
vector<int> fa;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) {
    u = find(u), v = find(v);
    if(u == v) return;
    fa[u] = v;
}
struct info {
    int x, y;
};
void solve() {
    int n;
    cin >> n;
    fa.resize(n + 1);
    iota(fa.begin(), fa.end(), 0);
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y;
    }
    vector d(n + 1, vector<db>(n + 1, inf));
    for(int i = 1; i <= n; i++) d[i][i] = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            char c;
            cin >> c;
            if(c == '1') {
                merge(i, j);
                d[i][j] = dis(a[i].x, a[i].y, a[j].x, a[j].y);
            }
        }
    }
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            if(d[i][k] > 1e9 + 1) continue;
            for(int j = 1; j <= n; j++) {
                if(d[j][k] > 1e9 + 1) continue;
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
    vector<db> mx(n + 1, 0);
    vector<db> D(n + 1);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(d[i][j] < 1e9) {
                int f = find(i);
                D[f] = max(D[f], d[i][j]);
                mx[i] = max(mx[i], d[i][j]);
            }
        }
    }
    db ans = inf;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(d[i][j] < 1e9) continue;
            ans = min(ans, max({D[find(i)], D[find(j)], mx[i] + mx[j] + dis(a[i].x, a[i].y, a[j].x, a[j].y)}));
        }
    }
    cout << fixed << setprecision(6) << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
