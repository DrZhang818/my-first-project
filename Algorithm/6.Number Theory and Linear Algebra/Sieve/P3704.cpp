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
int dp[N + 1][M + 1];
vector<int> primes;
int init = []() -> int {

    fib[1] = 1;
    for(int i = 2; i <= N; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
        if(fib[i] >= MOD) fib[i] -= MOD;
        dp[i][0] = fib[i];
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

    for(int i = 2; i <= N; i++) {
        add(mu[i], mu[i - 1], phi);
    }

    for(int s = 1; s <= M; s++) {
        for(int i = 1; i + (1 << s) - 1 <= N; i++) {
            dp[i][s] = 1LL * dp[i][s - 1] * dp[i + (1 << s - 1)][s - 1] % MOD;
        }
    }

    return 1;
}();

int sum_mu(int L, int R) {
    return (mu[R] - mu[L - 1] + phi) % phi;
}

int prob_fib(int L, int R) {
    int res = fib[R];
    for(int s = M; s >= 0; s--) {
        if(L + (1 << s) - 1 < R) {
            res = 1LL * res * dp[L][s] % MOD;
            L += 1 << s;
        }
    }
    return res;
}

int cal(int x, int y) {
    int res = 0;
    for(int L = 1, R; L <= min(x, y); L = R + 1) {
        R = min(x / (x / L), y / (y / L));
        add(res, 1LL * sum_mu(L, R) * (x / L) % phi * (y / L) % phi, phi);
    }
    return res;
}

void solve() {  
    int n, m;
    cin >> n >> m;
    int ans = 1;
    for(int L = 1, R; L <= min(n, m); L = R + 1) {
        R = min(n / (n / L), m / (m / L));
        ans = 1LL * ans * power(prob_fib(L, R), cal(n / L, m / L)) % MOD;
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
