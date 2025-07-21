#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int ans = -inf;
    for(int x = 1; x <= 100; x++) {
        vector<int> b(n + 1);
        for(int i = 1; i <= n; i++) {
            b[i] = a[i] >= x ? 1 : -1;
        }
        vector<int> pre(n + 1), premn(n + 1), sufmx(n + 1);
        for(int i = 1; i <= n; i++) {
            pre[i] = pre[i - 1] + b[i];
        }
        sufmx[n] = pre[n];
        for(int i = 1; i <= n; i++) {
            premn[i] = min(premn[i - 1], pre[i]);
        }
        for(int i = n - 1; i >= 1; i--) {
            sufmx[i] = max(sufmx[i + 1], pre[i]);
        }
        for(int i = 1; i <= n; i++) {
            if(sufmx[i] >= premn[i - 1]) {
                ans = max(ans, x - a[i]);
            }
        }
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
