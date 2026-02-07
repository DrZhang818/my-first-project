#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr ll inf = ll(1E18);

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<vector<char>> a(n + 1, vector<char>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    vector<int> lo(n + m), hi(n + m);
    for(int s = 1; s <= n + m - 1; s++) {
        lo[s] = max(1, s - m + 1);
        hi[s] = min(n, s);
    }

    auto work = [&](int tag) -> ll {
        vector<vector<int>> pre(n + m, vector<int>(n + m));
        for(int s = 1; s < n + m; s++) {
            for(int i = lo[s]; i <= hi[s]; i++) {
                pre[s][i] = pre[s][i - 1] + (a[i][s + 1 - i] == '#');
            }
        }
        auto cal = [&](int s, int l, int r) {
            if(s < 1 || s >= n + m) return 0;
            if(tag) l++, r--;
            l = max(lo[s], l);
            r = min(hi[s], r);
            if(r < l) return 0;
            return pre[s][r] - pre[s][l - 1];
        };
        ll ans = 0;
        for(int s = 1; s < n + m; s++) {
            for(int x1 = lo[s]; x1 <= hi[s]; x1++) {
                int y1 = s + 1 - x1;
                if(a[x1][y1] != '#') continue;
                for(int x2 = x1 - 1; x2 >= lo[s]; x2--) {
                    int y2 = s + 1 - x2;
                    if(a[x2][y2] != '#') continue;
                    int r = x1 - x2;
                    int ns = x2 + y2 - 2 * r - 1;
                    ans += cal(ns, x1 - 2 * r, x2);
                    ns = x1 + y1 + 2 * r - 1;
                    ans += cal(ns, x1, x2 + 2 * r);
                }
            }
        }
        return ans;
    };

    ll ans = 0;
    ans += work(0);
    for(int i = 1; i <= n; i++) {
        reverse(a[i].begin() + 1, a[i].end());
    }
    ans += work(1);

    cout << ans << "\n";
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
