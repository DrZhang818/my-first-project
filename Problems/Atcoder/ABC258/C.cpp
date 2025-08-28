#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    int pos = 0;
    while(q--) {
        int op, x;
        cin >> op >> x;
        if(op == 1) {
            pos = ((pos - x) % n + n) % n;
        } else {
            cout << s[(pos + x - 1) % n] << "\n";
        }
    }
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
