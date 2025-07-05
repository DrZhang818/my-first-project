#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> a(n + 1, vector<int>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            a[i][j] = c - '0';
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            a[i][j] += a[i - 1][j];
        }
    }
    for(int j = 1; j <= m; j++) {
        for(int i = 1; i <= n; i++) {
            a[i][j] += a[i][j - 1];
        }
    }
    ll ans = inf;
    for(int s = 0; s < 1 << n - 1; s++) {
        vector<int> cut = {1};
        int las = 0;
        ll cnt = 0;
        for(int i = 0; i < n - 1; i++) {
            if(s >> i & 1) {
                cnt++;
                cut.push_back(i + 2);
            }
        }
        cut.push_back(n + 1);
        bool ok = true;
        for(int j = 1; j <= m && ok; j++) {
            for(int p = 0; p < cut.size() - 1; p++) {
                int st = cut[p], en = cut[p + 1] - 1;
                if(a[en][j] - a[en][j - 1] - a[st - 1][j] + a[st - 1][j - 1] > k) {
                    ok = false;
                    break;
                }
                if(a[en][j] - a[en][las] - a[st - 1][j] + a[st - 1][las] > k) {
                    las = j - 1;
                    cnt++;
                    break;
                }
            }
        }
        if(!ok) continue;
        ans = min(ans, cnt);
    }
    cout << ans << "\n";
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
