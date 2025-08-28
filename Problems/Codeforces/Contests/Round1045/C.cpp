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
    ll ans = 0;
    for(int i = 1; i <= n; i += 2) {
        int L = inf + 1, R = inf + 1;
        if(i != 1) L = a[i - 1];
        if(i != n) R = a[i + 1];
        int mn = min(L, R);
        ans += max(0, a[i] - mn);
        a[i] = min(a[i], mn);
    }
    for(int i = 2; i < n; i += 2) {
        int L = a[i - 1], R = a[i + 1];
        int sum = L + R;
        if(sum > a[i]) {
            ans += sum - a[i];
            a[i + 1] -= sum - a[i];
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
