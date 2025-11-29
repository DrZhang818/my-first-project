#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int l, r;
    cin >> l >> r;
    if(r == 2 * l) {
        cout << "Alice\n";
        return;
    }
    if(r < 2 * l) {
        if((r - l) % 2 == 0) {
            cout << "Alice\n"; 
        } else {
            cout << "Bob\n";
        }
    } else {
        if(l & 1) {
            cout << "Alice\n";
        } else {
            cout << "Bob\n";
        }
    }
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
