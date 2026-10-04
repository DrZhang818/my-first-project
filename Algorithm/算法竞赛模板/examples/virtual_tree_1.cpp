#include "../code/virtual_tree.hpp"
int main() {
    vector<vector<int>> g(6);
    for(auto [u, v] : vector<pair<int, int>>{{1, 2}, {1, 3}, {2, 4}, {2, 5}}) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    VirtualTree s(g);
    auto [root, e] = s.build({4, 5, 3, 4});
    long long ans = 0;
    for(auto [u, v] : e) {
        ans += s.dis(u, v);
    }
    assert(root == 1 && ans == 4);
}
