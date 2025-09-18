#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

vector<int> primes, minp;
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

ll fast_pow(int a, int b) {
    ll res = 1;
    while(b) {
        if(b & 1) res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}

void solve() {
    sieve(1E6);
    

    for(int i = 1; i <= 100000; i++) {
        int j = i + 1;
        vector<int> fac;
        auto dfs = [&](this auto &&self, int pos, ll cur) -> bool {
            if(pos == fac.size()) {
                return cur == j;
            }
            for(int k = 1; k < 32; k++) {
                ll t = fast_pow(fac[pos], k);
                if(cur + t > j) {
                    break;
                }
                if(self(pos + 1, cur + t)) {
                    return true;
                }
            }
            return false;
        };
        int x = i;
        while(x > 1) {
            int p = minp[x];
            fac.push_back(p);
            while(x % p == 0) {
                x /= p;
            }
        }
        if(dfs(0, 0)) {
            cout << i << " " << j << "\n";
            for(int p : fac) {
                cout << p << " ";
            }
            cout << "\n\n";
        }
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
