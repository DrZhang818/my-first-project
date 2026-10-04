#include "../code/hopcroft_karp.hpp"
int main() {
    HK s(3, 3);
    s.addEdge(1, 1);
    s.addEdge(1, 2);
    s.addEdge(2, 2);
    s.addEdge(3, 2);
    assert(s.solve() == 2);
    auto [a, b] = s.minVertexCover();
    assert(a.size() + b.size() == 2);
    for(int u = 1; u <= 3; u++) {
        if(s.left[u]) {
            cout << u << ' ' << s.left[u] << '\n';
        }
    }
}
