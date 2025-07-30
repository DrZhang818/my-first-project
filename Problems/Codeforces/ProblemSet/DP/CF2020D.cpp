#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


struct info {
    int d, k;
};
vector<int> fa;
int sz;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) {
    u = find(u), v = find(v);
    if(u == v) return;
    fa[u] = v;
    sz--;
}
void solve() {
    int n, m;
    cin >> n >> m;
    fa.resize(n + 1);
    iota(fa.begin(), fa.end(), 0);
    sz = n;
    vector<vector<info>> a(n + 1);
    for(int i = 1; i <= m; i++) {
        int pos, d, k;
        cin >> pos >> d >> k;
        a[pos].emplace_back(d, k);
    }
    vector dp(11, vector<int>(11)); 
    for(int i = 1; i <= n; i++) {
        for(int d = 1; d <= 10; d++) {
            if(dp[d][0]) {
                merge(i - d, i);
                dp[d][0]--;
            }
            for(int j = 0; j < d - 1; j++) {
                swap(dp[d][j], dp[d][j + 1]);
            }
        }
        for(auto [d, k] : a[i]) {
            dp[d][d - 1] = max(dp[d][d - 1], k);
        }
    }
    cout << sz << "\n";
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
