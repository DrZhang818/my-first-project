#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr int V = 1000000;
constexpr int m = 63;

void solve() {
    int n;
    cin >> n;
    vector<PII> ans;
    int len = 1;
    for(int t = 0; t < 3; t++) {
        for(int r = 1; r < m; r++) {
            for(int i = n / len; i >= 1; i--) {
                if(i % m == r) {
                    ans.emplace_back(i * len, len);
                }
            }
        }
        len *= m;
    }
    cout << ans.size() << "\n";
    for(auto [y, l] : ans) {
        cout << y << " " << l << "\n";
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
