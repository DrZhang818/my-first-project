#include "../code/offline_connectivity.hpp"
int main() {
    OfflineConn s(3, 4);
    s.add(1, 2, 1, 2); // 时刻3删去，所以截止2。
    s.add(2, 4, 2, 3);
    vector<pair<int, int>> ask = {{0, 0}, {1, 3}, {1, 3}, {1, 3}, {2, 3}};
    auto a = s.solve(ask);
    assert(a == vector<int>({0, 0, 1, 0, 1}));
}
