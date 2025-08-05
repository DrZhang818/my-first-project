#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
//https://codeforces.com/problemset/problem/1879/C

const int MOD = 998244353;
const int N = 200000;
int fac[N + 1];
void solve() {
    string s;
    cin >> s;
    int c0 = 0, c1 = 0, n = s.size();
    int cnt0 = 0, cnt1 = 0, x = 0;
    int p0 = 1, p1 = 1;
    for(int i = 0, tag = 0; i < n; i++) {
        if(s[i] - '0' != tag) {
            c0++;
            x++;
        } else {
            tag ^= 1;
            cnt0 += x;
            p0 = 1LL * p0 * (x + 1) % MOD;
            x = 0;
        }
    }   
    cnt0 += x;
    p0 = 1LL * p0 * (x + 1) % MOD;
    x = 0;
    for(int i = 0, tag = 1; i < n; i++) {
        if(s[i] - '0' != tag) {
            c1++;
            x++;
        } else {
            tag ^= 1;
            cnt1 += x;
            p1 = 1LL * p1 * (x + 1) % MOD;
            x = 0;
        }
    }
    cnt1 += x;
    p1 = 1LL * p1 * (x + 1) % MOD;
    if(c0 < c1) {
        cout << c0 << " " << 1LL * p0 * fac[cnt0] % MOD << "\n";
    } else if(c0 > c1) {
        cout << c1 << " " << 1LL * p1 * fac[cnt1] % MOD << "\n";
    } else {
        cout << c0 << " " << (1LL * p0 * fac[cnt0] % MOD + 1LL * p1 * fac[cnt1] % MOD) % MOD << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    fac[0] = 1;
    for(int i = 1; i <= N; i++) {
        fac[i] = 1LL * fac[i - 1] * i % MOD;
    }
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
