#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

int mod(ll x) {
    return (x % MOD + MOD) % MOD;
}

void solve() {
    int n;
    cin >> n;
    int x = 1, y = 0;
    for(int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        int nx = mod(1LL * x * a - 1LL * y * b);
        int ny = mod(1LL * x * b + 1LL * y * a);
        x = nx;
        y = ny;
    }
    cout << x << " " << y << "\n";
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
