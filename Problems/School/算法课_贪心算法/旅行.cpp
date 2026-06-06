#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n, m;
    i64 V;
    cin >> n >> m >> V;
    vector<int> L(m + 1), R(m + 1);
    vector<i64> t(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> L[i] >> R[i] >> t[i];
    }

    i64 ans = 0;
    vector<i64> cur(n + 1);

    auto dfs = [&](auto&& self, int i, i64 sum) -> void {
        if(i == m + 1) {
            ans = max(ans, sum);
            return;
        }
        self(self, i + 1, sum);
        bool ok = true;
        for(int j = L[i]; j < R[i]; j++) {
            cur[j] += t[i];
            if(cur[j] > V) ok = false;
        }
        if(ok) {
            self(self, i + 1, sum + t[i] * (R[i] - L[i]));
        }
        for(int j = L[i]; j < R[i]; j++) {
            cur[j] -= t[i];
        }
    };
    dfs(dfs, 1, 0);

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}