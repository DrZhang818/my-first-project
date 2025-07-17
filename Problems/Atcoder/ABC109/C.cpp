#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n + 2);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    a[n + 1] = x;
    sort(a.begin() + 1, a.end());
    int g = 0;
    for(int i = 1; i <= n; i++) {
        g = gcd(g, a[i + 1] - a[i]);
    }
    cout << g << "\n";
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
