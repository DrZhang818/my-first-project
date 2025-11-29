#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int N = 1000000;

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
            if(minp[i] == p) break;
        }
    }
}

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int p : primes) {
        for(int i = 1; i <= n; i++) {
            if(a[i] % p != 0) {
                cout << p << "\n";
                return;
            }
        }
    }
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
