#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, x;
    cin >> n >> x;
    string s;
    cin >> s;
    int cnt = count(s.begin(), s.end(), '#');
    if(cnt == 0 || x == 1 || x == n) {
        cout << 1 << "\n";
        return;
    }
    int c0 = 0, c1 = 0;
    for(int i = x - 2, tag = 0; i >= 0; i--) {
        if(s[i] == '#') tag = 1;
        if(tag) c0++;
    }
    for(int i = x, tag = 0; i < n; i++) {
        if(s[i] == '#') tag = 1;
        if(tag) c1++;
    }
    cout << 1 + max(min(x - 1, c1), min(n - x, c0)) << "\n";
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
