#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int N = 1000000;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), las(N + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    ll f = 1, g = 1;
    las[a[1]] = 1;
    for(int i = 2; i <= n; i++) {
        g = g + 2 + (i - 1 - las[a[i]]) * 2;
        f += g;
        las[a[i]] = i;
    }
    cout << fixed << setprecision(12) << db(f) / (1LL * n * n) << "\n";
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
