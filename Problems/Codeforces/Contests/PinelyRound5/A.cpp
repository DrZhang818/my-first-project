#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int R0, X, D, n;
    cin >> R0 >> X >> D >> n;
    string s;
    cin >> s;
    int ans = 0;
    for(char c : s) {
        if(c == '1') {
            ans++;
            if(R0 >= X) {
                R0 -= D;
            }
        } else {
            if(R0 < X) {
                ans++;
            }
        }
    }
    cout << ans << "\n";
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
