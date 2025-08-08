#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;
const int N = 1000000;

//https://codeforces.com/contest/839/problem/D

vector<int> fac[N + 1];
int sum[200001];
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
vector<int> minp, primes;
void init(int n) {
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
void chmax(int &a, int b) {
    if(a < b) {
        a = b;
    }
}
void solve() {
    int n;
    cin >> n;
    vector<int> cnt(N + 1);
    int mx = 0;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        chmax(mx, x);
        for(int j : fac[x]) {
            cnt[j]++;
        }
    }
    int ans = 0;
    vector<int> dp(mx + 1);
    for(int i = mx; i >= 2; i--) {
        dp[i] = sum[cnt[i]];
        for(int j = i * 2; j <= mx; j += i) {
            add(dp[i], MOD - dp[j]);
        }
    }
    for(int d = 2; d <= mx; d++) {
        add(ans, 1LL * d * dp[d] % MOD);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    init(N);
    for(int i = 2; i <= N; i++) {
        for(int j = i; j <= N; j += i) {
            fac[j].push_back(i);
        }
    }
    int cur = 1;
    for(int i = 1; i <= 200000; i++) {
        sum[i] = 1LL * i * cur % MOD;
        cur = 2LL * cur % MOD;
    }
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
