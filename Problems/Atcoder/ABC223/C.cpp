#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    vector<db> w(n + 1);
    int sum = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
        w[i] = db(a[i]) / b[i];
        sum += a[i];
    }

    auto ck = [&](db x) -> bool {
        db L = 0, R = sum;
        db tmp = x;
        for(int i = 1; i <= n; i++) {
            db t = min(x, w[i]);
            L += b[i] * t;
            x -= t;
        }
        x = tmp;
        for(int i = n; i >= 1; i--) {
            db t = min(x, w[i]);
            R -= b[i] * t;
            x -= t;
        }
        return L >= R;
    };

    db l = 0, r = inf;
    for(int t = 0; t < 100; t++) {
        db mid = l + (r - l) / 2;
        if(ck(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }

    db L = 0;
    for(int i = 1; i <= n; i++) {
        db t = min(r, w[i]);
        L += b[i] * t;
        r -= t;
    }
    cout << fixed << setprecision(12) << L << "\n";

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}