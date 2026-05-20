#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n, k, p, q;
    cin >> n >> k >> p >> q;
    if(p > q) swap(p, q);

    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<array<i64, 2>> pre(n + 1);
    vector<i64> sum(n + 1);
    for(int i = 1; i <= n; i++) {
        pre[i][0] = pre[i - 1][0] + (a[i] % p);
        pre[i][1] = pre[i - 1][1] + (a[i] % q % p);
        sum[i] = sum[i - 1] + min(a[i] % p, a[i] % q % p);
    }

    i64 ans = 1E18;
    for(int i = 1; i <= n - k + 1; i++) {
        ans = min(ans, min(pre[i + k - 1][0] - pre[i - 1][0], pre[i + k - 1][1] - pre[i - 1][1]) + sum[i - 1] + sum[n] - sum[i + k - 1]);
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}