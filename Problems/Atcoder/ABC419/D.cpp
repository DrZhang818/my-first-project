#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m;
    cin >> n >> m;
    string s, t;
    cin >> s >> t;
    s = "#" + s;
    t = "#" + t;
    vector<int> d(n + 2);
    for(int i = 1; i <= m; i++) {
        int l, r;
        cin >> l >> r;
        d[l] ^= 1;
        d[r + 1] ^= 1;
    }
    for(int i = 1; i <= n; i++) {
        d[i] ^= d[i - 1];
    }
    for(int i = 1; i <= n; i++) {
        if(d[i]) {
            cout << t[i];
        } else {
            cout << s[i];
        }
    }
    cout << "\n";
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
