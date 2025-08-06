#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    ll cnt, w;
    friend bool operator < (const info &a, const info &b) {
        return a.w < b.w;
    }
};
void solve() {
    int n, m;
    cin >> n >> m;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].w >> a[i].cnt;
    }
    sort(a.begin() + 1, a.end());
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        ans += a[i].w * min((ll)m, a[i].cnt);
        m -= min((ll)m, a[i].cnt);
    }
    cout << ans << "\n";
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
