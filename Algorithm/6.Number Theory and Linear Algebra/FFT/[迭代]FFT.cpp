#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
typedef complex<double> cdb;
const int inf = 1000000000;
const db PI = acos(-1.0);

vector<int> rev;
void change(vector<cdb> &a, int n) {
    rev.resize(n);
    for(int i = 0; i < n; i++) {
        int k = __builtin_ctz(n) - 1;
        rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
    }
    for(int i = 0; i < n; i++) {
        if(rev[i] < i) {
            swap(a[i], a[rev[i]]);
        }
    }
}
void FFT(vector<cdb> &a, int n, int op) {
    change(a, n);
    for(int s = 2; s <= n; s <<= 1) {
        cdb w1({cos(2 * PI / s), sin(2 * PI / s) * op});
        for(int i = 0; i < n; i += s) {
            cdb wk({1, 0});
            for(int j = 0; j < s / 2; j++) {
                cdb x = a[i + j], y = a[i + j + s / 2] * wk;
                a[i + j] = x + y;
                a[i + j + s / 2] = x - y;
                wk *= w1;
            }
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    int p = 1, tot = n + m;
    while(p <= tot) p <<= 1;
    vector<cdb> A(p), B(p);
    for(int i = 0; i <= n; i++) {
        cin >> A[i];
    }
    for(int i = 0; i <= m; i++) {
        cin >> B[i];
    }
    FFT(A, p, 1);
    FFT(B, p, 1);
    vector<cdb> ans(p);
    for(int i = 0; i < p; i++) {
        ans[i] = A[i] * B[i];
    }
    FFT(ans, p, -1);
    for(int i = 0; i <= tot; i++) {
        cout << int(ans[i].real() / p + 0.5) << " \n"[i == tot];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
