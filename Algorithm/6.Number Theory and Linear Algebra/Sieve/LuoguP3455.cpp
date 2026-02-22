#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr int N = 50000;

ll mu[N + 1];
int minp[N + 1];
vector<int> primes;

int init = []() {
    mu[1] = 1;

    for(int i = 2; i <= N; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
            mu[i] = -1;
        }
        for(auto p : primes) {
            if(i * p > N) break;
            minp[i * p] = p;
            if(minp[i] == p) {
                mu[i * p] = 0;
                break;
            } else {
                mu[i * p] = -mu[i];
            }
        }
    }

    for(int i = 2; i <= N; i++) {
        mu[i] += mu[i - 1];
    }

    return 1;
}();

ll get(int L, int R) {
    return mu[R] - mu[L - 1];
}

void solve() {  
    int q;
    cin >> q;
    while(q--) {
        int a, b, d;
        cin >> a >> b >> d;
        a /= d;
        b /= d;
        ll ans = 0;
        for(int L = 1, R; L <= min(a, b); L = R + 1) {
            R = min(a / (a / L), b / (b / L));
            ans += get(L, R) * (a / L) * (b / L);
        }
        cout << ans << "\n";
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
