#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

const int N = 1000000;
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> pre(N + 1);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        pre[x] = 1;
    }
    for(int i = 1; i <= N; i++) {
        if(pre[i]) {
            pre[i] = i;
        } else {
            pre[i] = pre[i - 1];
        }
    }
    vector<int> vis(N + 1, -1);
    while(q--) {
        int x;
        cin >> x;
        if(vis[x] != -1) {
            cout << vis[x] << "\n";
            continue;
        }
        int ans = 0;
        for(int i = x - 1, c = 0; i <= N; i += x, c++) {
            int p = pre[i];
            if(p <= i - x) continue;
            ans = max(ans, c + p % x);
        }
        vis[x] = ans;
        cout << ans << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
