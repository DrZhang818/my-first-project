#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

i64 query(i64 n, i64 m) {
    cout << "? " << n << " " << m << endl;
    char c;
    i64 res;
    cin >> c >> res;
    return res;
}

void solve() {
    int n;
    cin >> n;
    vector<i64> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<i64> val(61);
    for(int i = 0; i < 61; i++) {
        val[i] = query(1LL << i, 1LL << i) >> 1;
    }

    auto dfs = [&](this auto&& self, i64 x) -> i64 {
        i64 y = 1LL << __lg(x) + 1;
        if(x == y - x) {
            return val[__lg(x)];
        }
        auto s = query(x, y - x);
        return s - self(y - x);
    };

    for(int i = 1; i <= n; i++) {
        auto ans = dfs(a[i]);
        cout << "! " << ans << endl;
        char c;
        cin >> c;
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
