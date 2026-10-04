#include "../code/cdq.hpp"
int main() {
    auto a = dominance({{1, 1, 1}, {1, 1, 1}, {2, 2, 2}});
    assert(a == vector<long long>({1, 1, 2}));
}
