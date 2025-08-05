#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
typedef complex<double> cdb;
const int inf = 1000000000;
const db PI = acos(-1.0);

void FFT(vector<cdb> &a, int n, int op) {
    if(n == 1) return;
    vector<cdb> a1(n >> 1), a2(n >> 1);
    for(int i = 0; i < n / 2; i++) {
        a1[i] = a[i << 1];
        a2[i] = a[i << 1 | 1];
    }
    FFT(a1, n >> 1, op);
    FFT(a2, n >> 1, op);
    cdb w1({cos(2 * PI / n), sin(2 * PI / n) * op});
    cdb wk({1, 0});
    for(int i = 0; i < n / 2; i++) {
        a[i] = a1[i] + a2[i] * wk;
        a[i + n / 2] = a1[i] - a2[i] * wk;
        wk *= w1;
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
