#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int ans = 0, mx = 0;
    for(int i = 1; i <= 5; i++) {
        int x;
        cin >> x;
        int d = 0;
        while(x % 10 != 0) x++, d++;
        ans += x;
        mx = max(mx, d);
    }
    cout << ans - mx << "\n";
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
