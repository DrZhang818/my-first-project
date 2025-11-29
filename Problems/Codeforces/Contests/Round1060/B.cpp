#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int cur = 0;
    for(int i = 1; i <= n; i++) {
        cur = max(cur, a[i]);
        if(i % 2 == 0) {
            a[i] = max(a[i], cur);
        }
    }
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        if(i % 2 == 1) {
            if(i == 1) {
                ans += max(0, a[i] - a[i + 1] + 1);
            } else if(i == n) {
                ans += max(0, a[i] - a[i - 1] + 1);
            } else {
                ans += max({0, a[i] - a[i - 1] + 1, a[i] - a[i + 1] + 1});
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
