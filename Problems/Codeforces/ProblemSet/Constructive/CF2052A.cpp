#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<int> p(n + 1);
    vector<int> idx(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        p[i] = i;
        idx[i] = i;
    }

    vector<pair<int,int>> ans {};

    for(int i = n; i >= 1; i--) {
        int j = idx[a[i]];
        for(int k = j - 1; k >= 1; k--) {
            ans.emplace_back(a[i], p[k]);
        }
        for(int k = 1; k <= j - 1; k++) {
            ans.emplace_back(p[k], a[i]);
        }
        for(int k = j + 1; k <= i; k++) {
            ans.emplace_back(p[k], a[i]);
            tie(idx[p[k]], p[k - 1]) = tuple(k - 1, p[k]);
        }
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
    while(t--) {
        solve();
    }
    return 0;
}
