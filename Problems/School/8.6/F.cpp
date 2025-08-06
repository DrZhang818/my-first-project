#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m, c;
    cin >> n >> m >> c;
    vector<int> a(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> a[i];
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        ll cur = 0;
        for(int j = 1; j <= m; j++) {
            int x;
            cin >> x;
            cur += a[j] * x;
        }
        if(cur + c > 0) {
            ans++;
        }
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
