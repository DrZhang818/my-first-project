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
    for(int i = 1; i < s.size(); i++) {
        if(s[i - 1] == '#' && s[i] != '#') {
            s[i] = 'o';
        }
    }
    if(s[0] != '#') {
        s[0] = 'o';
    }
    cout << s << "\n";
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
