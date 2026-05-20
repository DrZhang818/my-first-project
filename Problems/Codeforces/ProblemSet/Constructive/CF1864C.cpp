#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

inline int lowbit(int x) { return x & -x; }

void solve() {
    int x;
    cin >> x;
    vector<int> ans;
    ans.push_back(x);
    while(x != lowbit(x)) {
        x -= lowbit(x);
        ans.push_back(x);
    }
    while(x > 1) {
        x -= lowbit(x) >> 1;
        ans.push_back(x);
    }
    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " \n"[i == ans.size() - 1];
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
