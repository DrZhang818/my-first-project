#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    int xa = 0, xb = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        xa ^= a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
        xb ^= b[i];
    }
    if(xa == xb) {
        cout << "Tie\n";
        return;
    }
    int p = -1;
    for(int i = n; i >= 1; i--) {
        if(a[i] ^ b[i]) {
            p = i;
            break;
        }
    }
    if(p == -1) {
        if(xa > xb) {
            cout << "Ajisai\n";
        } else {
            cout << "Mai\n";
        }
    } else {
        if(p & 1) {
            cout << "Ajisai\n";
        } else {
            cout << "Mai\n";
        }
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
