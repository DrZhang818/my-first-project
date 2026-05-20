#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr i64 inf = 1E18;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<i64> a(n + 1), b(m + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= m; i++) {
        cin >> b[i];
    }
    sort(a.begin() + 1, a.end());
    sort(b.begin() + 1, b.end());
    i64 ans = inf;

    for(int i = 1, j = 1; i <= n; i++) {
        while(j <= m && b[j] < a[i]) {
            j++;
        }
        if(j <= m) {
            ans = min(ans, abs(a[i] - b[j]));
        }
        if(j - 1 >= 1) {
            ans = min(ans, abs(a[i] - b[j - 1]));
        }
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
