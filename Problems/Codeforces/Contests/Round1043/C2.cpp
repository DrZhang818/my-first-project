#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

vector<ll> mi, cost;
void solve() {
    int sz = mi.size() - 1;
    int n, k;
    cin >> n >> k;
    ll ans = 0;
    vector<ll> cnt(sz + 1);
    ll tot = 0;
    for(int s = sz; s >= 0; s--) {
        while(n >= mi[s]) {
            ans += cost[s];
            n -= mi[s];
            cnt[s]++;
            tot++;
        }
    }
    assert(n == 0);
    if(tot > k) {
        cout << -1 << "\n";
        return;
    }
    ll rem = k - tot;
    for(int s = sz; s > 0; s--) {
        ll x = min(cnt[s], rem / 2);
        cnt[s - 1] += 3 * x;
        cnt[s] -= x;
        rem -= 2 * x;
        ans -= x * cost[s];
        ans += 3 * x * cost[s - 1];
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    mi.push_back(1);
    cost.push_back(3);
    int x = 0;
    while(mi.back() <= inf) {
        x++;
        mi.push_back(mi.back() * 3);
        cost.push_back(mi.back() * 3 + x * (mi.back() / 3));
    }
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
