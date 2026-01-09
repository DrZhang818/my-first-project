#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m, k;
    cin >> n >> m >> k;
    int ans = 1;
    int mx = 0;
    for(int i = 0; i <= k - 1; i++) {
        int rem = m - 2 * i + 1;
        if(rem < 0) break;
        int l = -1, r = n - k + 1;
        while(l + 1 < r) {
            int mid = l + r >> 1;
            if(max(0, mid - i) + mid <= rem) {
                l = mid;
            } else {
                r = mid;
            }
        }
        mx = max(mx, i + l);
    }
    for(int i = 0; i <= n - k; i++) {
        int rem = m - 2 * i + 1;
        if(rem < 0) break;
        int l = -1, r = k;
        while(l + 1 < r) {
            int mid = l + r >> 1;
            if(max(0, mid - i) + mid <= rem) {
                l = mid;
            } else {
                r = mid;
            }
        }
        mx = max(mx, i + l);
    }
    ans += mx;
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
