#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000007;

void solve() {
    int n;
    cin >> n;
    int lx, rx, ly, ry;
    lx = ly = inf;
    rx = ry = -inf;
    for(int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        lx = min(lx, x);
        rx = max(rx, x);
        ly = min(ly, y);
        ry = max(ry, y);
    }
    ll d1 = (rx - lx + 1) / 2;
    ll d2 = (ry - ly + 1) / 2;
    cout << max(d1, d2) << "\n";
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
