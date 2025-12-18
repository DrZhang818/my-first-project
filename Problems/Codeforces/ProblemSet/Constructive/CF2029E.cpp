#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr int N = 400000;

vector<int> minp, primes;
void init(int n) {
    minp.resize(n + 1);
    for(int i = 2; i <= n; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
        }
        for(auto p : primes) {
            if(i * p > n) break;
            minp[i * p] = p;
            if(p == minp[i]) break;
        }
    }
}

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int c = 0, p = -1;
    for(int i = 1; i <= n; i++) {
        if(minp[a[i]] == a[i]) {
            c++;
            p = a[i];
        }
    }
    if(c >= 2) {
        cout << -1 << "\n";
        return;
    }
    if(p == -1) {
        cout << 2 << "\n";
        return;
    }
    for(int i = 1; i <= n; i++) {
        if(a[i] == p) continue;
        int x;
        if(a[i] % 2 == 0) {
            x = a[i];
        } else {
            x = a[i] - minp[a[i]];
        }
        if(x < 2 * p) {
            cout << -1 << "\n";
            return;
        }
    }
    cout << p << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    init(N);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
