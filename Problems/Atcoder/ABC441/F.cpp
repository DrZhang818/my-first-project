#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<int> c(n + 1), w(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> c[i] >> w[i];
    }
    vector dp(n + 1, vector<ll>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= m; j++) {
            dp[i][j] = dp[i - 1][j];
            if(j >= c[i] && dp[i - 1][j - c[i]] + w[i] > dp[i][j]) {
                dp[i][j] = dp[i - 1][j - c[i]] + w[i];
            }
        }
    }
    vector<bool> tag0(n + 1), tag1(n + 1);

    vector vis(n + 1, vector<bool>(m + 1));

    queue<PII> q;
    q.emplace(n, m);
    while(!q.empty()) {
        auto [i, j] = q.front(); q.pop();
        if(i == 0) continue;

        if(dp[i - 1][j] == dp[i][j]) {
            tag0[i] = true;
            if(!vis[i - 1][j]) {
                q.emplace(i - 1, j);
                vis[i - 1][j] = true;
            }
        }
        if(j >= c[i] && dp[i - 1][j - c[i]] + w[i] == dp[i][j]) {
            tag1[i] = true;
            if(!vis[i - 1][j - c[i]]) {
                q.emplace(i - 1, j - c[i]);
                vis[i - 1][j - c[i]] = true;
            }
        }   
    }

    for(int i = 1; i <= n; i++) {
        if(tag0[i] && tag1[i]) {
            cout << 'B';
        } else if(tag0[i]) {
            cout << 'C';
        } else {
            cout << 'A';
        }
    }
    cout << "\n";
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
