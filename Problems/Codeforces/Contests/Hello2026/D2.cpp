#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    [&](this auto &&self, int u, int fa) -> void {
        auto it = find(adj[u].begin(), adj[u].end(), fa);
        if(it != adj[u].end()) {
            swap(*it, adj[u].back());
            adj[u].pop_back();
        }
        for(int v : adj[u]) {
            self(v, u);
        }
    } (1, 0);

    vector<int> q {1}, idx(n + 1, -1);
    vector<vector<int>> ans;

    idx[1] = 0;
    ans.push_back({1});

    while(!q.empty()) {
        vector<int> nq;
        int rem = q.size(), cnt = ans.size(), p = 0;
        for(int i = 0, j = (i + 1) % q.size(); i < q.size(); i++) {
            int u = q[i];

            if(adj[u].size() == 0) break;

            for(int v : adj[u]) {
                nq.push_back(v);
                if(rem > 0 && j != i) {
                    ans[idx[q[j]]].push_back(v);
                    idx[v] = idx[q[j]];
                    j = j + 1 == q.size() ? 0 : j + 1;
                    rem--;
                } else {
                    while(p < cnt && idx[ans[p].back()] != -1) p++;
                    if(p < cnt) {
                        ans[p].push_back(v);
                        idx[v] = p;
                        p++;
                    } else {
                        ans.push_back({v});
                        idx[v] = ans.size() - 1;
                    }
                }
            }
        }
        for(int u : q) {
            idx[u] = -1;
        }
        partition(nq.begin(), nq.end(),
            [&](auto x) {
                return adj[x].size() > 0;
            });
        swap(q, nq);
    }
    
    cout << ans.size() << "\n";
    for(auto &vec : ans) {
        cout << vec.size() << " ";
        for(int i = 0; i < vec.size(); i++) {
            cout << vec[i] << " \n"[i == vec.size() - 1];
        }
    }
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
