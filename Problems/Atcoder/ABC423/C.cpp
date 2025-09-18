#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int l = 1, r = n;
    while(l <= n && a[l] == 1) {
        l++;
    }
    while(r >= 1 && a[r] == 1) {
        r--;
    }
    l = min(l, x + 1);
    r = max(r, x);
    int ans = r - l + 1;
    for(int i = l; i <= r; i++) {
        ans += a[i] == 1;
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
