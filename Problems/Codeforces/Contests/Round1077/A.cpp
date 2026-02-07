#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 2000000000;

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    auto b = a;
    sort(b.begin() + 1, b.end());
    if(a == b) {
        cout << -1 << "\n";
        return;
    }
    vector<int> val;
    for(int i = 1; i <= n; i++) {
        if(a[i] != b[i]) {
            val.push_back(a[i]);
        }
    }
    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());
    int lo = b[1], hi = b[n];
    int ans = 0;
    for(int i = 0; i < val.size(); i++) {
        int x = inf, y = inf;
        x = val[i] - lo;
        int cur = x;
        if(i > 0) {
            y = hi - val[i - 1];
            cur = min(cur, y);
        }
        ans = max(ans, cur);
    }
    int cur = hi - val.back();
    ans = max(ans, cur);
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
