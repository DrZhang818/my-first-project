#include "../code/lazy_segment_tree.hpp"
const int P = 998244353;
struct Tag {
    long long mul = 1, add = 0;
    void apply(Tag t) {
        mul = mul * t.mul % P;
        add = (add * t.mul + t.add) % P;
    }
};
struct Info {
    long long sum = 0;
    int len = 0;
    void apply(Tag t) {
        sum = (sum * t.mul + t.add * len) % P;
    }
    Info operator+(Info b) const {
        return {(sum + b.sum) % P, len + b.len};
    }
};
int main() {
    vector<Info> a = {{0, 0}, {1, 1}, {2, 1}, {3, 1}};
    LazySeg<Info, Tag> s(a);
    s.apply(1, 3, {2, 1}); // x -> 2x+1，得到 3,5,7。
    s.apply(2, 3, {0, 4}); // 赋值为4；加c用 {1,c}。
    assert(s.query(1, 3).sum == 11);
}
