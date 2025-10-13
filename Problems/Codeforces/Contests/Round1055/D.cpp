#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    auto cal = [&](int x) -> int {
        int cnt = 0;
        while(x > 1) {
            x /= 2;
            cnt++;
            if(x >= 2) {
                x += 1;
            }
        }
        return cnt;
    };
    vector<ll> pre(n + 1);
    vector<int> c(n + 1);
    for(int i = 1; i <= n; i++) {
        int x = cal(a[i]), y = cal(a[i] + 1);
        pre[i] = pre[i - 1] + x;
        c[i] = c[i - 1] + (x != y);
    }
    while(q--) {
        int l, r;
        cin >> l >> r;
        ll ans = pre[r] - pre[l - 1];
        int cnt = c[r] - c[l - 1];
        ans += cnt / 2;
        cout << ans << "\n";
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
