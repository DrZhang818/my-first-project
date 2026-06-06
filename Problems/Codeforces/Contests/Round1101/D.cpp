#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for(int i = 1; i <= n; i++) {
        if(a[i] >= i) {
            cout << "NO\n";
            return;
        }
    }

    vector<tuple<int,int,int>> ans;
    auto dfs = [&](this auto&& self, int id, int from, int to, int help) -> void {
        if(id == 0) return;
        int h = id - a[id] - 1;
        if(h == 0) {
            ans.emplace_back(id, from, to);
            self(id - 1, from, to, help);
        } else {
            self(h, from, help, to);
            ans.emplace_back(id, from, to);
            if(h != id - 1) {
                self(h, help, from, to);
                self(id - 1, from, to, help);
            } else {
                self(h, help, to, from);
            }
        }
    };
    dfs(n, 1, 3, 2);

    assert(ans.size() <= (1 << n));
    cout << "YES\n";
    cout << ans.size() << "\n";
    for(auto [id, from, to] : ans) {
        cout << id << " " << from << " " << to << "\n";
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