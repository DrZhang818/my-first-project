#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000007;

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    if(n == 1) {
        cout << 0 << "\n";
        return;
    }
    vector<int> r(n + 2), d(n + 2);
    for(int i = 1; i <= n; i++) {
        if(i == 1) {
            r[i] = a[i + 1] - a[i];
        } else if(i == n) {
            r[i] = a[i] - a[i - 1];
        } else {
            r[i] = min(a[i] - a[i - 1], a[i + 1] - a[i]);
        }
        if(i > 1) {
            d[i] = a[i] - a[i - 1];
        }
    }
    ll mn = 0, mx = r[1];
    int ans = 0;
    ll sumd = 0;
    int j = 1;
    for(int i = 2; i <= n; i++) {
        if(i + j & 1) {
            sumd += d[i];
            mn = max(mn, sumd - r[i]);            
        } else {
            sumd -= d[i];
            mx = min(mx, sumd + r[i]);
        }
        if(r[i] + r[i - 1] <= d[i] || mn >= mx || r[j] <= mn) {
            mn = 0;
            mx = r[i];
            sumd = 0;
            j = i;
            continue;
        }
        ans++;
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
