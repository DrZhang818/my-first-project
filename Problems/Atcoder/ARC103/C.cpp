#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    s = "#" + s;
    if(s[1] == '0' || s[n] == '1') {
        cout << -1 << "\n";
        return;
    }
    for(int i = 1; i < n; i++) {
        if(s[i] != s[n - i]) {
            cout << -1 << "\n";
            return;
        }
    }
    int pre = 1;
    for(int i = 2; i <= n; i++) {
        cout << pre << " " << i << "\n";
        if(s[i - 1] == '1') pre = i;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
