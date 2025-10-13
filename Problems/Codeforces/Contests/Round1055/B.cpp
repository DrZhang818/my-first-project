#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, x0, y0, x1, y1;
    cin >> n >> x0 >> y0 >> x1 >> y1;
    if(x1 < x0) {
        x1 = n - x1;
        x0 = n - x0;
    }
    if(y1 < y0) {
        y1 = n - y1;
        y0 = n - y0;
    }
    if(x1 == x0) {
        cout << y1 << "\n";
    } else if(y1 == y0) {
        cout << x1 << "\n";
    } else {
        cout << max(x1, y1) << "\n";
    }
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
