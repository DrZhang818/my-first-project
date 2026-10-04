#include "../code/segment_tree.hpp"
struct Info {
    long long sum = 0;
    Info operator+(Info b) const {
        return {sum + b.sum};
    }
};
int main() {
    vector<Info> a = {{0}, {2}, {0}, {3}};
    Seg<Info> s(a);
    assert(s.query(1, 3).sum == 5);
    int p = s.first(1, 3, [](Info x) { return x.sum >= 3; });
    assert(p == 3); // 频次必须非负，判定才单调。
}
