#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    ll a, b, k;
    cin >> a >> b >> k;
    ll g = gcd(a, b);
    a /= g;
    b /= g;
    if(a - k <= 0 && b - k <= 0) {
        cout << 1 << "\n";
        return;
    }
    cout << 2 << "\n";
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
