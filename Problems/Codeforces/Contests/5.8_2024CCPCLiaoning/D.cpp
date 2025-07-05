#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/gym/105481
struct info {
    ll x, y;
};
db cal(info a, info b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
void solve() {
    int n;
    cin >> n;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y;
    }
    vector<vector<db>> len(n + 1, vector<db>(n + 1));
    for(int i = 1; i <= n; i++) {
        db cur = 0;
        for(int j = i + 1; j <= n; j++) {
            cur = max(cur, cal(a[i], a[j]));
            len[i][j] = cur;
        }
    }
    vector<db> dp(n + 1);
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < i; j++) {
            dp[i] = max(dp[i], dp[j] + len[j + 1][i]);
        }
    }
    cout << fixed << setprecision(9) << dp[n] << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
