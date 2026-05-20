#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> C(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> C[i];
    }
    i64 ans = 0;
    for(int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        ans += min(b, C[a]);
        C[a] -= min(b, C[a]);
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
