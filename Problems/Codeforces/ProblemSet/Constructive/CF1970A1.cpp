#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int v, pos;
    friend bool operator < (const info &a, const info &b) {
        if(a.v != b.v) {
            return a.v < b.v;
        }
        return a.pos > b.pos;
    }
};
void solve() {
    string s;
    cin >> s;
    int n = s.size();
    s = "#" + s;
    vector<info> a(n + 1);
    for(int i = 1, x = 0; i <= n; i++) {
        a[i] = info(x, i);
        x += (s[i] == '(' ? 1 : -1);
    }
    sort(a.begin() + 1, a.end());
    for(int i = 1; i <= n; i++) {
        cout << s[a[i].pos];
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
