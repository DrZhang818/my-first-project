#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, p;
    cin >> n >> p;
    vector<int> inv(n + 1);
    inv[1] = 1;
    for(int i = 2; i <= n; i++) {
        inv[i] = 1LL * (p - p / i) * inv[p % i] % p;
    }
    for(int i = 1; i <= n; i++) {
        cout << inv[i] << "\n";
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
