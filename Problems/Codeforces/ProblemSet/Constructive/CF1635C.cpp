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
    if(is_sorted(a.begin() + 1, a.end())) {
        cout << 0 << "\n";
        return;
    }
    if(a[n - 1] > a[n] || a[n] < 0) {
        cout << -1 << "\n";
        return;
    }
    cout << n - 2 << "\n";
    for(int i = 1; i <= n - 2; i++) {
        cout << i << " " << n - 1 << " " << n << "\n";
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
