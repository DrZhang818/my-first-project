#include "../code/hld.hpp"
#include "../code/segment_tree.hpp"
struct Info {
    long long sum = 0;
    Info operator+(Info b) const {
        return {sum + b.sum};
    }
};
int main() {
    HLD h(4);
    h.addEdge(1, 2);
    h.addEdge(1, 3);
    h.addEdge(2, 4);
    h.work();
    vector<Info> a(5);
    for(int u = 1; u <= 4; u++) {
        a[h.in[u]] = {u};
    }
    Seg<Info> s(a);
    auto query = [&](int u, int v) {
        long long ans = 0;
        while(h.top[u] != h.top[v]) {
            if(h.dep[h.top[u]] < h.dep[h.top[v]]) {
                swap(u, v);
            }
            ans += s.query(h.in[h.top[u]], h.in[u]).sum;
            u = h.parent[h.top[u]];
        }
        if(h.dep[u] > h.dep[v]) {
            swap(u, v);
        }
        return ans + s.query(h.in[u], h.in[v]).sum;
    };
    assert(query(4, 3) == 10);
}
