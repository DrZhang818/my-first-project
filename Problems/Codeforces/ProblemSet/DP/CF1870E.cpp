#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;

    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    const int N = 1 << (__lg(n) + 1);

    vector<vector<int>> dp(n + 1, vector<int>(N + 1));
    dp[0][0] = 1;

    vector<int> mex(n + 1);

    for(int i = 1; i <= n; i++) {
        vector<int> nmex(n + 1);

        vector<int> cnt(n + 1);
        for(int j = i, x = 0; j >= 1; j--) {
            cnt[a[j]]++;
            while(cnt[x]) {
                x++;
            }
            nmex[j] = x;
        }

        dp[i] = dp[i - 1];

        for(int j = i; j >= 1; j--) {
            bool ok = (j == i || nmex[j] > nmex[j + 1] && nmex[j] > mex[j]);
            if(ok) {
                for(int v = 0; v < N; v++) {
                    dp[i][v ^ nmex[j]] |= dp[j - 1][v];
                }
            }
        }

        mex = move(nmex);
    }

    for(int v = N - 1; v >= 0; v--) {
        if(dp[n][v]) {
            cout << v << "\n";
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
