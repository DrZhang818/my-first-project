#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

constexpr int MOD = 1000000007;

void solve() {  
    int n;
    cin >> n;

    vector<int> lo(n + 1, 1), hi(n + 1);

    int mx = -1;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if(x > mx) {
            mx = x;
            lo[i] = hi[i] = x;
        } else {
            hi[i] = mx;
        }
    }

    mx = -1;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = n; i >= 1; i--) {
        if(a[i] > mx) {
            mx = a[i];
            hi[i] = min(hi[i], a[i]);
            lo[i] = max(lo[i], a[i]);
        } else {
            hi[i] = min(hi[i], a[i]);
        }
    }

    int ans = 1;
    for(int i = 1; i <= n; i++) {
        if(lo[i] > hi[i]) {
            ans = 0;
        } else {
            ans = 1LL * ans * (hi[i] - lo[i] + 1) % MOD;
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
