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
    vector<ll> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    auto na = a;
    for(int i = 0; i < na.size(); i++) {
        ll t = na[i];
        na[i] = t % 10;
        if(t >= 10 && i + 1 >= na.size()) {
            na.push_back(0);
        }
        na[i + 1] += t / 10;
    }

    int sz = na.size();
    a.resize(sz);
    ll x = 0;
    vector<int> ans(sz);
    for(int i = sz - 1; i >= 0; i--) {
        ll cans = na[i] / m;
        ans[i] = cans;

        x = x * 10 + m * cans;
        ll cur = a[i];
        ll rem = na[i] % m;
        if(cur <= x) {
            x -= cur;
        } else {
            rem -= cur - x;
            x = 0;
        }

        if(i > 0) na[i - 1] += rem * 10;
    }
    while(ans.size() > 1 && ans.back() == 0) ans.pop_back();
    reverse(ans.begin(), ans.end());
    for(int x : ans) {
        cout << x;
    }
    cout << "\n";
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
