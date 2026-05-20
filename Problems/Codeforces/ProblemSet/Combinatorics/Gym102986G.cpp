#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n, w;
    cin >> n >> w;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());

    i64 sum = 0;
    for(int i = 1; i <= n; i++) {
        sum += 1LL * a[i] * (2 * i - n - 1);
    }
    sum *= 2;

    db ans = db(sum) / n + w;

    cout << fixed << setprecision(12) << ans << "\n";
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
