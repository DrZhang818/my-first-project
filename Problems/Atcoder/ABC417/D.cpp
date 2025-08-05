#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int N = 1000;
struct info {
    int p, x, y;
};
void solve() {
    int n;
    cin >> n;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].p >> a[i].x >> a[i].y;
    }
    vector dp(n + 1, vector<int>(N + 1));
    for(int i = 0; i <= a[n].p; i++) {
        dp[n][i] = i + a[n].x;
    }
    for(int i = a[n].p + 1; i <= N; i++) {
        dp[n][i] = max(0, i - a[n].y);
    }
    for(int i = n - 1; i >= 1; i--) {
        auto [p, x, y] = a[i];
        for(int j = 0; j <= a[i].p; j++) {
            dp[i][j] = dp[i + 1][j + x];
        }
        for(int j = a[i].p + 1; j <= N; j++) {
            dp[i][j] = dp[i + 1][max(0, j - y)];
        }
    } 
    vector<ll> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + a[i].y;
    }
    auto find = [&](int x) -> int {
        int l = -1, r = n + 1;
        while(l + 1 < r) {
            int mid = l + r >> 1;
            if(x - pre[mid] <= 500) {
                r = mid;
            } else {
                l = mid;
            }
        }
        return r;
    };
    int q;
    cin >> q;
    while(q--) {
        int x;
        cin >> x;
        int pos = find(x);
        if(pos >= n) {
            cout << x - pre[n] << "\n";
        } else {
            cout << dp[pos + 1][x - pre[pos]] << "\n";
        }
    }
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
