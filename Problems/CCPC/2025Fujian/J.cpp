#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    i64 n;
    cin >> n;

    vector<i64> ans;
    for(int i = 0; i < 60; i++) {
        if((n & (n - 1)) == 0 && __lg(n) % 2 == 0) break;
        if(n >> i & 1) {
            ans.push_back(1LL << i);
            n += 1LL << i;
        }
    }

    cout << ans.size() << "\n";
    for(auto x : ans) {
        cout << x << " \n"[x == ans.back()];
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