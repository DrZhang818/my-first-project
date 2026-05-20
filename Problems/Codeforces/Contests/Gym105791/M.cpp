#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> a(n + 1, vector<int>(n + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }

    if(n == 1) {
        cout << 0 << "\n";
        return;
    }

    vector<int> p(n + 1);
    iota(p.begin(), p.end(), 0);

    i64 ans = 1E18;

    do {
        i64 cur = 0;
        for(int i = 2; i <= n; i++) {
            cur += a[p[i - 1]][p[i]];
        }
        cur += a[p[n]][p[1]];
        ans = min(ans, cur);
    } while (next_permutation(p.begin() + 2, p.end()));

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}