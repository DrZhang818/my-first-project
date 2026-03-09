#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;
constexpr int N = 1000000;

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<string> ss(n);
    vector<array<int,2>> cnt(m);
    for(int i = 0; i < n; i++) {
        cin >> ss[i];
        auto& s = ss[i];
        for(int j = 0; j < m; j++) {
            cnt[j][0] += (s[j] == '0');
            cnt[j][1] += (s[j] == '1');
        }
    }

    for(int i = 0; i < n; i++) {
        int dp0 = 0, dp1 = inf, dp2 = inf;
        for(int j = 0; j < m; j++) {
            int c = ss[i][j] - '0';
            tie(dp0, dp1, dp2) = tuple(dp0 + cnt[j][c ^ 1], min(dp0, dp1) + cnt[j][c] - 1, min(dp1, dp2) + cnt[j][c ^ 1]);
        }
        cout << min({dp0, dp1, dp2}) << "\n";
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
