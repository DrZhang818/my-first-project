#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;
constexpr int N = 500000;

vector<int> minp, primes;
auto init = []() {
    minp.resize(N + 1);
    for(int i = 2; i <= N; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
        }
        for(auto p : primes) {
            if(i * p > N) break;
            minp[i * p] = p;
            if(minp[i] == p) break;
        }
    }
    return 1;
}();

template<int K>
struct TopK {
    struct Node {
        int val = 0;
        int key = -1;
    };

    array<Node, K> a;

    void norm() {
        sort(a.begin(), a.end(), [&](const Node &x, const Node &y) {
            return x.val > y.val;
        });
    }

    void add(int key, int val) {
        for (auto &x : a) {
            if (x.key == key) {
                x.val = max(x.val, val);
                norm();
                return;
            }
        }

        if (val > a[K - 1].val) {
            a[K - 1] = {val, key};
            norm();
        }
    }

    int get(int ban) const {
        for (auto x : a) {
            if (x.key != ban) {
                return x.val;
            }
        }
        return 0;
    }
};

void solve() {
    int n;
    cin >> n;

    vector<int> w(n + 1), c(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> c[i];
    }

    auto get = [&](int x) {
        vector<int> res;
        while(x > 1) {
            int p = minp[x];
            res.push_back(p);
            while(minp[x] == p) x /= p;
        }
        return res;
    };

    vector<TopK<2>> dp(N + 1);

    int ans = 1;
    
    for(int i = 1; i <= n; i++) {
        auto ps = get(w[i]);

        int cur = 1;
        for(auto p : ps) {
            cur = max(cur, dp[p].get(c[i]) + 1);
        }

        ans = max(ans, cur);

        for(auto p : ps) {
            dp[p].add(c[i], cur);
        }
    }
    cout << ans << "\n";
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