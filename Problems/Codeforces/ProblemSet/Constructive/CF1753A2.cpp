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
    int c1 = 0, cn1 = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        c1 += a[i] == 1;
        cn1 += a[i] == -1;
    }

    if((c1 + cn1) & 1) {
        cout << -1 << "\n";
        return;
    }

    int sum = c1 - cn1;

    vector<pair<int,int>> ans;
    for(int i = 1; i <= n; i++) {
        if(a[i] == 0) {
            ans.emplace_back(i, i);
        } else if(a[i] == 1) {
            if(sum > 0 && !ans.empty() && ans.back().first == ans.back().second) {
                ans.pop_back();
                ans.emplace_back(i - 1, i);
                sum -= 2;
            } else {
                ans.emplace_back(i, i);
            }
        } else {
            if(sum < 0 && !ans.empty() && ans.back().first == ans.back().second) {
                ans.pop_back();
                ans.emplace_back(i - 1, i);
                sum += 2;
            } else {
                ans.emplace_back(i, i);
            }
        }
    }

    cout << ans.size() << "\n";
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
