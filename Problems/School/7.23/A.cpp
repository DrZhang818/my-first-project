#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int y, id;
    friend bool operator < (const info &a, const info &b) {
        return a.y < b.y;
    }
};
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<info>> adj(n + 1); 
    for(int i = 1; i <= m; i++) {
        int y, p;
        cin >> p >> y;
        adj[p].emplace_back(y, i);
    }
    vector<string> ans(m + 1);
    for(int i = 1; i <= n; i++) {
        sort(adj[i].begin(), adj[i].end());
        int c = 1;
        for(auto [y, id] : adj[i]) {
            string s;
            int ti = i;
            while(ti) {
                s += '0' + ti % 10;
                ti /= 10;
            }
            while(s.size() < 6) s += '0';
            reverse(s.begin(), s.end());
            int tc = c;
            string t;
            while(tc) {
                t += '0' + tc % 10;
                tc /= 10;
            }
            while(t.size() < 6) t += '0';
            reverse(t.begin(), t.end());
            ans[id] = s + t;
            c++;
        }
    }
    for(int i = 1; i <= m; i++) {
        cout << ans[i] << "\n";
    }
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
