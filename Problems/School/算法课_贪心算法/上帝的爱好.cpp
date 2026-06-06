#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;
constexpr int M = 1E3;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> las(M + 1, n + 1);
    vector<int> nxt(n + 1);

    for(int i = n; i >= 1; i--) {
        nxt[i] = las[a[i]];
        las[a[i]] = i;
    }

    vector<int> f(n + 2, n + 1);
    for(int i = n - 1; i >= 1; i--) {
        f[i] = min(nxt[i], f[i + 1]);
    }

    vector<int> dp(n + 1);
    for(int i = 1; i <= n; i++) {
        dp[i] = max(dp[i], dp[i - 1]);
        int j = nxt[i];
        if(j == n + 1) continue;
        int k = f[i + 1];
        if(k == nxt[j]) {
            k = f[j + 1];
        }
        if(k == n + 1) continue;
        int r = max(j, k);
        dp[r] = max(dp[r], dp[i - 1] + 1);
    }

    cout << dp[n] << "\n";
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