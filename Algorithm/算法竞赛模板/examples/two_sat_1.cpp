#include "../code/two_sat.hpp"
int main() {
    TwoSAT s(2);
    s.addClause(1, true, 2, false); // x1 或 非x2。
    s.setValue(1, false);
    assert(s.solve());
    assert(!s.answer[1] && !s.answer[2]);
}
