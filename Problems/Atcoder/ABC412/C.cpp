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
    int lo = a[1], hi = a[n];
    if(hi <= 2 * lo) {
        cout << 2 << "\n";
        return;
    }
    sort(a.begin() + 2, a.end());
    int ans = 2, cur = a[1];
    for(int i = 2; i <= n; i++) {
        if(a[i] > 2 * cur) {
            if(a[i] > 2 * a[i - 1]) {
                cout << -1 << "\n";
                return;
            }
            cur = a[i - 1];
            ans++;
        }
        if(a[i] == hi) {
            break;
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
