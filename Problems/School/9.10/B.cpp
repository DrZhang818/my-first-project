#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m;
    cin >> n >> m;
    unordered_map<string,int> mp;
    vector<string> ss(n + 1), a(m + 1);
    for(int i = 1; i <= n; i++) {
        cin >> ss[i];
    }
    for(int i = 1; i <= m; i++) {
        cin >> a[i];
    }
    int t0;
    cin >> t0;
    for(int i = 1; i <= m; i++) {
        int x;
        cin >> x;
        mp[a[i]] = x;
    }
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        if(mp.contains(ss[i])) {
            ans += mp[ss[i]];
        } else {
            ans += t0;
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
