#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    string s, t;
    cin >> s >> t;
    
    int ans = 0;

    int n = s.size(), m = t.size();
    for(int i = 0, j = 0; i < n || j < m; ) {
        if(i < n && j < m && s[i] == t[j]) {
            i++;
            j++;
        } else if(i < n && s[i] == 'A') {
            ans++;
            i++;
        } else if(j < m && t[j] == 'A') {
            ans++;
            j++;
        } else {
            cout << -1 << "\n";
            return;
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
