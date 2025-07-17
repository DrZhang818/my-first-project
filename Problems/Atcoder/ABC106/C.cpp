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
    ll k;
    cin >> k;
    int cnt = 0;
    for(char c : s) {
        if(c == '1') {
            cnt++;
        } else {
            break;
        }
    }
    if(k <= cnt) {
        cout << 1 << "\n";
    } else {
        cout << s[cnt] << "\n";
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
