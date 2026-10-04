#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n, k;
    cin >> n >> k;
    int m = n + 2 * k;
    vector<int> vis(m + 1);

    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if(x <= m) {
            vis[x] = true;
        }
    }

    array<int, 2> cnt {};
    int tot = 0;
    for(int i = 0; tot < 2 * k + 1; i++) {
        if(!vis[i]) {
            cnt[i & 1]++;
            tot++;
        }
    }

    cout << (cnt[0] > k ? "Alice" : "Bob") << "\n";
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
