#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

constexpr int N = 1E7;

vector<int> minp, primes;

auto init = []() {

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

    return 1;
}();

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);    
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> d1(n + 1), d2(n + 1);

    for(int i = 1; i <= n; i++) {
        int x = a[i];
        int p = minp[x];
        while(minp[x] == p) {
            x /= p;
        }
        if(x == 1) {
            d1[i] = d2[i] = -1;
            continue;
        } 
        d1[i] = a[i] / x;
        d2[i] = x;
    }

    for(int i = 1; i <= n; i++) {
        cout << d1[i] << " \n"[i == n];
    }
    for(int i = 1; i <= n; i++) {
        cout << d2[i] << " \n"[i == n];
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
