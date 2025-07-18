#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int l, r, w;
    friend bool operator < (const info &a, const info &b) {
        return a.l < b.l;
    }
};
void solve() {
    int n, k;
    cin >> n >> k;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].l >> a[i].r >> a[i].w;
    }
    sort(a.begin() + 1, a.end());
    int ans = k;
    for(int i = 1; i <= n; i++) {
        auto [l, r, w] = a[i];
        if(r < ans) continue;
        if(l > ans) break;
        ans = max(ans, w);
    }
    cout << ans << "\n";
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
