#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int v, w;
};
struct rd {
    int v, p, q;
};
void solve() {
    int n, m, id = 0;
    cin >> n >> m;
    vector<vector<info>> a(m + 1);
    vector<rd> vec(m + 1); 
    vector<int> to(m + 1);
    for(int i = 1; i <= m; i++) {
        int v, p, q;
        cin >> vec[i].v >> vec[i].p >> vec[i].q;
    }
    for(int i = 1; i <= m; i++) {
        int v = vec[i].v, p = vec[i].p, q = vec[i].q;
        if(q == 0) {
            a[++id].push_back({v, v * p});
            to[i] = id;
        }
    }
    for(int i = 1; i <= m; i++) {
        int v = vec[i].v, p = vec[i].p, q = vec[i].q;
        if(q) {
            int idx = to[q];
            a[idx].push_back({v + a[idx][0].v, v * p + a[idx][0].w});
            if(a[idx].size() == 3) {
                a[idx].push_back({v + a[idx][1].v, v * p + a[idx][1].w});
            }
        }       
    }
    vector<vector<ll>> dp(id + 1, vector<ll>(n + 1));
    for(int i = 1; i <= id; i++) {
        for(int j = 0; j <= n; j++) {
            dp[i][j] = dp[i - 1][j];
            for(int k = 0; k < a[i].size(); k++) {
                if(j - a[i][k].v < 0) continue;
                dp[i][j] = max(dp[i][j], dp[i - 1][j - a[i][k].v] + a[i][k].w);
            }
        }
    }
    cout << dp[id][n] << "\n";
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
