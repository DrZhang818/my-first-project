#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr int MOD = 1000000007;
constexpr int phi = MOD - 1;
constexpr int N = 1000000;
constexpr int M = __lg(N);

void add(int &x, int y, int m) {
    x += y - m; x += x >> 31 & m;
}

int power(int a, int b) {
    int res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}

int fib[N + 1];
int mu[N + 1];
int minp[N + 1];
int pre[N + 1];
int ipre[N + 1];
vector<int> primes;
int init = []() -> int {

    fib[1] = 1;
    pre[1] = 1;
    for(int i = 2; i <= N; i++) {
        pre[i] = 1;
        fib[i] = fib[i - 1] + fib[i - 2];
        if(fib[i] >= MOD) fib[i] -= MOD;
    }

    mu[1] = 1;
    for(int i = 2; i <= N; i++) {
        if(!minp[i]) {
            minp[i] = i;
            mu[i] = phi - 1;
            primes.push_back(i);
        }
        for(auto p : primes) {
            if(i * p > N) break;
            minp[i * p] = p;
            if(minp[i] == p) {
                break;
            } else {
                add(mu[i * p], phi - mu[i], phi);
            }
        }
    }

    for(int i = 1; i <= N; i++) {
        for(int j = i; j <= N; j += i) {
            pre[j] = 1LL * pre[j] * power(fib[i], mu[j / i]) % MOD;
        }
    }

    vector<int> t(N + 1);
    for(int i = 1; i <= N; i++) {
        t[i] = pre[i];
    }

    for(int i = 2; i <= N; i++) {
        pre[i] = 1LL * pre[i] * pre[i - 1] % MOD;
    }

    ipre[N] = power(pre[N], MOD - 2);
    for(int i = N - 1; i >= 1; i--) {
        ipre[i] = 1LL * ipre[i + 1] * t[i + 1] % MOD;
    }

    return 1;
}();

int sum_mu(int L, int R) {
    return (mu[R] - mu[L - 1] + phi) % phi;
}

int prod(int L, int R) {
    if(L == 1) return pre[R];
    return 1LL * pre[R] * ipre[L - 1] % MOD;
}

void solve() {  
    int n, m;
    cin >> n >> m;
    int ans = 1;
    for(int L = 1, R; L <= min(n, m); L = R + 1) {
        R = min(n / (n / L), m / (m / L));
        ans = 1LL * ans * power(prod(L, R), 1LL * (n / L) * (m / L) % phi) % MOD;
    }
    cout << ans << "\n";
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
