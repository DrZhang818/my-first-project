#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

int L[60], R[60];
i64 dp[60];

i64 dfs(int pos, bool lead, bool limL, bool limR) {
    if(pos == 0) {
        return 1;
    }

    if(!lead && !limL && !limR && dp[pos] != -1) {
        return dp[pos];
    }

    int lo = limL ? L[pos] : 0;
    int hi = limR ? R[pos] : 2;

    i64 res = 0;
    for(int i = lo; i <= hi; i++) {
        if(lead && i == 0) {
            res = max(res, dfs(pos - 1, lead, limL && i == lo, limR && i == hi));
        } else {
            res = max(res, dfs(pos - 1, false, limL && i == lo, limR && i == hi) + i + (!lead));
        }
    }

    if(!lead && !limL && !limR) {
        dp[pos] = res;
    }

    return res;
}

void solve() {
    i64 l, r;
    cin >> l >> r;

    int i = 0, j = 0;
    while(l) {
        L[++i] = l % 3;
        l /= 3;
    }
    while(r) {
        R[++j] = r % 3;
        r /= 3;
    }
    for(int p = i + 1; p <= j; p++) L[p] = 0;

    cout << dfs(j, true, true, true) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(dp, -1, sizeof dp);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}