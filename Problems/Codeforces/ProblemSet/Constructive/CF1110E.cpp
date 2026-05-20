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
    if(a[1] != b[1] || a[n] != b[n]) {
        cout << "No\n";
        return;
    }
    vector<int> d1, d2;
    for(int i = 2; i <= n; i++) {
        d1.push_back(a[i] - a[i - 1]);
        d2.push_back(b[i] - b[i - 1]);
    }
    sort(d1.begin(), d1.end());
    sort(d2.begin(), d2.end());
    if(d1 == d2) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
