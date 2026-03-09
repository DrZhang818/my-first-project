#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int dp0 = 0, dp1 = 1;

    for(int i = 1; i <= n; i++) {
        if(a[i] == 1) {
            tie(dp0, dp1) = tuple(inf, min(dp0, dp1) + 1);
        } else if(i > 1) {
            if(gcd(a[i], a[i - 1]) == 1) {
                tie(dp0, dp1) = tuple(dp1, min(dp0, dp1) + 1);
            } else {
                tie(dp0, dp1) = tuple(min(dp0, dp1), min(dp0, dp1) + 1);
            }
        }
    }

    cout << min(dp0, dp1) << "\n";
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
