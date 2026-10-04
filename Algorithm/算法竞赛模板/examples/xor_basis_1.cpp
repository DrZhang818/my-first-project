#include "../code/xor_basis.hpp"
int main() {
    XorBasis s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    unsigned long long x;
    assert(s.zero && s.kth(1, x) && x == 0);
    assert(s.kth(4, x) && x == 3);
    assert(!s.kth(5, x));
}
