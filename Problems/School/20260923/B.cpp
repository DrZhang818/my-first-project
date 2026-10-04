#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<i64> L(n + 1), R(n + 1);
    for(int i = 2; i <= n; i++) {
        L[i] = L[i - 1] + (i == n || a[i] - a[i - 1] < a[i + 1] - a[i] ? 1 : a[i] - a[i - 1]);        
    }
    for(int i = n - 1; i >= 1; i--) {
        R[i] = R[i + 1] + (i == 1 || a[i + 1] - a[i] < a[i] - a[i - 1] ? 1 : a[i + 1] - a[i]);
    }

    int q;
    cin >> q;
    while(q--) {
        int x, y;
        cin >> x >> y;

        if(x < y) {
            cout << R[x] - R[y] << "\n";
        } else {
            cout << L[x] - L[y] << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}