#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    string mn = s, mx = s;
    s += s;

    for(int i = 1; i < n; i++) {
        string cur = s.substr(i, n);
        mn = min(mn, cur);
        mx = max(mx, cur);
    }

    cout << mn << "\n" << mx << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}