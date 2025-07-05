#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) cin >> x;
    
    vector<int> max_left(n, INT_MAX);
    for (int i = 1; i < n; ++i) {
        max_left[i] = min(max_left[i-1], a[i-1] + (i-1));
    }
    
    vector<int> min_right(n, INT_MIN);
    for (int i = n-2; i >= 0; --i) {
        min_right[i] = max(min_right[i+1], (i+1) - a[i+1] + 1);
    }
    
    for (int i = 0; i < n; ++i) {
        bool left_ok = (i == 0) || (max_left[i] >= i + 1);
        bool right_ok = (i == n-1) || (min_right[i] <= i);
        if (left_ok && right_ok && a[i] >= 1) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}