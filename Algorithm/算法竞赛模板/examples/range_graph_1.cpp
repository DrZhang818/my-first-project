#include "../code/range_graph.hpp"
int main() {
    RangeGraph s(6);
    s.pointRange(1, 2, 3, 5); // 1→[2,3]，每条权5。
    s.rangePoint(2, 3, 4, 2); // [2,3]→4，权2。
    s.rangeRange(4, 4, 5, 6, 1);
    auto d = s.distances(1);
    assert(d[2] == 5 && d[4] == 7 && d[6] == 8);
}
