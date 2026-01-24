#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr int N = 50000;

ll mu[N + 1];
ll d[N + 1];
int minp[N + 1];
int e[N + 1];
vector<int> primes;

int init = []() {
    mu[1] = 1;
    d[1] = 1;

    for(int i = 2; i <= N; i++) {
        if(!minp[i]) {
            minp[i] = i;
            mu[i] = -1;
            e[i] = 1;
            d[i] = 2;
            primes.push_back(i);
        }
        for(auto p : primes) {
            if(i * p > N) break;
            minp[i * p] = p;
            if(minp[i] == p) {
                mu[i * p] = 0;
                e[i * p] = e[i] + 1;
                d[i * p] = d[i] / (e[i] + 1) * (e[i * p] + 1);
                break;
            } else {
                mu[i * p] = -mu[i];
                e[i * p] = 1;
                d[i * p] = d[i] * 2;
            }
        }
    }

    for(int i = 2; i <= N; i++) {
        mu[i] += mu[i - 1];
        d[i] += d[i - 1];
    }

    return 1;
}();

ll get(int L, int R) {
    return mu[R] - mu[L - 1];
}

void solve() {  
    int n, m;
    cin >> n >> m;

    ll ans = 0;

    for(ll L = 1, R; L <= min(n, m); L = R + 1) {
        R = min(n / (n / L), m / (m / L));
        ans += get(L, R) * d[n / L] * d[m / L];
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
