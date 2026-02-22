#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr int N = 10000000;

vector<int> minp, primes, phi;
void sieve(int n) {
    minp.resize(n + 1);
    phi.resize(n + 1);
    for(int i = 2; i <= n; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
            phi[i] = i - 1;
        }
        for(auto p : primes) {
            if(i * p > n) {
                break;
            }
            minp[i * p] = p;
            if(minp[i] == p) {
                phi[i * p] = phi[i] * p;
                break;
            }
            phi[i * p] = phi[i] * (p - 1);
        }
    }
}

// int fast_pow(int a, int b, int MOD) {
//     int res = 1;
//     while(b) {
//         if(b & 1) res = 1LL * res * a % MOD;
//         a = 1LL * a * a % MOD;
//         b >>= 1;
//     }
//     return res;
// }

int tag_pow(ll a, ll b, int MOD) {
    ll res = 1;
    bool tag = false;
    if(a >= MOD) {
        a %= MOD;
        tag = true;
    }
    while(b) {
        if(b & 1) {
            res *= a;
            if(res >= MOD) {
                res %= MOD;
                tag = true;
            }
        }
        a *= a;
        if(a >= MOD) {
            a %= MOD;
            tag = true;
        }
        b >>= 1;
    }
    return res + (tag ? MOD : 0);
}

int dfs(int x) {
    if(x == 1) {
        return 1;
    }
    return tag_pow(2, dfs(phi[x]), x);
}

void solve() {
    int n;
    cin >> n;
    cout << dfs(n) % n << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    sieve(N);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
