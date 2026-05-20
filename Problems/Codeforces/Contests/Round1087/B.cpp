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

    vector<int> ans(n + 1);
    vector<int> val;

    for(int i = n; i >= 1; i--) {
        int pos = upper_bound(val.begin(), val.end(), a[i]) - val.begin();
        int x = val.size() - pos;
        pos = lower_bound(val.begin(), val.end(), a[i]) - val.begin() - 1;
        int y = pos + 1;
        ans[i] = max(x, y);
        val.push_back(a[i]);
        sort(val.begin(), val.end());
    }
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
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
