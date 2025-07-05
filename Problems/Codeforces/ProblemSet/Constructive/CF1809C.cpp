#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 2);
    int r = 1;
    while(r * (r + 1) / 2 <= k) r++;
    r--;
    int rem = k - r * (r + 1) / 2;
    for(int i = 1; i <= r; i++) a[i] = 2;
    a[r + 1] = 2 * (rem - r) - 1;
    for(int i = r + 2; i <= n; i++) a[i] = -1000;
    for(int i = 1; i <= n; i++) {
        cout << a[i] << " \n"[i == n];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
