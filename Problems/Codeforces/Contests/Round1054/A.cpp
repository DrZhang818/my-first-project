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

    int neg = 0, c0 = 0;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if(x < 0) {
            neg ^= 1;
        } else if(x == 0) {
            c0 += 1;
        }
    }
    cout << c0 + neg * 2 << "\n";
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
