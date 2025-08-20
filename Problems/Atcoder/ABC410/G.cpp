#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int x, y;
};
void chmax(int &x, int y) {
    if(x < y) {
        x = y;
    }
}
inline int lowbit(int o) { return o & -o; }
class BIT {
private:
    vector<int> tr;
    int n;
public:
    BIT(int n) : tr(n + 1), n(n) {}
    void update(int x, int d) {
        for(int i = x; i <= n; i += lowbit(i)) {
            chmax(tr[i], d);
        }
    }
    int query(int x) {
        int res = 0;
        for(int i = x; i > 0; i -= lowbit(i)) {
            chmax(res, tr[i]);
        }
        return res;
    }
};
void solve() {
    int n;
    cin >> n;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y;
        if(a[i].x > a[i].y) {
            swap(a[i].x, a[i].y);
        }
    }
    int ans = 0;
    vector<int> dp(n + 1);
    sort(a.begin() + 1, a.end(), 
        [&](auto u, auto v) {
            return u.x < v.x;
        });
    BIT tr1(2 * n + 1);
    for(int i = n; i >= 1; i--) {
        auto [x, y] = a[i];
        int cur = tr1.query(y) + 1;
        dp[i] = cur;
        tr1.update(y, cur);
    }
    BIT tr2(2 * n + 1);
    for(int i = 1; i <= n; i++) {
        auto [x, y] = a[i];
        int cur = tr2.query(x);
        ans = max(ans, cur + dp[i]);
        tr2.update(y, dp[i]);
    }
    BIT tr3(2 * n + 1);
    for(int i = n; i >= 1; i--) {
        auto [x, y] = a[i];
        int cur = tr3.query(2 * n - y + 1);
        ans = max(ans, cur + dp[i]);
        tr3.update(2 * n - x + 1, dp[i]);
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
