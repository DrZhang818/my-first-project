#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, x1, y1;
    cin >> n >> x1 >> y1;
    db ans = 0;
    for(int i = 1; i <= n; i++) {
        int x2, y2;
        cin >> x2 >> y2;
        ans = max(ans, db(x1 * y2 - x2 * y1) / (x1 - x2));
    }
    cout << fixed << setprecision(12) << ans << "\n";
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
