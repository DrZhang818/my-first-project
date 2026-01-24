#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, w;
    cin >> n >> w;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<ll> cost(2 * w);
    for(int i = 1; i <= n; i++) {
        int j = i % (2 * w);
        if(j < w) {
            cost[0] += a[i];
            cost[w - j] -= a[i];
            cost[2 * w - j] += a[i];
        } else {
            cost[2 * w - j] += a[i];
            cost[3 * w - j] -= a[i];
        }
    }
    for(int i = 1; i < 2 * w; i++) {
        cost[i] += cost[i - 1];
    }
    ll ans = *min_element(cost.begin(), cost.end());
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
