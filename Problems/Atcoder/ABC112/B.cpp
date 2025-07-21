#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, t;
    cin >> n >> t;
    vector<PII> a(n + 1);
    for(int i = 1; i <= n; i++) {
        int c, tt;
        cin >> c >> tt;
        a[i] = {tt, c};
    }
    sort(a.begin() + 1, a.end());
    int ans = inf;
    for(int i = 1; i <= n; i++) {
        auto [tt, c] = a[i];
        if(tt <= t) {
            ans = min(ans, c);
        } else {
            break;
        }
    }
    if(ans == inf) {
        cout << "TLE\n";
        return;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
