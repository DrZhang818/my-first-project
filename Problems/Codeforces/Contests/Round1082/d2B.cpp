#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    string s;
    cin >> s;
    if(n & 1) {
        if(s[0] == 'b') {
            cout << "NO\n";
            return;
        }
        s = s.substr(1);
    }

    n = s.size();
    for(int i = 0; i < n; i += 2) {
        if(s[i] == '?' || s[i + 1] == '?') {
            continue;
        }
        if(s[i] == s[i + 1]) {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
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
