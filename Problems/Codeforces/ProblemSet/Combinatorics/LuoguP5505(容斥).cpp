#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;
const int N = 2000;

//https://www.luogu.com.cn/problem/P5505
int C[N + 1][N + 1];
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> a[i];
    }
    int ans = 0;
    for(int i = 0, tag = 1; i < n; i++, tag ^= 1) {
        int cur = C[n][i];
        for(int j = 1; j <= m; j++) {
            cur = 1LL * cur * C[n - i - 1 + a[j]][n - i - 1] % MOD;;
        }
        if(tag) {
            add(ans, cur);
        } else {
            add(ans, MOD - cur);
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int i = 0; i <= N; i++) {
        for(int j = 0; j <= i; j++) {
            if(j == 0) C[i][j] = 1;
            else C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
    }
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
