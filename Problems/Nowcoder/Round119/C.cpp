#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    int l, r;
    cin >> l >> r;
    int ans = 0;
    auto cal = [&](int x) -> int {
        int res = 0;
        while(x) {
            res += x % 10;
            x /= 10;
        }
        return res;
    };
    for(int i = l; i <= 200 && i <= r; i++) {
        if(i == cal(i * i)) {
            ans++;
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
