#include "../code/boruvka.hpp"
int main() {
    vector<Boruvka::Edge> e = {{1, 2, 4}, {2, 3, 1}, {1, 3, 2}};
    auto a = Boruvka::run(4, e);
    assert(a.weight == 3 && a.comp == 2);
    assert(a.edges.size() == 2); // 第4点孤立，不能当生成树。
}
