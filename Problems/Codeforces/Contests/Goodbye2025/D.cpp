#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> p(n + 1);
    iota(p.begin(), p.end(), 0);
    sort(p.begin() + 1, p.end(),
        [&](auto x, auto y) {
            return a[x] < a[y];
        });
    if(m == 0) {
        ll sum = 0;
        for(int i = 1; i <= n - 1; i++) {
            sum += a[p[i]];
        }
        if(a[p[n]] > sum) {
            cout << -1 << "\n";
            return;
        }
        ll cur = 0;
        int l = -1;
        for(int i = n - 1; i >= 1; i--) {
            cur += a[p[i]];
            if(cur >= a[p[n]]) {
                l = i;
                break;
            }
        }
        vector<PII> ans;
        for(int i = 1; i < l; i++) {
            ans.push_back({p[i], p[i + 1]});
        }
        for(int i = l; i < n; i++) {
            ans.push_back({p[i], p[n]});
        }
        cout << ans.size() << "\n";
        for(auto [x, y] : ans) {
            cout << x << " " << y << "\n";
        }
        return;
    }
    if(m > n / 2) {
        cout << -1 << "\n";
        return;
    } 
    vector<PII> ans;
    for(int i = 1; i <= n - 2 * m; i++) {
        ans.push_back({p[i], p[i + 1]});
    }
    for(int i = n - m + 1; i <= n; i++) {
        ans.push_back({p[i], p[i - m]});
    }
    cout << ans.size() << "\n";
    for(auto [x, y] : ans) {
        cout << x << " " << y << "\n";
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
