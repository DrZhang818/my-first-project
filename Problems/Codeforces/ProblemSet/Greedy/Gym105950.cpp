#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9 + 7;

struct Info {
    int v, w;
    friend bool operator<(const Info& a, const Info& b) {
        return a.w > b.w;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<Info>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    vector<int> dis(n + 1, inf);
    dis[1] = 0;
    priority_queue<Info> pq;
    pq.push({1, 0});

    while(!pq.empty()) {
        auto [u, w] = pq.top(); pq.pop();
        if(w != dis[u]) {
            continue;
        }
        for(auto [v, val] : adj[u]) {
            int nw = max(w, val);
            if(nw < dis[v]) {
                dis[v] = nw;
                pq.push({v, nw});
            }
        }
    }

    int D;
    cin >> D;
    vector<int> a(D + 1);
    for(int i = 1; i <= D; i++) {
        cin >> a[i];
        a[i] = dis[a[i]];
    }
    vector<int> len(D + 1);
    for(int i = 1; i <= D; i++) {
        cin >> len[i];
    }

    sort(a.begin() + 1, a.end(), greater());
    sort(len.begin() + 1, len.end(), greater());

    int ans = 0;
    for(int i = 1, j = 1; i <= D; i++) {
        while(j <= D && a[j] > len[i]) {
            j++;
        }
        if(j > D) break;
        ans++;
        j++;
    }

    cout << ans << "\n";
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
