#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

inline int lowbit(int o) { return o & -o; }
struct FenwickTree {
    int n;
    vector<int> tr;
    FenwickTree(int n_) : n(n_), tr(n_) {}
    void add(int o, int x) {
        for(; o < n; o += lowbit(o)) {
            tr[o] += x;
        }
    }
    int query(int o) {
        int res = 0;
        for(; o > 0; o -= lowbit(o)) {
            res += tr[o];
        }
        return res;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<pair<int,int>> a(n + 1);
    for(int i = 1; i <= n; i++) {
        auto& [x, id] = a[i];
        cin >> x;
        id = i;
    }
    sort(a.begin() + 1, a.end());

    FenwickTree fen(n + 1);

    vector<int> ans(n + 1);
    i64 sum = 0;
    for(int i = 1; i <= n; i++) {
        auto [x, id] = a[i];
        sum += x;
        i64 cur = 1LL * x * i - sum;
        cur += fen.query(id);
        fen.add(id, 1);
        if(cur > m - 2) {
            ans[id] = -1;
        } else {
            ans[id] = cur;
        }
    }

    for(int i = 1; i <= n; i++) {
        cout << ans[i] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
