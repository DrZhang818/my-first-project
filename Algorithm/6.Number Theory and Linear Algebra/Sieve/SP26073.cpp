#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr int N = 10000000;

int minp[N + 1], e[N + 1];
ull mu[N + 1], mu2[N + 1], d[N + 1];
vector<int> primes;

void init() {
    mu[1] = mu2[1] = d[1] = 1;
    for(int i = 2; i <= N; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
            mu[i] = -1;
            e[i] = 1;
            d[i] = 2;
        }
        for(auto p : primes) {
            if(i * p > N) break;
            minp[i * p] = p;
            if(minp[i] == p) {
                e[i * p] = e[i] + 1;
                d[i * p] = d[i] / (e[i] + 1) * (e[i * p] + 1);
                break;
            } else {
                mu[i * p] = -mu[i];
                e[i * p] = 1;
                d[i * p] = d[i] * d[p];
            }
        }
    }

    for(int i = 2; i <= N; i++) {
        mu2[i] = mu2[i - 1] + (mu[i] != 0);
        d[i] += d[i - 1];
    }
}

ull sum_mu2(ll x) {
    if(x <= N) return mu2[x];
    ull res = 0;
    for(ll i = 1; i * i <= x; i++) {
        res += mu[i] * (x / (i * i));
    }
    return res;
}

ull sum_mu2(ll l, ll r) {
    return sum_mu2(r) - sum_mu2(l - 1);
}

ull sum_d(ll x) {
    if(x <= N) return d[x];
    ull res = 0;
    ll sq = sqrt(x);
    for(ll i = 1; i <= sq; i++) {
        res += x / i;
    }
    return 2 * res - (ull)sq * sq;
}

void solve() {  
    ll n;
    cin >> n;

    ull ans = 0;
    for(ll L = 1, R; L <= n; L = R + 1) {
        R = n / (n / L);
        ans += sum_mu2(L, R) * sum_d(n / L);
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    init();

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
