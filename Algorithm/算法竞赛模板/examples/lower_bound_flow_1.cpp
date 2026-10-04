#include "../code/lower_bound_flow.hpp"
int main() {
    BoundFlow s(3);
    s.addEdge(0, 1, 1, 3);
    s.addEdge(1, 2, 1, 2);
    BoundFlow::Result a, b;
    assert(s.maxFlow(0, 2, a) && a.value == 2);
    assert(s.minFlow(0, 2, b) && b.value == 1);
    assert(a.flow[0] == 2 && b.flow[1] == 1);
    vector<long long> f;
    assert(!s.circulation(f)); // 此图没有回边，无法形成环流。
}
