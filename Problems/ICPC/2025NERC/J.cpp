#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, k;
    cin >> n >> k;
    vector<int> cnt(101);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }
    vector power(101, vector<db>(k + 1, 1));
    for(int i = 0; i <= 100; i++) {
        for(int j = 1; j <= k; j++) {
            power[i][j] = power[i][j - 1] * db(i) / 100;
        }
    }
    vector<vector<db>> p(k + 1, vector<db>(k + 1));
    for(int a = 0; a <= k; a++) {
        for(int b = 0; b <= k - a; b++) {
            for(int i = 0; i <= 100; i++) {
                if(cnt[i] == 0) continue;
                p[a][b] += power[i][a] * power[100 - i][b] * cnt[i];
            }
        }
    }
    auto t = p;
    for(int a = 0; a < k; a++) {
        for(int b = 0; b <= k - 1 - a; b++) {
            if(t[a][b] == 0) {
                continue;
            }
            p[a][b] = t[a + 1][b] / t[a][b];
        }
    }
    vector dp(k + 1, vector<db>(k + 1));
    for(int a = 0; a <= k; a++) {
        dp[a][k - a] = 1;
    }
    for(int s = k - 1; s >= 0; s--) {
        for(int a = 0; a <= s; a++) {
            int b = s - a;
            dp[a][b] = max(2 * p[a][b] * dp[a + 1][b], p[a][b] * (dp[a + 1][b] - dp[a][b + 1]) + dp[a][b + 1]);
        }
    }
    cout << fixed << setprecision(12) << 1000 * (dp[0][0] - 1) << "\n";
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
