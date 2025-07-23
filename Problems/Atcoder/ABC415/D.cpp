#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    ll x, y;
    friend bool operator < (const info &a, const info &b) {
        return a.x - a.y < b.x - b.y;
    }
};
void solve() {
    ll n;
    int m;
    cin >> n >> m;
    vector<info> a(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> a[i].x >> a[i].y;
    }
    sort(a.begin() + 1, a.end());
    ll ans = 0, cur = n;
    for(int i = 1; i <= m; i++) {
        if(cur < a[i].x) continue;
        ll t = (cur - a[i].x) / (a[i].x - a[i].y) + 1;
        ans += t;
        cur = cur + (a[i].y - a[i].x) * t;
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
