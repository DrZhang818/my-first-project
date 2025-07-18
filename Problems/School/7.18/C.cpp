#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, k;
    cin >> n >> k;
    ll ans1 = 0, ans2 = 0;
    ll cnt = n / k;
    ans1 = cnt * cnt * cnt;
    if(k & 1) {
        cout << ans1 << "\n";
        return;
    }
    ll c2 = n / (k / 2) - cnt;
    ans2 = c2 * c2 * c2;
    cout << ans1 + ans2 << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
