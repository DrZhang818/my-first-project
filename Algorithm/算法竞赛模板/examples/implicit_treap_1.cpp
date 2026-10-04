#include "../code/implicit_treap.hpp"
struct Policy {
    using Val = long long;
    using Info = long long;
    using Tag = long long;
    static Info identity() {
        return 0;
    }
    static Tag tagIdentity() {
        return 0;
    }
    static bool tagEmpty(Tag t) {
        return t == 0;
    }
    static Info make(Val v) {
        return v;
    }
    static Info merge(Info a, Info b) {
        return a + b;
    }
    static void apply(Val& v, Info& sum, int len, Tag t) {
        v += t;
        sum += len * t;
    }
    static void compose(Tag& a, Tag b) {
        a += b;
    }
    static void reverseInfo(Info&) {
    } // 和与方向无关，才能留空。
};
int main() {
    Treap<Policy> s;
    int rt = s.build(vector<long long>{1, 2, 3, 4}); // build为0-based。
    s.apply(rt, 2, 4, 10);
    s.rangeReverse(rt, 1, 3);
    assert(s.query(rt, 1, 2) == 25);
    int t = s.erase(rt, 2, 3);
    s.insert(rt, 0, t);
    assert(s.size(rt) == 4);
}
