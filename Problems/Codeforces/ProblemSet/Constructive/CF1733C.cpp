#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    if(n == 1) {
        cout << 0 << "\n";
        return;
    }
    vector<pair<int,int>> ans;
    ans.emplace_back(1, n);
    if(a[1] + a[n] & 1) {
        a[n] = a[1];
    } else {
        a[1] = a[n];
    }
    for(int i = 2; i < n; i++) {
        if(a[1] + a[i] & 1) {
            ans.emplace_back(1, i);
        } else {
            ans.emplace_back(i, n);
        }
    }
    int m = ans.size();
    cout << m << "\n";
    for(auto [l, r] : ans) {
        cout << l << " " << r << "\n";
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
