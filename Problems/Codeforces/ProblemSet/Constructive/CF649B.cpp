#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int n, m, k;
PII cal(int x) {
    return {(x + m * k - 1) / (m * k), (x - ((x + m * k - 1) / (m * k) - 1) * m * k + k - 1) / k};
}
void solve() {
    cin >> n >> m >> k;
    int u, v;
    cin >> u >> v;
    PII a = cal(u), b = cal(v);
    int ans = 0;
    if(a.first == b.first) {
        int x = max(a.second, b.second), y = min(a.second, b.second);
        ans += min(5 * (x - y), 10 + x - y);
    } else {
        ans += min(5 * (a.second - 1), 10 + a.second - 1);
        ans += min(5 * (b.second - 1), 10 + b.second - 1);
        ans += 15 * min((b.first - a.first + n) % n, (a.first - b.first + n) % n);
    }
    cout << ans << "\n";
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
