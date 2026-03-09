#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;

    vector<int> a(n);
    vector<int> ans(n);

    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int pre = 0;
    for(int i = 0; i < n; i++) {
        int x = a[i];
        if(x > 0 && pre - x >= 0) {
            cout << -1 << "\n";
            return;
        }
        pre += x;
        ans[i] = pre;
    }
    for(int i = 0; i < n; i++) {
        cout << ans[i] << " \n"[i == n - 1];
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
