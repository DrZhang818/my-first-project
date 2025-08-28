#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

vector<ll> mi;
void solve() {
    int sz = mi.size() - 1;
    int n;
    cin >> n;
    ll ans = 0;
    for(int s = sz; s >= 0; s--) {
        while(n >= mi[s]) {
            ans += mi[s] * 3 + s * (mi[s] / 3);
            n -= mi[s];
        }
    }
    if(n) {
        ans += 3;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    mi.push_back(1);
    while(mi.back() <= inf) {
        mi.push_back(mi.back() * 3);
    }
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
