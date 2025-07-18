#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct line {
    int x, y;
};
void solve() {
    int x0, y0, x1, y1;
    cin >> x0 >> y0 >> x1 >> y1;
    line r;
    r.x = x1 - x0, r.y = y1 - y0;
    line c = {-r.y, r.x};
    int x2 = x1 + c.x, y2 = y1 + c.y;
    int x3 = x0 + c.x, y3 = y0 + c.y;
    cout << x2 << " " << y2 << " " << x3 << " " << y3 << "\n";
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
