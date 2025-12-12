#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), b(m + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= m; i++) {
        cin >> b[i];
    }
    sort(a.begin() + 1, a.end());
    sort(b.begin() + 1, b.end());
    int al = 1, ar = n, bl = 1, br = m;
    ll ans = 0;
    while(al <= ar) {
        if(abs(b[br] - a[al]) > abs(b[bl] - a[ar])) {
            ans += abs(b[br] - a[al]);
            br--;
            al++;
        } else {
            ans += abs(b[bl] - a[ar]);
            bl++;
            ar--;
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
