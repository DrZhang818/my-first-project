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
    vector<int> a(2 * n + 1);
    for(int i = 1; i <= 2 * n; i++) {
        cin >> a[i];
    }
    vector<ll> dp0(2 * n + 1), dp1(2 * n + 1);
    for(int i = 1; i <= 2 * n; i++) {
        if(i & 1) {
            dp0[i] = dp0[i - 1] - a[i];
            dp1[i] = dp1[i - 1] + a[i];
        } else {
            dp0[i] = dp0[i - 1] + a[i];
            dp1[i] = dp1[i - 1] - a[i];
        }
    }
    ll sum = 0;
    for(int i = 1; i <= n; i++) {
        int j = 2 * n - i + 1;
        ll t;
        if(i & 1) {
            t = dp0[j] - dp0[i - 1];
        } else {
            t = dp1[j] - dp1[i - 1];
        }
        cout << sum + t << " \n"[i == n];
        sum -= a[i];
        sum += a[j];
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
