#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://www.luogu.com.cn/problem/P3200
vector<int> minp, primes;
void init(int n) {
    minp.resize(n + 1);
    for(int i = 2; i <= n; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
        }
        for(int p : primes) {
            if(i * p > n) {
                break;
            }
            minp[i * p] = p;
            if(minp[i] == p) {
                break;
            }
        }
    }
}
int fast_pow(int a, int b, int MOD) {
    int res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}
void solve() {
    int n, p;
    cin >> n >> p;
    init(2 * n);
    vector<int> cnt(2 * n + 1);
    for(int i = n + 2; i <= 2 * n; i++) {
        int x = i;
        while(x != 1) {
            cnt[minp[x]]++;
            x /= minp[x];
        }
    }
    for(int i = 1; i <= n; i++) {
        int x = i;
        while(x != 1) {
            cnt[minp[x]]--;
            x /= minp[x];
        }
    }
    int ans = 1;
    for(int i = 1; i <= 2 * n; i++) {
        if(cnt[i]) {
            ans = 1LL * ans * fast_pow(i, cnt[i], p) % p;
        }
    }
    cout << ans << "\n";
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
