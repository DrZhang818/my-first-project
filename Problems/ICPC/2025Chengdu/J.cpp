#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m, k, b;
    cin >> n >> m >> k >> b;
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        vector<int> a(m);
        int sum1 = 0, sum2 = 0;
        for(int j = 0; j < m; j++) {
            cin >> a[j];
            sum1 += a[j];
            if(a[j] >= 1) sum2 += a[j] - 1;
            else sum2 += a[j] + 1;
        }
        if(sum1 >= k) {
            ans++;
        } else if(sum2 >= k && b) {
            b--;
            ans++;
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
