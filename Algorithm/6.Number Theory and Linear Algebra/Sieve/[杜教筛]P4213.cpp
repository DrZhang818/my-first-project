#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
using i64 = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr int N = 2000000;

i64 phi[N + 1];
i64 mu[N + 1];
int minp[N + 1];
vector<int> primes;

void init() {
    phi[1] = 1;
    mu[1] = 1;

    for(int i = 2; i <= N; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
            phi[i] = i - 1;
            mu[i] = -1;
        }
        for(auto p : primes) {
            if(i * p > N) break;
            minp[i * p] = p;
            if(minp[i] == p) {
                phi[i * p] = phi[i] * p;
                mu[i * p] = 0;
                break;                
            } else {
                phi[i * p] = phi[i] * (p - 1);
                mu[i * p] = -mu[i];
            }
        }
    }

    for(int i = 2; i <= N; i++) {
        phi[i] += phi[i - 1];
        mu[i] += mu[i - 1];
    }

};

map<i64, pair<i64, i64>> memo;

pair<i64,i64> get(i64 n) {
    if(n <= N) {
        return {phi[n], mu[n]};
    }
    auto it = memo.find(n);
    if(it != memo.end()) {
        return it->second;
    }
    
    i64 sum_phi = n * (n + 1) / 2;
    i64 sum_mu = 1;
    for(i64 L = 2, R; L <= n; L = R + 1) {
        R = n / (n / L);
        auto [x, y] = get(n / L);
        sum_phi -= x * (R - L + 1);
        sum_mu -= y * (R - L + 1);
    }

    return memo[n] = {sum_phi, sum_mu};
}

void solve() {  
    int n;
    cin >> n;

    auto [sum_phi, sum_mu] = get(n);

    cout << sum_phi << " " << sum_mu << "\n";
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
