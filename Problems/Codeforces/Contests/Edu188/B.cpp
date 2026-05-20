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
    vector<int> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        pre[i] = max(pre[i - 1], a[i]);
    }
    int cur = pre[n];
    int ans = 0;

    for(int i = n; i >= 1; i--) {
        if(a[i] == cur) {
            ans++;
            cur = pre[i - 1];
        }
    }

    cout << ans << "\n";
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
