#include "../code/bsgs.hpp"
int main() {
    assert(BSGS::solve(2, 4, 8) == 2);
    assert(BSGS::solve(2, 3, 8) == -1);
    assert(BSGS::solve(0, 0, 7) == 1);
}
