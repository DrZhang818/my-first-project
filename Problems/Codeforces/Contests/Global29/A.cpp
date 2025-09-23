#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int x, y;
    cin >> x >> y;
    if(y == 1) {
        cout << -1 << "\n";
        return;
    }
    if(y > x) {
        cout << 2 << "\n";
        return;
    }
    if(x >= y + 2) {
        cout << 3 << "\n";
        return;
    }
    cout << -1 << "\n";
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
