#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int W, H;
    cin >> W >> H;
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    int w, h;
    cin >> w >> h;
    int ans = inf;
    if(y2 - y1 + h <= H) {
        ans = min(ans, max(0, h - y1));
        ans = min(ans, max(0, h - (H - y2)));
    }
    if(x2 - x1 + w <= W) {
        ans = min(ans, max(0, w - x1));
        ans = min(ans, max(0, w - (W - x2)));
    }
    if(ans == inf) {
        cout << -1 << "\n";
        return;
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
