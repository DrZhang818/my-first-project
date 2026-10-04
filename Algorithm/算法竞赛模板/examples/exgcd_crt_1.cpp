#include "../code/exgcd_crt.hpp"
int main() {
    long long r, m;
    int ok = crt({{2, 6}, {5, 9}}, r, m);
    assert(ok == 1 && r == 14 && m == 18);
    assert(crt({{1, 2}, {0, 4}}, r, m) == 0);
}
