#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;
constexpr int N = 1E6;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    const int N = 1 << (__lg(n) + 1);

    vector<vector<int>> dp(n + 1, vector<int>(N + 1));
    vector<int> mex(n + 1);
    dp[0][0] = 1;

    for(int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];

        vector<int> nmex(n + 1);
        vector<bool> vis(n + 2);
        for(int j = i, x = 0; j >= 1; j--) {
            vis[a[j]] = true;
            while(vis[x]) x++;
            nmex[j] = x;
        }

        for(int j = i; j >= 1; j--) {
            if(j == i || nmex[j] > nmex[j + 1] && nmex[j] > mex[j]) {
                for(int x = 0; x < N; x++) {
                    dp[i][x ^ nmex[j]] |= dp[j - 1][x];
                }
            }
        }
        mex = move(nmex);
    }

    for(int i = N - 1; i >= 0; i--) {
        if(dp[n][i]) {
            cout << i << "\n";
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}