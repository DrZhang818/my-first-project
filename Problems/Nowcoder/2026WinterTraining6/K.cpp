#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    ll m, n, z;
    cin >> m >> n >> z;
    z %= (m + n);
    if(z == 0) z = m + n;
    if(z <= m) {
        cout << "0";
    } else {
        cout << "1";
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
