#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, s;
    cin >> n >> s;
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        int dx, dy, x, y;
        cin >> dx >> dy >> x >> y;
        if(x + y == s && dx + dy == 0) {
            ans++;
        } else if(x == y && dx + dy != 0) {
            ans++;
        }
    }
    cout << ans << "\n";
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
