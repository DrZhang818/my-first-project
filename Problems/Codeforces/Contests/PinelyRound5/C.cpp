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
    ll ans = 0;
    sort(a.begin() + 1, a.end());
    int l = 1, r = n;
    int S = 0;
    vector<int> val;
    while(l <= r) {
        if(S + a[r] >= x) {
            ans += a[r];
            S = (S + a[r]) % x;
            val.push_back(a[r]);
            r--;
        } else {
            S += a[l];
            val.push_back(a[l]);
            l++;
        }
    }
    cout << ans << "\n";
    for(int i = 0; i < n; i++) {
        cout << val[i] << " \n"[i == n - 1];
    }
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
