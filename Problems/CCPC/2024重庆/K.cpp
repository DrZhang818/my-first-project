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
    string s, t;
    cin >> s >> t;
    for(int i = 0; i < n; i++) {
        if(s[i] != '1' && t[i] != '1') {
            cout << 0 << "\n";
            return;
        }
    }
    cout << 1 << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}