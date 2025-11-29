#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

// vector<int> minp, primes;
// void sieve(int n) {
//     minp.resize(n + 1);
//     for(int i = 2; i <= n; i++) {
//         if(!minp[i]) {
//             minp[i] = i;
//             primes.push_back(i);
//         }
//         for(auto p : primes) {
//             if(i * p > n) break;
//             minp[i * p] = p;
//             if(minp[i] == p) break;
//         }
//     }
// }

int fast_pow(int a, int b, int MOD) {
    int res = 1;
    while(b) {
        if(b & 1) {
            res = 1LL * res * a % MOD;
        }
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}


void solve() {
    for(int i = 2; i <= 1000; i += 2) {
        cerr << "i: " << i << "\n";
        for(int j = 1, cur = 2; j <= 20; j++) {
            cerr << cur % i << " \n"[j == 20];
            cur = cur * 2 % i;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // sieve(int(1E7));
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
