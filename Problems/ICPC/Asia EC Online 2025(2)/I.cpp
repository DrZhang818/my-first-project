#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;
int fast_pow(int a, int b) {
    int res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}
int inv(int x) {
    return fast_pow(x, MOD - 2);
}
void gauss(vector<vector<int>> &a) {
    int n = a.size() - 1;
    for(int cur = 1; cur <= n; cur++) {
        int mx = cur;
        for(int i = 1; i <= n; i++) {
            if(i < cur && a[i][cur] > 0) continue;
            if(a[i][cur] > a[mx][cur]) mx = i;
        }
        swap(a[mx], a[cur]);
        if(a[cur][cur] == 0) continue;
        int tmp = inv(a[cur][cur]);
        for(int j = cur; j <= n + 1; j++) a[cur][j] = 1LL * a[cur][j] * tmp % MOD;
        for(int i = 1; i <= n; i++) {
            if(i == cur) continue;
            int fac = a[i][cur];
            for(int j = cur; j <= n + 1; j++) a[i][j] = (a[i][j] - 1LL * a[cur][j] * fac % MOD + MOD) % MOD;
        }
    }
}
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
void solve() {
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
    }   
    vector<vector<int>> a(1000, vector<int>(1001)); 
    for(int c = 1; c <= 999; c++) {
        cout << "? " << 1 << " " << n << " " << c << endl;
        cin >> a[c][1000];
        for(int j = 1; j <= 999; j++) {
            a[c][j] = fast_pow(c, j);
        }
    }
    gauss(a);
    int k;
    cout << "!" << endl;
    cin >> k;
    int ans = 0;
    for(int i = 1; i <= 999; i++) {
        add(ans, 1LL * a[i][1000] * fast_pow(k, i) % MOD);
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
