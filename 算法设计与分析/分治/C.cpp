#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    auto dfs = [&](auto&& self, int x) -> void {
        vector<int> b;
        for(int i = 29; i >= 0; i--) {
            if(x >> i & 1) {
                b.push_back(i);
            }
        }
        for(int i = 0; i < b.size(); i++) {
            if(b[i] == 0) {
                cout << "2(0)";
            } else if(b[i] == 1) {
                cout << 2;
            } else {
                cout << "2(";
                self(self, b[i]);
                cout << ")";
            }
            if(i + 1 < b.size()) {
                cout << "+";
            }
        }
    };
    dfs(dfs, n);
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