#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    auto it = max_element(a.begin(), a.end());
    swap(*it, a[1]);

    sort(a.begin() + 2, a.end());
    unique(a.begin() + 2, a.end());

    i64 ans = 1LL * a[1] * n;
    int mex = 0;
    vector<int> vis(n + 1);
    for(int i = 1; i <= n; i++) {
        if(a[i] <= n) vis[a[i]] = 1;
        while(vis[mex]) mex++;
        ans += mex;
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}