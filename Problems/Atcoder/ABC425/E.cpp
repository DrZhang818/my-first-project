#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int N = 5000;
int MOD;

vector<int> primes, minp;
vector<PII> divide[N + 1];
void sieve(int n) {
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
    for(int i = 2; i <= N; i++) {
        int x = i;
        while(x > 1) {
            int p = minp[x], c = 0;
            while(x % p == 0) {
                c++;
                x /= p;
            }
            divide[i].emplace_back(p, c);
        }
    }
}
int fast_pow(int a, int b) {
    int res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}
void solve() {
    int n;
    cin >> n;
    int tot = 0;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        tot += a[i];
    }
    vector<int> cnt(tot + 2), cp(tot + 1);
    for(int i = 1; i <= n; i++) {
        int x = a[i];
        cnt[1]--;
        cnt[x + 1]++;
    }
    cnt[1]++;
    cnt[tot + 1]--;
    for(int i = 1; i <= tot; i++) {
        cnt[i] += cnt[i - 1];
    }
    for(int i = 1; i <= tot; i++) {
        if(cnt[i]) {
            for(auto &[p, c] : divide[i]) {
                cp[p] += c * cnt[i];
            }
        }
    }
    int ans = 1;
    for(int p : primes) {
        if(p > tot) {
            break;
        }
        if(cp[p]) {
            ans = 1LL * ans * fast_pow(p, cp[p]) % MOD;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t >> MOD;
    sieve(N);
    while(t--) {
        solve();
    }
    return 0;
}
