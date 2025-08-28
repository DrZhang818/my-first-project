#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void chmax(int &x, int y) {
    if(x < y) {
        x = y;
    }
}
void solve() {
    string s;
    cin >> s;
    int n = s.size();
    s = "#" + s;
    vector<array<array<int,2>,3>> f(n * 3 + 1, {-inf,-inf,-inf,-inf,-inf,-inf});
    vector<int> g(n + 1);
    vector<int> pre(n + 1);
    pre[0] = n;
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + (s[i] == 'A' ? -1 : 2);
    }
    f[n][0][s[1] == 'B'] = 0;
    for(int i = 1; i <= n; i++) {
        char c = s[i];
        g[i] = g[i - 1];
        chmax(g[i], f[pre[i]][i % 3][1] + i / 3);
        if(c == 'B') {
            chmax(g[i], f[pre[i]][i % 3][0] + i / 3);
        }
        if(i + 1 <= n) {
            chmax(f[pre[i]][i % 3][s[i + 1] == 'B'], g[i] - i / 3);
        }
    }
    cout << g[n] << "\n";
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
