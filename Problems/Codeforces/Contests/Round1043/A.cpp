#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    string s, t, c;
    cin >> s;
    int m;
    cin >> m >> t >> c;
    string r1, r2;
    for(int i = 0; i < m; i++) {
        if(c[i] == 'D') {
            r2 += t[i];
        } else {
            r1 += t[i];
        }
    }
    reverse(r1.begin(), r1.end());
    s = r1 + s;
    s += r2;
    cout << s << "\n";
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
