#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());

    int mx = a[n - 1];
    n -= 1;
    const int N = 1 << n;

    auto ck = [&](i64 x) {
        vector<pair<int,i64>> dp(N);

        for(int s = 0; s < N; s++) {
            for(int i = 0; i < n; i++) {
                if(s >> i & 1) continue;
                int ns = s | 1 << i;

                auto [cnt, sum] = dp[s];
                int ncnt = cnt;
                i64 nsum = sum + a[i];
                if(nsum >= x) {
                    ncnt++;
                    nsum = 0;
                }

                dp[ns] = max(dp[ns], pair{ncnt, nsum});
            }
        }

        return dp[N - 1].first >= k;
    };

    i64 l = 0, r = 2E10;

    while(l + 1 < r) {
        i64 mid = l + r >> 1;
        if(ck(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }

    cout << l + mx << "\n";
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