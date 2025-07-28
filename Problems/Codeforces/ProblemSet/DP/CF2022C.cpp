#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int get(char a, char b, char c) {
    return (a == 'A') + (b == 'A') + (c == 'A') >= 2;
}
void solve() {
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    s = "#" + s;
    t = "#" + t;

    vector<int> f(n + 1), g(n + 1), h(n + 1);    
    for(int i = 0; i < n; i++) {
        if(i % 3 == 0) {
            f[i + 3] = max(f[i + 3], f[i] + get(s[i + 1], s[i + 2], s[i + 3]) + get(t[i + 1], t[i + 2], t[i + 3]));
            g[i + 2] = max(g[i + 2], f[i] + get(s[i + 1], s[i + 2], t[i + 1]));
            h[i + 2] = max(h[i + 2], f[i] + get(t[i + 1], t[i + 2], s[i + 1]));            
        }
        if(i % 3 == 2) {
            if(i + 3 <= n) {
                g[i + 3] = max(g[i + 3], g[i] + get(s[i + 1], s[i + 2], s[i + 3]) + get(t[i], t[i + 1], t[i + 2]));
                h[i + 3] = max(h[i + 3], h[i] + get(t[i + 1], t[i + 2], t[i + 3]) + get(s[i], s[i + 1], s[i + 2]));
            }
            f[i + 1] = max(f[i + 1], g[i] + get(s[i + 1], t[i], t[i + 1]));
            f[i + 1] = max(f[i + 1], h[i] + get(t[i + 1], s[i], s[i + 1]));
        }
    }
    cout << f[n] << "\n";
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
