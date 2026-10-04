#include "../code/min_cost_flow.hpp"
int main() {
    MCF s(3);
    s.addEdge(0, 1, 2, -3);
    s.addEdge(1, 2, 2, 5);
    auto [f, c] = s.flow(0, 2, 2);
    assert(f == 2 && c == 4);
}
