#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    ll a, b;
    cin >> a >> b;
    if(b % 2 == 0) {
        if(b % 4 != 0 && a % 2 != 0) {
            cout << -1 << "\n";
            return;
        }
        cout << 2 + a * (b / 2) << "\n";
    } else {
        if(a % 2 == 0) {
            cout << -1 << "\n";
            return;
        }
        cout << a * b + 1 << "\n";
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
