#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

vector<int> query(int k) {
    cout << "? " << k << endl;
    int q;
    cin >> q;
    vector<int> vec(q + 1);
    for(int i = 1; i <= q; i++) {
        cin >> vec[i];
    }
    return vec;
}

void solve() {  
    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);

    vector<ll> dp(n + 1, -1);

    auto work = [&](this auto&& self, int u) -> ll {
        if(dp[u] != -1) {
            return dp[u];
        }
        dp[u] = 1;
        for(int v : adj[u]) {
            dp[u] += self(v);;
        }
        return dp[u];
    };

    vector<PII> e;
    int cur = 1;
    vector<int> b {0, 1};
    int id = 2;
    while(cur <= n) {
        fill(dp.begin(), dp.end(), -1);
        for(int u = 1; u <= n; u++) {
            work(u);
        }

        auto a = query(id);
        if(a.size() == 1) {
            break;
        }

        if(a[1] != cur) {
            cur = a[1];
        } else {
            int idx = -1;
            for(int i = 1; i < a.size() && i < b.size(); i++) {
                if(a[i] == b[i]) {
                    idx = i;
                } else {
                    break;
                }
            }

            adj[a[idx]].push_back(a.back());
            e.emplace_back(a[idx], a.back());
        }

        id += dp[a.back()];

        b = move(a);
    }   

    cout << "! " << e.size() << endl;
    for(auto [u, v] : e) {
        cout << u << " " << v << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
