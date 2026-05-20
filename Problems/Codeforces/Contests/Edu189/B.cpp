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
    int cnt = 0;
    for(int i = 1; i < n; i++) {
        if(s[i] == s[i - 1]) {
            cnt++;
        }
    }
    if(cnt <= 2) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}