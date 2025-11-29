#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int V = 100000;
const int MOD = 1000000007;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {
    int N, X;
    cin >> N >> X;
    vector<int> S(N + 1);
    for(int i = 1; i <= N; i++) {
        cin >> S[i];
    }
    sort(S.begin() + 1, S.end(), greater<int>());
    vector<array<int,V + 1>> dp(N + 1);
    for(int i = 1; i <= N; i++) {
        fill(dp[i].begin(), dp[i].end(), -1);
    }
    auto dfs = [&](auto &&self, int i, int X) -> int {
        if(i == N) {
            return X % S[i];
        }
        int &res = dp[i][X];
        if(res != -1) {
            return res;
        }
        res = 0;
        add(res, self(self, i + 1, X % S[i]));
        add(res, 1LL * (N - i) * self(self, i + 1, X) % MOD);
        return res;
    };
    int ans = dfs(dfs, 1, X);
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
