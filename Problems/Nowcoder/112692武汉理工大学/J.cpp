#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

vector<int> minp, primes;
void sieve(int n) {
    minp.assign(n + 1, 0);
    for(int i = 2; i <= n; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
        }
        for(auto p : primes) {
            if(p * i > n) {
                break;
            }
            minp[p * i] = p;
            if(p == minp[i]) {
                break;
            } 
        }
    }
}
void solve() {
    int n;
    cin >> n;
    int pos = lower_bound(primes.begin(), primes.end(), n + 1) - primes.begin();
    vector<int> a(n + 1);
    iota(a.begin(), a.end(), 0);
    for(int i = 1; i <= n; i++) {
        a[i] *= primes[pos + i];
    }
    for(int i = 1; i <= n; i++) {
        cout << a[i] << " \n"[i == n];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    sieve(20005);
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
