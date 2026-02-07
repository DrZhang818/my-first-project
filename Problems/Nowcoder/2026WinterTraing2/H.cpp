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
    ll ans = 0, dp = 0, f = 0;
    map<int,int> las;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        f += i - las[x];
        dp += f;
        ans += dp;

        las[x] = i;
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
