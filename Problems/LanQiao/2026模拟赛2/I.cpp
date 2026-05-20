#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;
constexpr int N = 4000;

vector<i64> minp, primes;

void solve() {
    i64 x;
    cin >> x;

    for(auto p : primes) {
        if(x % p == 0) {
            int c = 0;
            while(x % p == 0) {
                c++;
                x /= p;
            }
            if(c == 1) {
                cout << "no\n";
                return;
            }
        }
    }

    i64 a = sqrt(x);
    for(i64 i = max(0LL, a - 2); i <= a + 2; i++) {
        if(i * i == x) {
            cout << "yes\n";
            return;
        }
    }

    a = cbrt(x);
    for(i64 i = max(0LL, a - 2); i <= a + 2; i++) {
        if(i * i * i == x) {
            cout << "yes\n";
            return;
        }
    }

    cout << "no\n";
}   

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    minp.resize(N + 1);
    for(int i = 2; i <= N; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
        }
        for(auto p : primes) {
            if(i * p > N) break;
            minp[i * p] = p;
            if(minp[i] == p) break;
        }
    }

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}