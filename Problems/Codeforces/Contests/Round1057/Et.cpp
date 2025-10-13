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

int cal(int x, int p) {
    int res = 0; 
    while(x /= p) {
        res += x;
    }
    return res;
}

void solve() {
    int n, m;
    cin >> n >> m;
    ll ans = 0;

    vector<int> val;
    for(int x = n; x >= 1; x--) {
        int cur = x;
        while(cur > 1) {
            val.push_back(minp[cur]);
            cur /= minp[cur];
        }
        if(minp[x] == x) {
            break;
        }
    }
    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());
    for(int x = n - 1; x >= 1; x--) {
        if(minp[x + 1] == x + 1) {
            break;
        }
        int res = inf;
        for(auto p : val) {
            int a = cal(x, p);
            int b = cal(n, p);
            ll pe = p;
            for(int e = 1; pe <= m; e++, pe *= p) {
                if(a / e != b / e) {
                    res = min(res, a / e);
                }
            }
        }
        ans += res;
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
