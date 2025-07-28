#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

vector<int> minp, primes;
void sieve(int n) {
    minp.resize(n + 1);
    for(int i = 2; i <= n; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
        }
        for(int p : primes) {
            if(i * p > n) break;
            minp[i * p] = p;
            if(minp[i] == p) break;
        }
    }
}
void solve() {
    ll l, r;
    cin >> l >> r;
    if(l == r) {
        cout << 1 << "\n";
        return;
    }
    int ans = 1;
    l++;
    int sz = primes.size();
    vector<int> cnt(sz);
    vector<int> vis(r - l + 1);
    for(int i = 0; i < sz; i++) {
        ll p = primes[i], cur = p;
        while(cur < l) cur *= p;
        while(cur <= r) {
            cnt[i]++;   
            if(cur <= r / p) cur *= p;
            else break;
        }
    }
    for(ll p : primes) {
        ll t = (l + p - 1) / p;
        ll cur = p;
        cur *= t;
        while(cur <= r) {
            vis[cur - l] = 1;
            cur += p;
        }
    }
    ans += accumulate(cnt.begin(), cnt.end(), 0);
    for(int i = 0; i <= r - l; i++) {
        if(!vis[i]) {
            ans++;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    sieve(10000000);
    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}