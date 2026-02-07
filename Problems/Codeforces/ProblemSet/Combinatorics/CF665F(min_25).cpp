#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

vector<int> minp, primes;
vector<ll> sp0;
void init(int n) {
    minp.resize(n + 1);
    sp0.resize(n + 1);
    for(int i = 2; i <= n; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
            int j = primes.size();
            sp0[j] = sp0[j - 1] + 1;
        }
        for(auto p : primes) {
            if(i * p > n) break;
            minp[i * p] = p;
            if(minp[i] == p) break;
        }
    }
}

void solve() {  
    ll n;
    cin >> n;
    int sq = sqrt(n);
    init(sq);

    vector<ll> w;
    vector<int> id1(sq + 1), id2(sq + 1);
    for(ll L = 1, R; L <= n; L = R + 1) {
        R = n / (n / L);
        ll v = n / L;
        w.push_back(v);
        if(v <= sq) {
            id1[v] = w.size() - 1;
        } else {
            id2[R] = w.size() - 1;
        }
    }

    auto get = [&](ll x) {
        return x <= sq ? id1[x] : id2[n / x];
    };  

    vector<ll> g0(w.size());
    for(int i = 0; i < w.size(); i++) {
        ll x = w[i];
        g0[i] = x - 1;
    }

    ll ans = 0;

    for(int j = 0; j < primes.size(); j++) {
        ll p = primes[j];
        ll p2 = p * p;
        for(int i = 0; i < w.size(); i++) {
            if(w[i] < p2) break;
            int k = get(w[i] / p);
            g0[i] -= g0[k] - sp0[j];
        }
    }

    for(int j = 0; j < primes.size(); j++) {
        ll p = primes[j];
        if(p * p <= n && p * p * p <= n) {
            ans++;
        }
        int k = get(w[0] / p);
        ans += g0[k] - sp0[j + 1];
    }

    cout << ans << "\n";

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
