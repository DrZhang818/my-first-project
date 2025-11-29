#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = int(1E9) + 7;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

using T = vector<vector<int>>;

T operator * (const T &a, const T &b) {
    assert(a[0].size() == b.size());
    T res(a.size(), vector<int>(b[0].size()));
    for(int i = 0; i < a.size(); i++) {
        for(int k = 0; k < a[0].size(); k++) {
            if(a[i][k] == 0) {
                continue;
            }
            for(int j = 0; j < b[0].size(); j++) {
                add(res[i][j], 1LL * a[i][k] * b[k][j] % MOD);
            }
        }
    }
    return res;
}

T fast_pow(T &a, int b) {
    assert(a.size() == a[0].size());
    T res(a.size(), vector<int>(a.size()));
    for(int i = 0; i < a.size(); i++) {
        res[i][i] = 1;
    }
    while(b) {
        if(b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> k(101);
    for(int i = 1; i <= n; i++) {
        int d;
        cin >> d;
        k[d]++;
    }
    int mx = 100;
    while(k[mx] == 0) {
        mx--;
    }
    T mat(mx + 1, vector<int>(mx + 1));
    for(int d = 1; d <= mx; d++) {
        mat[0][d - 1] = k[d];
    }
    mat[0][mx] = 1;
    for(int i = 1; i < mx; i++) {
        mat[i][i - 1] = 1;
    }
    mat[mx][mx] = 1;
    mat = fast_pow(mat, x);
    int ans = mat[0][0];
    add(ans, mat[0][mx]);
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
