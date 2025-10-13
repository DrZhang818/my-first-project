#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

vector<int> minp, primes;
void sieve(int n) {
    minp.resize(n + 1);
    for(int i = 2; i <= n; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
        }
        for(auto p : primes) {
            if(i * p > n) break;
            minp[i * p] = p;
            if(minp[i] == p) break;
        }
    }
}

void solve() {
    int x, y;
    cin >> x >> y;
    int z = y - x;
    int ans = inf;
    while(z > 1) {
        int m = minp[z];
        while(z % m == 0) {
            z /= m;
        }
        if(x % m == y % m) {
            ans = min(ans, (m - x % m) % m);
        }
    }
    if(ans == inf) {
        cout << -1 << "\n";
        return;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    sieve(int(1E7));
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
