#include "../code/link_cut_tree.hpp"
int main() {
    LCT s(3);
    for(int i = 1; i <= 3; i++) {
        s.setValue(i, i);
    }
    assert(s.link(1, 2) && s.link(2, 3));
    assert(s.pathXor(1, 3) == (1 ^ 2 ^ 3));
    assert(!s.link(1, 3));
    assert(s.cut(1, 2));
    assert(!s.connected(1, 3));
}
