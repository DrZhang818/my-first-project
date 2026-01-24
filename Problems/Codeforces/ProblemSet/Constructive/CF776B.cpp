#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr int N = 100005;

vector<int> minp, primes;
int sieve = []() {
    minp.resize(N + 1);
    for(int i = 2; i <= N; i++) {
        if(minp[i] == 0) {
            minp[i] = i;
            primes.push_back(i);
        }
        for(auto p : primes) {
            if(i * p > N) break;
            minp[i * p] = p;
            if(minp[i] == p) break;
        }
    }
    return 1;
}();

void solve() {  
    int n;
    cin >> n;
    if(n <= 2) {
        cout << 1 << "\n";
    } else {
        cout << 2 << "\n";
    }
    vector<int> col(n + 1, 2);
    for(int i = 1; i <= n; i++) {
        if(minp[i + 1] == i + 1) {
            col[i] = 1;
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << col[i] << " \n"[i == n];
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
