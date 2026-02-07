#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

struct Node {
    array<int,2> to {-1, -1};
    int cnt = 0;
};

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<Node> tr;
    tr.push_back(Node());

    auto add = [&]() {
        tr.push_back(Node());
        return tr.size() - 1;
    };

    for(int i = 0; i < n; i++) {
        int o = 0;
        for(int j = 29; j >= 0; j--) {
            int s = a[i] >> j & 1;
            if(tr[o].to[s] == -1) {
                tr[o].to[s] = add();
            }
            o = tr[o].to[s];
            tr[o].cnt++;
        }
    }

    auto calc = [&](vector<int>& a, int u, int s) -> int {
        if(s == 0) return 0;
        int res = numeric_limits<int>::max();
        for(int v : a) {
            int o = u;
            int cur = 0;
            for(int i = s - 1; i >= 0; i--) {
                int f = v >> i & 1;
                if(tr[o].to[f] == -1) {
                    cur += 1 << i;
                    o = tr[o].to[f ^ 1];
                } else {
                    o = tr[o].to[f];
                }
            }
            res = min(res, cur);
        }

        return res;
    };

    auto dfs = [&](this auto&& self, vector<int>& a, int o, int i) -> ll {
        if(a.empty() || i == 0) {
            return 0;
        }

        int u = tr[o].to[0];
        int v = tr[o].to[1];
        if(u == -1) {
            return self(a, v, i - 1);
        }
        if(v == -1) {
            return self(a, u, i - 1);
        }

        vector<int> s0, s1;
        for(int v : a) {
            if(v >> (i - 1) & 1) {
                s1.push_back(v);
            } else {
                s0.push_back(v);
            }
        }

        ll res = self(s0, u, i - 1) + self(s1, v, i - 1) + (1 << i - 1);
        if(s0.size() < s1.size()) {
            res += calc(s0, v, i - 1);
        } else {
            res += calc(s1, u, i - 1);
        }
        return res;
    };

    ll ans = dfs(a, 0, 30);

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
