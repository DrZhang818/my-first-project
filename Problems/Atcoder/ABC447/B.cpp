#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    string s;
    cin >> s;
    array<int, 26> cnt {};
    int mx = 0;
    for(char c : s) {
        mx = max(mx, ++cnt[c - 'a']);
    }

    string ans;
    for(char c : s) {
        if(cnt[c - 'a'] != mx) {
            ans += c;
        }
    }
    cout << ans << "\n";
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
