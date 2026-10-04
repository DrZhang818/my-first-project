#include "../code/kruskal_reconstruction_tree.hpp"
int main() {
    KRT s(4, {{1, 2, 4}, {2, 3, 7}, {1, 3, 10}});
    long long w;
    assert(s.bottle(1, 3, w) && w == 7);
    assert(!s.bottle(1, 4, w));
}
