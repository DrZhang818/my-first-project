#include "../code/fps.hpp"
int main() {
    vector<int> a = {1, 2, 3};
    auto b = polyInv(a, 8);
    auto c = fpsConvTrunc(a, b, 8);
    c.resize(8);
    assert(c[0] == 1);
    for(int i = 1; i < 8; i++) {
        assert(c[i] == 0);
    }
    auto d = polyExp(polyLog(a, 8), 8);
    a.resize(8);
    assert(d == a);
}
