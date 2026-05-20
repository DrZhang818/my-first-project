template<int K>
struct TopK {
    struct Node {
        int val = 0;
        int key = -1;
    };

    array<Node, K> a;

    void norm() {
        sort(a.begin(), a.end(), [&](const Node &x, const Node &y) {
            return x.val > y.val;
        });
    }

    void add(int key, int val) {
        for (auto &x : a) {
            if (x.key == key) {
                x.val = max(x.val, val);
                norm();
                return;
            }
        }

        if (val > a[K - 1].val) {
            a[K - 1] = {val, key};
            norm();
        }
    }

    int get(int ban) const {
        for (auto x : a) {
            if (x.key != ban) {
                return x.val;
            }
        }
        return 0;
    }
};