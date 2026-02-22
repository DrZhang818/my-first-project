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

    int c0 = count(s.begin(), s.end(), '0');
    int c1 = n - c0;
    if(c0 == n) {
        cout << 0 << "\n";
        return;
    }

    if(~c1 & 1) {
        cout << c1 << "\n";
        for(int i = 0; i < n; i++) {
            if(s[i] == '1') {
                cout << i + 1 << " ";
            }
        }
    } else if(c0 & 1) {
        cout << c0 << "\n";
        for(int i = 0; i < n; i++) {
            if(s[i] == '0') {
                cout << i + 1 << " ";
            }
        }
    } else {
        cout << -1;
    }
    cout << "\n";
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
