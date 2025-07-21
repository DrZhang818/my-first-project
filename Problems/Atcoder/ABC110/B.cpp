
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m, X, Y;
    cin >> n >> m >> X >> Y;
    int mx = X, mn = Y;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        mx = max(mx, x);
    }
    for(int j = 1; j <= m; j++) {
        int y;
        cin >> y;
        mn = min(mn, y);
    }
    if(mx < mn) {
        cout << "No War\n";
    } else {
        cout << "War\n";
    }
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
