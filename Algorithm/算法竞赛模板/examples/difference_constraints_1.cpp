#include "../code/difference_constraints.hpp"
int main() {
    Diff s(3);
    s.le(2, 1, -3); // x2 >= x1+3。
    s.le(2, 3, 2);  // x3 <= x2+2。
    s.eq(1, 3, 4);  // x3=x1+4。
    vector<__int128> d;
    assert(s.solve(d));
    assert(d[2] - d[1] >= 3 && d[3] - d[1] == 4);
    s.le(1, 3, 3);
    assert(!s.solve(d));
}
