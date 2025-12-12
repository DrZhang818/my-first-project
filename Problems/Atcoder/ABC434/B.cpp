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
    vector<int> sum(m + 1);
    vector<int> cnt(m + 1);
    for(int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        sum[a] += b;
        cnt[a] += 1;
    }
    for(int i = 1; i <= m; i++) {
        db ans = db(sum[i]) / cnt[i];
        cout << fixed << setprecision(12) << ans << "\n";
    }
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
