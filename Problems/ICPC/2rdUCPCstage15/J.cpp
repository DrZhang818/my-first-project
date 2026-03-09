#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    vector<int> cur(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> dis(n + 1, inf);
    vector<int> vis(n + 1);
    dis[0] = 0;

    vector<int> q;
    q.push_back(0);

    while(!q.empty()) {
        vector<int> nq;
        for(int u : q) {
            int v = (u + a[u]) % n;
            if(!vis[v]) {
                vis[v] = true;
                dis[v] = min(dis[v], dis[u] + cur[u] + 1);
                cur[u]++;
                a[u]++;
                nq.push_back(u);
                if(v != u) {
                    nq.push_back(v);
                }
            }
        }
        q = move(nq);
    }

    cout << dis[x] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
