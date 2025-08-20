#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int m;
int mod(int x) {
    return (x % m + m) % m;
}
void solve() {
    int n, L;
    cin >> n >> m >> L;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector cost(L + 1,  vector<int>(m));
    for(int i = 1; i <= L; i++) {
        for(int j = i; j <= n; j += L) {
            for(int s = 0; s < m; s++) {
                cost[i][s] += mod(s - a[j]);
            }
        }
    }
    vector<int> dp(m, inf);
    dp[0] = 0;
    for(int i = 1; i <= L; i++) {
        vector<int> ndp(m, inf);
        for(int x = 0; x < m; x++) {
            for(int y = 0; y < m; y++) {
                ndp[mod(x + y)] = min(ndp[mod(x + y)], dp[x] + cost[i][y]);
            }
        }
        swap(dp, ndp);
    }
    cout << dp[0] << "\n";
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
