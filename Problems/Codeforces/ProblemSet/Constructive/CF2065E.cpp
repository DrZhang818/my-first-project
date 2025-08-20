#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    if(max(n, m) - min(n, m) > k || n < k && m < k) {
        cout << -1 << "\n";
        return;
    }
    int tag = n > m;
    int c0 = n, c1 = m;
    for(int i = 1; i <= n + m; i++) {
        if(c0 == 0) tag = 0;
        if(c1 == 0) tag = 1;
        if(tag) {
            cout << 0;
            c0--;
        } else {
            cout << 1;
            c1--;
        }
        if(i % k == 0) {
            tag ^= 1;
        }
    }
    cout << "\n";
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
