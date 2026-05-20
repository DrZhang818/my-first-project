#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int sum = 0;
    int mx = -inf;
    for(int i = 0; i < 7; i++) {
        int x;
        cin >> x;
        sum -= x;
        mx = max(mx, x);
    }
    cout << sum + 2 * mx << "\n";
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
