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
    int rem = 0;
    while(n--) {
        char op;
        int x;
        cin >> op >> x;
        if(op == 'B') {
            if(x > rem) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
            rem -= min(rem, x);
        } else {
            rem += x;
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
