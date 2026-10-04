#include "../code/parallel_binary_search.hpp"
int main() {
    using E = KthOffline::Event;
    vector<E> e;
    e.push_back({0, 1, 5, 1, 0, 0, 0, 0});
    e.push_back({0, 2, 1, 1, 0, 0, 0, 0});
    e.push_back({1, 0, 0, 0, 1, 2, 1, 0});
    e.push_back({0, 2, 1, -1, 0, 0, 0, 0});
    e.push_back({0, 2, 7, 1, 0, 0, 0, 0});
    e.push_back({1, 0, 0, 0, 1, 2, 1, 1});
    auto a = KthOffline().solve(2, e, 2);
    assert(a == vector<int>({1, 5}));
}
