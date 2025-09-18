#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    ll w, c;
};

void solve() {
    int n;
    cin >> n;
    vector<info> a(n + 1);
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        ll v;
        cin >> a[i].w >> v >> a[i].c;
        ans += v;
    }
    sort(a.begin() + 1, a.end(), 
        [&](auto x, auto y) {
            return x.c * y.w < y.c * x.w;
        });
    ll W = 0;
    for(int i = 1; i <= n; i++) {
        ans -= a[i].c * W;
        W += a[i].w;
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
