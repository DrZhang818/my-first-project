#include "../code/centroid_decomposition.hpp"
#include "../code/lca.hpp"
int main() {
    vector<vector<int>> g(6);
    for(int u = 2; u <= 5; u++) {
        g[u - 1].push_back(u), g[u].push_back(u - 1);
    }
    LCA l(g);
    Centroid c(g);
    const int INF = 1000000000;
    vector<int> best(6, INF);
    auto add = [&](int u) {
        for(int x = u; x; x = c.parent[x]) {
            best[x] = min(best[x], l.dis(u, x));
        }
    };
    auto query = [&](int u) {
        int ans = INF;
        for(int x = u; x; x = c.parent[x]) {
            ans = min(ans, best[x] + l.dis(u, x));
        }
        return ans;
    };
    add(1);
    add(5);
    assert(query(3) == 2 && query(4) == 1);
}
