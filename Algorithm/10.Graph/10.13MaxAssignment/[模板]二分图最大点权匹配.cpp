#include <bits/stdc++.h>
using namespace std;
const int inf = 1000000000;

//下标从 0 开始
class MaxAssignment {
public:
    int solve(int n, int m, vector<vector<int>> &adj, vector<int> &val) {
        assert(adj.size() == n);
        assert(val.size() == n);
        vector<int> yx(m, -1);
        vector<bool> vis(n, false);
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        sort(p.begin(), p.end(),
            [&](auto x, auto y) {
                return val[x] > val[y];
            });
        auto find = [&](auto &&self, int x) -> bool {
            vis[x] = true;
            for(int y : adj[x]) {
                if(yx[y] == -1 || !vis[yx[y]] && self(self, yx[y])) {
                    yx[y] = x;
                    return true;
                }
            }
            return false;
        };
        int ans = 0;
        for(auto i : p) {
            if(find(find, i)) {
                vis.assign(n, false);
                ans += val[i];
            }
        }
        return ans;
    }
};