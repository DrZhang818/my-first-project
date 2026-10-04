#include "../code/dinic.hpp"
int main() {
    Dinic s(3);
    int id = s.addEdge(0, 1, 5);
    s.addEdge(1, 2, 3);
    assert(s.maxFlow(0, 2) == 3);
    assert(5 - s.g[0][id].cap == 3);
    s.addEdge(1, 2, 2);
    assert(s.maxFlow(0, 2) == 2); // 本次新增量。
}
