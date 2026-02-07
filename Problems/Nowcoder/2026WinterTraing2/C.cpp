#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

vector<int> fa;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if(u == v) return;
    fa[v] = u;
}

void solve() {  
    int n, q;
    cin >> n >> q;
    vector<int> x(n), y(n);
    vector<int> val = {0, inf};
    for(int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        val.push_back(x[i]);
        val.push_back(x[i] + 1);
    }

    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());

    int m = val.size();
    vector<vector<int>> points(m);

    for(int i = 0; i < n; i++) {
        x[i] = lower_bound(val.begin(), val.end(), x[i]) - val.begin();
        points[x[i]].push_back(y[i]);
    }

    vector<vector<array<int,3>>> seg(m);

    int cnt = 0;
    for(int i = 0; i < m; i++) {
        sort(points[i].begin(), points[i].end());
        points[i].push_back(inf);

        int las = 0;
        for(int y : points[i]) {
            if(y > las) {
                seg[i].push_back({las, y, cnt++});
            }
            las = y + 1;
        }
    }

    fa.resize(cnt);
    iota(fa.begin(), fa.end(), 0);

    for(int i = 1; i < m; i++) {
        int x = 0, y = 0;
        auto& a = seg[i - 1];
        auto& b = seg[i];

        while(x < a.size() && y < b.size()) {
            if(a[x][1] < b[y][1]) {
                if(a[x][1] > b[y][0]) {
                    merge(a[x][2], b[y][2]);
                }
                x++;
            } else {
                if(b[y][1] > a[x][0]) {
                    merge(a[x][2], b[y][2]);
                }
                y++;
            }
        }
    }

    while(q--) {
        int x, y;
        cin >> x >> y;

        int i = upper_bound(val.begin(), val.end(), x) - val.begin() - 1;
        int j = lower_bound(seg[i].begin(), seg[i].end(), array {y + 1, 0, 0}) - seg[i].begin() - 1;
    
        if(find(0) == find(seg[i][j][2])) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
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
