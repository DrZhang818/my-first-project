#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/problemset/problem/991/E
ll C[19][19];
ll fac[19];
void solve() {
    ll n;
    cin >> n;
    vector<int> cnt(10);
    while(n) {
        cnt[n % 10]++;
        n /= 10;
    }
    int c0 = cnt[0];
    vector<int> a;
    for(int i = 1; i <= 9; i++) {
        if(cnt[i]) {
            a.push_back(cnt[i]);
        }
    }
    int sz = a.size();
    auto dfs = [&](this auto &&self, int pos, ll div, int num) -> ll {
        ll res = 0;
        if(pos == -1) {
            res = fac[num] / div;
            if(c0 == 0) return res;
            ll p = 0;
            for(int i = 1; i <= c0; i++) {
                p += C[num - 1 + i][i];
            }
            return res * p;
        }
        for(int i = 1; i <= a[pos]; i++) {
            res += self(pos - 1, div * fac[i], num + i);
        }
        return res;
    };
    ll ans = dfs(sz - 1, 1, 0);
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    fac[0] = 1;
    for(int i = 1; i <= 18; i++) {
        fac[i] = fac[i - 1] * i;
    }
    for(int i = 0; i <= 18; i++) {
        for(int j = 0; j <= i; j++) {
            if(j == 0) C[i][j] = 1;
            else C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        }
    }
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
