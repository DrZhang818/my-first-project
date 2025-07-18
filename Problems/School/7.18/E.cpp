#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int u, v, w;
};
void solve() {
    int n;
    cin >> n;
    int sz = __lg(n) + 1;
    int rem = n - (1 << sz - 1);
    vector<info> ans;
    ans.reserve(sz << 1);
    for(int i = 2; i <= sz; i++) {
        ans.emplace_back(i - 1, i, 1 << i - 2);
        ans.emplace_back(i - 1, i, 0);
    }
    int cur = 1 << sz - 1;
    while(rem) {
        int t = __lg(rem);
        ans.emplace_back(t + 1, sz, cur);        
        rem -= (1 << t);
        cur += (1 << t);
    }
    cout << sz << " " << ans.size() << "\n";
    for(auto [u, v, w] : ans) {
        cout << u << " " << v << " " << w << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
