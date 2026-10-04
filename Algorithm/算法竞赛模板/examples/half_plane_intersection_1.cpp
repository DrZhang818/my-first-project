#include "../code/half_plane_intersection.hpp"
int main() {
    vector<Point> p = {{0, 0}, {3, 0}, {3, 2}, {0, 2}};
    vector<Line> a;
    for(int i = 0; i < 4; i++) {
        a.emplace_back(p[i], p[(i + 1) % 4]);
    }
    auto h = halfPlanes(a);
    long double area = 0;
    for(int i = 0; i < int(h.size()); i++) {
        area += cross(h[i], h[(i + 1) % h.size()]);
    }
    assert(fabsl(area / 2 - 6) < 1e-10);
}
