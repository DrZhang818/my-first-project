#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;
constexpr int N = 1E6;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<pair<int,int>> ans;
    for(int i = 1; i <= n; i++) {
        if(a[i] == i) continue;
        int l = i, r = -1;
        for(int j = n; j > i; j--) {
            if(a[j] < a[i]) {
                r = j;
                break;
            }
        }
        ans.emplace_back(l, r);
        sort(a.begin() + l, a.begin() + r + 1);
    }
    cout << ans.size() << "\n";
    for(auto [l, r] : ans) {
        cout << l << " " << r << "\n";
    }
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