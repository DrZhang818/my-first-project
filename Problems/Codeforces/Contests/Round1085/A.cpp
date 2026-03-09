#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    s = "#" + s;

    int mn = 0, mx = 0;
    for(int i = 1; i <= n; i++) {
        if(s[i] == '1') {
            mx++;
            if(i >= 3 && s[i - 1] == '0' && s[i - 2] == '1') {
                mx++;
                s[i - 1] = '1';
            }
        } 
    }

    mn = mx;
    for(int l = 1, r = 1; l <= n; l = r) {
        while(r <= n && s[r] == s[l]) {
            r++;
        }
        if(s[l] == '1') {
            mn -= (r - l - 1) / 2;
        }
    }

    cout << mn << " " << mx << "\n";
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
