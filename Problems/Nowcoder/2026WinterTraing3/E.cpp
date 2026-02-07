#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

struct Edge {
    int u, v, w;
};

void solve() {  
    int n, m, k;
    cin >> n >> m >> k;

    ll cur = 1LL * n * (n - 1) / 2;

    if(cur > k) {
        cout << "NO\n";
        return;
    }

    vector<int> w(n);
    iota(w.begin(), w.end(), 0);

    for(int i = n - 1; i >= 1; i--) {
        ll d = min((ll)m - n + 1, 1LL * i * (i - 1) / 2 + 1 - i);
        w[i] += min(k - cur, d);
        cur += min(k - cur, d);
    }

    if(cur < k) {
        cout << "NO\n";
        return;
    }

    vector<Edge> e;
    vector<PII> can;

    int idx = 1;

    for(int i = 1; i <= m; i++) {
        if(idx < n && w[idx] == i) {
            idx++;
            e.emplace_back(1, idx, i);
            if(can.size() < m) {
                for(int j = 2; j < idx; j++) {
                    can.push_back({j, idx});
                }
            }
        } else {
            auto [u, v] = can.back();
            can.pop_back();
            e.emplace_back(u, v, i);
        }
    }

    cout << "YES\n";
    for(auto [u, v, w] : e) {
        cout << u << " " << v << " " << w << "\n"; 
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
