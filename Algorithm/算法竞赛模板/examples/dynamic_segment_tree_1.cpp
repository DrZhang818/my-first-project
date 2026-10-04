#include "../code/dynamic_segment_tree.hpp"
struct Info {
    long long sum = 0;
    Info operator+(Info b) const {
        return {sum + b.sum};
    }
};
int main() {
    DynSeg<Info> s(-1000000000, 1000000000);
    int rt = 0;
    s.modify(rt, -7, {3});
    s.modify(rt, 12, {5});
    s.modify(rt, 12, {1});
    assert(s.query(rt, -10, 20).sum == 4);
}
