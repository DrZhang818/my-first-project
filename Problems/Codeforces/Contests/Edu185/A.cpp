#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    if(n == 1) {
        cout << 1 << "\n";
    } else if(n == 2) {
        cout << 9 << "\n";
    } else if(n == 3) {
        cout << 29 << "\n";
    } else if(n == 4) {
        cout << 56 << "\n";
    } else {
        int ans = 5 * n * n - 5 * n - 5;
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
