#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<int> A(n + 1), B(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> A[i] >> B[i];
    }

    auto w = A;

    vector<int> X(m + 1), Y(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> X[i] >> Y[i];
        if(X[i] == Y[i]) {
            w[X[i]] = max(A[X[i]], B[X[i]]);
        }
    }

    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        ans += w[i];
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
