#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000007;

void solve() {
    vector<int> a(4);
    for(int i = 1; i <= 3; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());
    int ans = 0;
    for(int i = 1; i < 3; i++) {
        ans += a[i + 1] - a[i];
    }
    cout << ans << "\n";
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
