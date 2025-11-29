#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    string s;
    cin >> s;
    int m;
    cin >> m;
    string L, R;
    cin >> L >> R;
    int n = s.size();
    s = "#" + s;
    vector<array<int,10>> nxt(n + 2);
    fill(nxt[n + 1].begin(), nxt[n + 1].end(), inf);
    for(int i = n; i >= 1; i--) {
        for(int j = 0; j <= 9; j++) {
            nxt[i][j] = nxt[i + 1][j];
        }
        nxt[i][s[i] - '0'] = i;
    }
    vector<int> dp(10);
    for(int i = 0; i < m; i++) {
        vector<int> ndp(10);
        for(int j = 0; j <= 9; j++) {
            for(int k = L[i] - '0'; k <= R[i] - '0'; k++) {
                if(dp[j] == inf) {
                    ndp[k] = inf;
                } else {
                    ndp[k] = max(ndp[k], nxt[dp[j] + 1][k]);
                }
            }
        }
        swap(dp, ndp);
    }
    int mx = *max_element(dp.begin(), dp.end());
    if(mx == inf) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
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
