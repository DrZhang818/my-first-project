#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    auto ck = [&](db x) {
        vector<db> w(n + 1);
        for(int i = 1; i <= n; i++) {
            w[i] = a[i] - x * b[i];
        }
        sort(w.begin() + 1, w.end(), greater());
        db sum = 0;
        for(int i = 1; i <= k; i++) {
            sum += w[i];
        }
        return sum >= 0;
    };

    db lo = 0, hi = inf;
    for(int t = 0; t < 60; t++) {
        db mid = lo + (hi - lo) / 2;
        if(ck(mid)) {
            lo = mid;
        } else {
            hi = mid;
        }
    }

    cout << fixed << setprecision(2) << lo << "\n";
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
