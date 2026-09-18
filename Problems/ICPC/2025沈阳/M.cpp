#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;
constexpr int N = 1E6;

void solve() {
    array<int, 16> a{}, b{};
    for(int i = 8; i <= 15; i++) {
        cin >> a[i] >> b[i];
    }

    array<vector<int>, 16> son{};
    auto build = [&](auto&& self, int u) -> void {
        if(u >= 8) {
            son[u].push_back(u);
            return;
        }
        self(self, u << 1);
        self(self, u << 1 | 1);
        son[u].insert(son[u].end(), son[u << 1].begin(), son[u << 1].end());
        son[u].insert(son[u].end(), son[u << 1 | 1].begin(), son[u << 1 | 1].end());
    };
    build(build, 1);

    vector<int> p(16);
    iota(p.begin(), p.end(), 0);

    db ans = 0;
    auto work = [&]() -> void {
        array<db, 16> dp {};
        fill(dp.begin() + 8, dp.end(), 1);
        auto dfs = [&](auto&& self, int u) -> void {
            if(u >= 8) return;
            int ls = u << 1;
            int rs = u << 1 | 1;
            self(self, ls);
            self(self, rs);
            vector<int> L, R;
            array<int, 16> pos {};
            for(int l : son[ls]) {
                L.push_back(p[l]);
                pos[p[l]] = l;
            }
            for(int r : son[rs]) {
                R.push_back(p[r]);
                pos[p[r]] = r;
            }
            // cerr << "!: " << u << "\n";
            // for(int l : L) {
            //     cerr << l << " \n"[l == L.back()];
            // }
            // for(int r : R) {
            //     cerr << r << " \n"[r == R.back()];
            // }
            
            array<db, 16> ndp {};
            for(int l : L) {
                for(int r : R) {
                    int x = pos[l] < pos[r] ? a[l] : b[l];
                    int y = pos[r] < pos[l] ? a[r] : b[r];
                    db q = db(x) / (x + y);
                    // cerr << "l: " << l << " r: " << r << " p: " << p << "\n";
                    ndp[l] += dp[l] * dp[r] * q;
                    ndp[r] += dp[l] * dp[r] * (1 - q);
                }
            }
            for(int x : son[u]) {
                dp[p[x]] = ndp[p[x]];
            }
            // cerr << "!: " << u << "\n";
            // for(int i = 8; i < 16; i++) {
            //     cerr << dp[i] << " \n"[i == 15];
            // }
        };
        dfs(dfs, 1);
        ans = max(ans, dp[8]);
    };

    do {
        work();
    } while(next_permutation(p.begin() + 8, p.end()));

    cout << fixed << setprecision(15) << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}