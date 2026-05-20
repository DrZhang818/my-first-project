#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

vector<int> minp, primes, phi;
vector<i64> sum;

auto init(int n) {
    minp.resize(n + 1);
    phi.resize(n + 1);

    for(int i = 2; i <= n; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
            phi[i] = i - 1;
        }
        for(auto p : primes) {
            if(i * p > n) break;
            minp[i * p] = p;
            if(minp[i] == p) {
                phi[i * p] = phi[i] * p;
                break;
            } else {
                phi[i * p] = phi[i] * phi[p];
            }
        }
    }

    sum.resize(n + 1);

    for(auto p : primes) {
        for(int i = 1; i * p <= n; i++) {
            sum[i * p] += phi[i];
        }
    }

    for(int i = 1; i <= n; i++) {
        sum[i] += sum[i - 1];
    }

    return 1;
}

void solve() {
    int l, r;
    cin >> l >> r;

    i64 ans = sum[r] - sum[l - 1];

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    init(2E5);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
