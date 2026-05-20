#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> d(n + 2);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        d[i]++;
        if(x > i) {
            d[x]--;
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        d[i] += d[i - 1];
        ans = max(ans, d[i]);
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
