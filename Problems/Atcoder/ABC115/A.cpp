#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int d;
    cin >> d;
    if(d == 25) {
        cout << "Christmas\n";
    } else if(d == 24) {
        cout << "Christmas Eve\n";
    } else if(d == 23) {
        cout << "Christmas Eve Eve\n";
    } else {
        cout << "Christmas Eve Eve Eve\n";
    }
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
