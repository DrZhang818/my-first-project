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
    int c1 = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        if(a[i] & 1) {
            c1++;
        }
    }
    if(c1 != 0 && c1 != n) {
        cout << -1 << "\n";
        return;
    }

    vector<int> ans;

    for(int i = 29; i >= 0; i--) {
        ans.push_back(1 << i);
    }

    if(c1 == 0) {
        ans.push_back(1);
    }

    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " \n"[i == ans.size() - 1];
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
