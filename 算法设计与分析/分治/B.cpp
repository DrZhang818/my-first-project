#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> L(n + 1), R(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        if(L[u] == 0) {
            L[u] = v;
        } else {
            R[u] = v;
        }
    }

    auto dfs = [&](auto&& self, int u) -> void {
        for(int i : {L[u], R[u]}) {
            if(i == 0) continue;
            self(self, i);
        }
        cout << u << " ";
    };
    dfs(dfs, 1);

    cout << "\n";
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