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

int cal(int n, int m) {
    int res = 0, tm = m; 
    while(n >= m) {
        res += n / m;
        m *= tm;
    }
    return res;
}

int get(int a, int b, int m) {
    int va = inf, vb = inf;
    while(m > 1) {
        int p = minp[m];
        int c = 0;
        while(m % p == 0) {
            c++;
            m /= p;
        }
        va = min(va, cal(a, p) / c);
        vb = min(vb, cal(b, p) / c);
    }
    return min(va, vb);
}

void solve() {
    // int n = 15;
    // for(int x = 1; x <= n - 1; x++) {
    //     for(int k = 2; k <= 10; k++) {
    //         cout << "a: " << x << " b: " << n << " " << " k: " << k << " val: " << get(x, n, k) << "\n";
    //     }
    // }
    int n, m;
    cin >> n >> m;
    int ans = 0;
    for(int x = 1; x < n; x++) {
        int cur = inf;
        for(int k = 2; k <= m; k++) {
            cur = min(cur, get(x, n, k));
        }
        ans += cur;
    }
    cerr << ans << "\n";
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
