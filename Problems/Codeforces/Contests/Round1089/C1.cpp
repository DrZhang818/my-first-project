#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        if(i == 1) {
            if(gcd(a[i], a[i + 1]) != a[i]) {
                ans++;
            }
        } else if(i == n) {
            if(gcd(a[i - 1], a[i]) != a[i]) {
                ans++;
            }
        } else {
            int l = gcd(a[i], a[i - 1]);
            int r = gcd(a[i], a[i + 1]);
            if(lcm(l, r) != a[i]) {
                ans++;
            }
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
