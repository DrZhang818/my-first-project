#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int r, x;
    cin >> r >> x;
    if(x == 1) {
        if(1600 <= r && r <= 2999) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    } else {
        if(1200 <= r && r <= 2399) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
