#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int l, r;
    cin >> l >> r;
    vector<int> a(r + 1);
    auto dfs = [&](this auto &&self, int l, int r) -> void {
        if(l > r) return;
        int sz = r - l + 1;
        int high_bit = __lg(sz);
        int s = (1 << high_bit) - 1;
        for(int i = l; i <= l + s; i++) {
            int j = i - l;
            a[i] |= s ^ j;
        }
        int len = r - l - s;
        for(int i = l + s; i > l + s - len; i--) {
            a[i] |= (s + 1);
        }
        self(l + s + 1, r);
    };
    dfs(0, r);
    ll ans = 0;
    for(int i = 0; i <= r; i++) {
        ans += a[i] | i;
    }
    cout << ans << "\n";
    for(int i = 0; i <= r; i++) {
        cout << a[i] << " \n"[i == r];
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
