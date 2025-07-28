#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int w, u, v;
    friend bool operator < (const info &a, const info &b) {
        if(a.w != b.w) return a.w > b.w;
        return a.u > b.u;
    }
};
void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    s = "#" + s;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> pre(n + 2), nxt(n + 2);
    for(int i = 1; i <= n; i++) {
        pre[i] = i - 1;
        nxt[i] = i + 1;
    }
    vector<int> vis(n + 1);
    vector<int> ans;
    ans.reserve(n);
    priority_queue<info> q;
    for(int i = 1; i < n; i++) {
        if(s[i] != s[i + 1]) {
            q.push({abs(a[i] - a[i + 1]), i, i + 1});
        }
    }
    while(!q.empty()) {
        auto [w, u, v] = q.top(); q.pop();
        if(vis[u] || vis[v]) continue;
        vis[u] = vis[v] = true;
        ans.push_back(u);
        ans.push_back(v);
        nxt[pre[u]] = nxt[v];
        pre[nxt[v]] = pre[u];
        if(pre[u] >= 1 && nxt[v] <= n) {
            if(s[pre[u]] != s[nxt[v]]) {
                q.push({abs(a[pre[u]] - a[nxt[v]]), pre[u], nxt[v]});
            }
        }
    }
    cout << ans.size() / 2 << "\n";
    for(int i = 0; i < ans.size(); i += 2) {
        cout << ans[i] << " " << ans[i + 1] << "\n";
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
