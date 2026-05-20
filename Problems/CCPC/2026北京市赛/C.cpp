#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

pair<int,int> split(int n) {
    int p = 1 << __lg(n);
    if(n == p) {
        p >>= 1;
    }
    return {p, n - p};
}

void solve() {
    int n;
    cin >> n;

    if(n == 1) {
        cout << 1 << "\n";
        return;
    }

    auto ends = [&](this auto&& self, int n) -> vector<int> {
        if(n == 1) {
            return {0};
        }

        auto [p, q] = split(n);
        int h = p >> 1;

        auto e = self(q);

        vector<int> res;
        for(int x : e) {
            res.push_back(x ^ h);
            res.push_back(p + x);
        }
        return res;
    };

    auto en = ends(n);
    int st = *min_element(en.begin(), en.end());

    vector<int> ans;

    int cur = st;
    ans.push_back(cur);

    auto add = [&](int x) {
        cur ^= x;
        ans.push_back(cur);
    };

    auto gray = [&](int p) {
        for(int i = 1; i < p; i++) {
            add(i & -i);
        }
    };

    auto gen = [&](this auto&& self, int n, int st) -> void {
        if(n == 1) return;

        auto [p, q] = split(n);
        int h = p >> 1;

        if(st < p) {
            gray(p);
            add(p);
            self(q, st ^ h);
        } else {
            self(q, st - p);
            add(p);
            gray(p);
        }
    };

    gen(n, st);

    for(int i = 0; i < n; i++) {
        cout << ans[i] << " \n"[i == n - 1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}