#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
using ordered_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    vector<int> kthSmallest(vector<int>& fa, vector<int>& val, vector<vector<int>>& que) {
        int q = que.size(), n = fa.size();
        vector<int> ans(q, -1);
        vector<vector<int>> adj(n);
        for(int i = 1; i < n; i++) {
            adj[fa[i]].push_back(i);
        }
        vector<vector<PII>> Q(n);
        for(int i = 0; i < q; i++) {
            int u = que[i][0], k = que[i][1];
            Q[u].emplace_back(i, k);
        }
        auto dfs = [&](this auto &&self, int u, int w) -> ordered_set* {
            w ^= val[u];
            ordered_set* cur = new ordered_set();
            cur->insert(w);
            for(int v : adj[u]) {
                auto nxt = self(v, w);
                if(nxt->size() > cur->size()) {
                    swap(cur, nxt);
                }
                for(int x : *nxt) {
                    cur->insert(x);
                }
                delete nxt;
            }
            for(auto [id, k] : Q[u]) {
                if(k - 1 < cur->size()) {
                    ans[id] = *cur->find_by_order(k - 1);
                }
            }
            return cur;
        };
        ordered_set* st = dfs(0, 0);
        delete st;
        return ans;
    }
};