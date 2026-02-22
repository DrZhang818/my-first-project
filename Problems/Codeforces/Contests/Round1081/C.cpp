#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, h, k;
    cin >> n >> h >> k;
    vector<int> a(n + 1);
    i64 sum = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }

    int t = h / sum;
    h %= sum;

    i64 ans = 1LL * t * (n + k);
    if(h == 0) {
        ans -= k;
        cout << ans << "\n";
        return;
    }

    vector<int> mn(n + 1, inf), mx(n + 2, -inf);
    vector<i64> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        mn[i] = min(a[i], mn[i - 1]);
        pre[i] = pre[i - 1] + a[i];
    }
    for(int i = n; i >= 1; i--) {
        mx[i] = max(mx[i + 1], a[i]);
    }

    for(int i = 1; i <= n; i++) {
        if(pre[i] + max(mx[i + 1] - mn[i], 0) >= h) {
            ans += i;
            break;
        }
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
