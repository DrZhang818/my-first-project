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
    ll ans = 0;
    for(int s = 2; s <= x - 1; s++) {
        for(int a = 1; a <= s / 2; a++) {
            int b = s - a;
            if(n - a * b < s) {
                break;
            }
            ll t = min((n - a * b) / s, x - s);
            if(a == b) {
                ans += t;
            } else {
                ans += t * 2;
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
