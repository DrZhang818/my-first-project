#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = ll(1E18);

using Matrix = vector<vector<ll>>;

Matrix operator * (const Matrix &a, const Matrix &b) {
    int n = a.size();
    Matrix res(n, vector<ll>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            ll mx = -inf;
            for(int k = 0; k < n; k++) {
                mx = max(mx, a[i][k] + b[k][j]);
            }
            res[i][j] = mx;
        }
    }
    return res;
}

Matrix fast_pow(Matrix &a, int b) {
    auto res = a;
    b--;
    while(b) {
        if(b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

void solve() {
    int n, m, k, R;
    cin >> n >> m >> k >> R;
    vector<int> a(n), c(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i] >> c[i];
    }
    const int N = 1 << n;
    Matrix dp(N, vector<ll>(N));
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            int cost = 0;
            ll dam = 0;
            for(int s = 0; s < n; s++) {
                if(j >> s & 1) {
                    if(i >> s & 1) {
                        cost += c[s] + k;
                    } else {
                        cost += c[s];
                    }
                    dam += a[s];
                }
            }
            if(cost > m) {
                dp[i][j] = -inf;
            } else {
                dp[i][j] = dam;
            }
        }
    }
    dp = fast_pow(dp, R);
    ll ans = *max_element(dp[0].begin(), dp[0].end());
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
