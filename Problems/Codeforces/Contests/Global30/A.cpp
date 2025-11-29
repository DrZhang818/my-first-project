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
    vector<int> a(n + 1);
    int mn = inf, mx = -inf;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        tie(mn, mx) = tie(min(mn, x), max(mx, x));
    }
    int x;
    cin >> x;
    if(mn <= x && x <= mx) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
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
