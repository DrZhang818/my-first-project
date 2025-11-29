#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    ll n, k, m;
    cin >> n >> k >> m;
    if(m <= n - n / k) {
        cout << m + 1 + (n / k - 1) / 2 << "\n";
    } else {
        cout << min(n, m + 1 + (n - m - 1) / 2) << "\n";
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
