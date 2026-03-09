#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> a(2 * n + 1);
    vector<int> tot(n + 1);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        tot[x]++;
        a[i] = a[i + n] = x;
    }

    vector<int> cnt(n + 1);

    auto getAns = [&](int col) -> int {
        return min(tot[col], (cnt[col] + k - 1) / k * k);
    };

    int cur = 0, ans = 0, p = 1;
    
    auto add = [&](int col, int d) {
        ans -= getAns(col);
        cur -= (cnt[col] + k - 1) / k;
        cnt[col] += d;
        ans += getAns(col);
        cur += (cnt[col] + k - 1) / k;
    };

    for(int l = 1, r = n; r < 2 * n; l++, r++) {
        while(p <= r && cur < m) {
            add(a[p], 1);
            p++;
        }
        cout << ans << "\n";
        add(a[l], -1);
    }
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
