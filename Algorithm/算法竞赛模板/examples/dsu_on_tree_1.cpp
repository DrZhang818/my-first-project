#include "../code/dsu_on_tree.hpp"
int main() {
    vector<vector<int>> g(5);
    for(int u = 2; u <= 4; u++) {
        g[1].push_back(u), g[u].push_back(1);
    }
    vector<int> color = {0, 1, 1, 2, 2}, cnt(3), ans(5);
    int cur = 0;
    DSUOnTree s(g);
    s.run(
        [&](int u, int d) {
            if(cnt[color[u]]) {
                cur--;
            }
            cnt[color[u]] += d;
            if(cnt[color[u]]) {
                cur++;
            }
        },
        [&](int u) { ans[u] = cur; });
    assert(ans[1] == 2 && ans[2] == 1 && cur == 0);
}
