#include "../code/persistent_segment_tree.hpp"
struct Info {
    int sum = 0;
    void apply(Info b) {
        sum += b.sum;
    }
    Info operator+(Info b) const {
        return {sum + b.sum};
    }
    Info operator-(Info b) const {
        return {sum - b.sum};
    }
};
int main() {
    vector<int> a = {0, 5, 1, 5, 3}, v(a.begin() + 1, a.end());
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    int n = a.size() - 1, m = v.size();
    PST<Info> s(m, n);
    vector<int> rt(n + 1);
    for(int i = 1; i <= n; i++) {
        int x = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
        rt[i] = s.modify(rt[i - 1], x, {1});
    }
    int l = 2, r = 4, k = 2; // 闭区间；k需合法。
    int x = s.first(rt[l - 1], rt[r], 1, m, [&](Info t) { return t.sum >= k; });
    assert(v[x - 1] == 3);
}
