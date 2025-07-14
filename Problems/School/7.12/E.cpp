#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000007;

struct info {
    int l, r;
    friend bool operator < (const info &a, const info &b) {
        return a.l < b.l;
    }
};
void solve() {
    int n, m;
    cin >> n >> m;
    vector<info> a(m + 1);
    for(int i = 1; i <= m; i++) {
        int l, r;
        cin >> l >> r;
        a[i].l = l, a[i].r = r - 1;
    }
    sort(a.begin() + 1, a.end());
    int R = 0, ans = 0;
    for(int i = 1; i <= m; i++) {
        auto [l, r] = a[i];
        if(l <= R) {
            R = min(R, r);
        } else {
            ans++;
            R = r;
        }
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
