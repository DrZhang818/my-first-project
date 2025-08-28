#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

vector<int> minp, primes, phi;
void init(int n) {
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

void solve() {
    int n;
    cin >> n;
    if(n == 1) {
        cout << 0 << "\n";
        return;
    }
    init(n);
    ll ans = 0;
    for(int i = 2; i <= n - 1; i++) {
        ans += phi[i];
    }
    cout << 2 * ans + 3 << "\n";
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
