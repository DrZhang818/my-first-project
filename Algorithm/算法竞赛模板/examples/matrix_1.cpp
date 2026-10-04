#include "../code/matrix.hpp"
int main() {
    Matrix a(2, 2);
    a(1, 1) = a(1, 2) = a(2, 1) = 1;
    auto v = power(a, 10) * vector<int>{0, 1, 0};
    assert(v[2] == 55); // [F(11),F(10)]，下标0占位。
}
