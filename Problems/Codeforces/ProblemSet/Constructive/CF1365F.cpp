#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    if(n & 1) {
        if(a[n / 2 + 1] != b[n / 2 + 1]) {
            cout << "No\n";
            return;
        }
    }
    vector<pair<int,int>> x, y;
    for(int i = 1; i <= n / 2; i++) {
        if(a[i] < a[n - i + 1]) {
            swap(a[i], a[n - i + 1]);
        }
        x.emplace_back(a[i], a[n - i + 1]);
    }
    for(int i = 1; i <= n / 2; i++) {
        if(b[i] < b[n - i + 1]) {
            swap(b[i], b[n - i + 1]);
        }
        y.emplace_back(b[i], b[n - i + 1]);
    }
    ranges::sort(x);
    ranges::sort(y);
    if(x == y) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
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
