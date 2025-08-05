#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/677/problem/D
void chmin(int &x, int y) {
    if(x > y) {
        x = y;
    }
}
inline int lowbit(int o) { return o & -o; }
class BIT {
    vector<vector<int>> tr;
    int n, m;
public:
    BIT(int a, int b) : tr(a + 1, vector<int>(b + 1, inf)), n(a), m(b){}
    void add(int x, int y, int d) {
        for(int i = x; i <= n; i += lowbit(i)) {
            for(int j = y; j <= m; j += lowbit(j)) {
                chmin(tr[i][j], d);
            }
        }
    }
    void clear(int x, int y) {
        for(int i = x; i <= n; i += lowbit(i)) {
            for(int j = y; j <= m; j += lowbit(j)) {
                tr[i][j] = inf;
            }
        }
    }
    int query(int x, int y) {
        int res = inf;
        for(int i = x; i > 0; i -= lowbit(i)) {
            for(int j = y; j > 0; j -= lowbit(j)) {
                chmin(res, tr[i][j]);
            }
        }
        return res;
    }
};
struct info {
    int x, y, d;
};
void solve() {
    int n, m, p;
    cin >> n >> m >> p;
    vector<vector<info>> a(p + 1);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            int x;
            cin >> x;
            a[x].emplace_back(i, j, inf);
        }
    }
    a[0].emplace_back(1, 1, 0);
    vector<BIT> tr(4, BIT(n, m));
    for(int i = 1; i <= p; i++) {
        for(auto [x, y, d] : a[i - 1]) {
            tr[0].add(x, y, d - x - y);
            tr[1].add(n - x + 1, y, d + x - y);
            tr[2].add(x, m - y + 1, d - x + y);
            tr[3].add(n - x + 1, m - y + 1, d + x + y);
        }
        for(auto &[x, y, d] : a[i]) {
            chmin(d, tr[0].query(x, y) + x + y);
            chmin(d, tr[1].query(n - x + 1, y) - x + y);
            chmin(d, tr[2].query(x, m - y + 1) + x - y);
            chmin(d, tr[3].query(n - x + 1, m - y + 1) - x - y);
        }
        for(auto [x, y, d] : a[i - 1]) {
            tr[0].clear(x, y);
            tr[1].clear(n - x + 1, y);
            tr[2].clear(x, m - y + 1);
            tr[3].clear(n - x + 1, m - y + 1);
        }
    }
    cout << a[p][0].d << "\n";
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
