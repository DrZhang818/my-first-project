#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    int n, m, l, x, y;
    cin >> n >> m >> l >> x >> y;
    vector<array<int,2>> Line(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> Line[i][0] >> Line[i][1];
    }
    vector<array<int,2>> pos(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> pos[i][0];
        pos[i][1] = i;
    }
    sort(pos.begin() + 1, pos.end());
    sort(Line.begin() + 1, Line.end());
    
    double cur = inf;
    int j = 1;
    vector<db> ans(m + 1);
    for(int i = 1; i <= m; i++) {
        while(j <= n && Line[j][0] <= pos[i][0]) {
            cur = min(cur, db(Line[j][1] - Line[j][0]) / x + db(l - Line[j][1]) / y);
            j++;
        }
        ans[pos[i][1]] = min(cur, db(l - pos[i][0]) / y);
    }
    for(int i = 1; i <= m; i++) {
        cout << ans[i] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cout << fixed << setprecision(12);
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
