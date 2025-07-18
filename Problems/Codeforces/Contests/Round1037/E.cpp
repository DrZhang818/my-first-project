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
    vector<ll> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    auto ans = a;
    for(int i = n; i >= 1; i--) {
        ans[i] = lcm(ans[i], b[i]);
    }
    ll g = 0;
    for(int i = 1; i <= n; i++) {
        g = gcd(g, ans[i]);
        if(g != a[i]) {
            cout << "NO\n";
            return;
        }
    }
    g = 0;
    for(int i = n; i >= 1; i--) {
        g = gcd(g, ans[i]);
        if(g != b[i]) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
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
