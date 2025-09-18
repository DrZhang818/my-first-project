#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    ll a, b, c;
    cin >> a >> b >> c;
    if(b > a || b > c) {
        cout << min(a, c) << "\n";        
    } else {
        a -= b;
        c -= b;
        cout << b + min({a, c, (a + c) / 3}) << "\n";
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
