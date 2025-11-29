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
    if(s.size() == 1) {
        cout << 1 << "\n";
        return;
    }
    int n = s.size();
    s = "#" + s;
    for(int i = 2; i <= n; i++) {
        if((s[i - 1] == '>' || s[i - 1] == '*') && (s[i] == '<' || s[i] == '*')) {
            cout << -1 << "\n";
            return;
        }
    }
    int ans = 1;
    for(int i = 1, cur = 0; i <= n; i++) {
        if(s[i] == '>') {
            break;
        }
        cur++;
        ans = max(ans, cur);
    }
    for(int i = n, cur = 0; i >= 1; i--) {
        if(s[i] == '<') {
            break;
        }
        cur++;
        ans = max(ans, cur);
    }
    cout << ans << "\n";
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
