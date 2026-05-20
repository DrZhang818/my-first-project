#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<int> vis(n);
    vis[0] = 1;
    int x = 0;
    for(int i = 0; i < n; i++) {
        if(s[x] == 'L') {
            x--;
        } else {
            x++;
        }
        vis[x] = 1;
    }
    int ans = accumulate(vis.begin(), vis.end(), 0);
    cout << ans << "\n";
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
