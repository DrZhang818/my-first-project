#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

ll get(ll x) {
    ll p = x / 4 * 4;
    ll res = 0;
    while(p <= x) {
        res ^= p;
        p++;
    }
    return res;
}
void solve() {
    ll a, b;
    cin >> a >> b;
    if(a == 0) {
        cout << get(b) << "\n";
    } else {
        cout << (get(b) ^ get(a - 1)) << "\n";
    }
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
