#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    ll x, y;
    cin >> x >> y;
    for(int i = 3; i <= 10; i++) {
        ll z = x + y;
        string s = to_string(z);
        reverse(s.begin(), s.end());
        z = stoll(s);
        x = y;
        y = z;
    }
    cout << y << "\n";
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
