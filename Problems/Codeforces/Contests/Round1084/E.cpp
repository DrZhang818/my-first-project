#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;
constexpr int N = 1E6;

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

    bool sorted = true;
    for(int i = 2; i <= n; i++) {
        if(a[i] < a[i - 1]) {
            sorted = false;
        }
    }
    if(sorted) {
        cout << "Bob\n";
        return;
    }

    for(int i = 1; i <= n; i++) {
        if(a[i] == 1) continue;
        int p = minp[a[i]];
        while(a[i] % p == 0) {
            a[i] /= p;
        }
        if(a[i] > 1) {
            cout << "Alice\n";
            return;
        }
        a[i] = p;
    }

    for(int i = 2; i <= n; i++) {
        if(a[i] < a[i - 1]) {
            cout << "Alice\n";
            return;
        }
    }

    cout << "Bob\n";
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
