#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    auto dfs = [&](this auto &&self, int x, int y) -> int {
        if(x > y) swap(x, y);
        if(x == 0) return inf;
        if(x == 1) return y - 1;
        return y / x + self(x, y % x);
    };
    int ans = inf;
    for(int i = 1; i <= n; i++) {
        ans = min(ans, dfs(n, i));
    }
    cout << ans << "\n";
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
