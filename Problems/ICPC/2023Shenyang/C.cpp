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
    int ans;
    if(x == 0 && y == 0) {
        ans = 4;
    } else if(x == 0 && y == 1) {
        ans = 4;
    } else if(x == 0 && y == 2) {
        ans = 6;
    } else if(x == 1 && y == 0) {
        ans = 3;
    } else if(x == 1 && y == 1) {
        ans = 3;
    } else if(x == 1 && y == 2) {
        ans = 4;
    } else if(x == 2 && y == 0) {
        ans = 2;
    } else if(x == 2 && y == 1) {
        ans = 2;
    } else if(x == 2 && y == 2) {
        ans = 2;
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
