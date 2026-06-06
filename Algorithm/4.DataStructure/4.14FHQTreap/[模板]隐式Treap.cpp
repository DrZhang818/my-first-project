// 约定：
// 1. Policy::merge(left, right) 必须表示 leftInfo + rightInfo。
// 2. Policy::merge 必须满足结合律。
// 3. Policy::identity() 必须是空序列信息。
// 4. applyTag() 必须同步更新 val 和 info。
// 5. compose(oldTag, newTag) 表示原来已有 oldTag，现在又来了 newTag。
// 6. 若使用 rangeReverse()，reverse_info() 必须正确维护方向性信息。
// 7. setValue() 必须通过接口调用，不要裸改 tr[u].val 后 pullPath。

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template <typename Policy>
struct FHQ {
    using Val = typename Policy::Val;
    using Info = typename Policy::Info;
    using Tag = typename Policy::Tag;

    struct Node {
        int l = 0, r = 0, fa = 0;
        int sz = 1;
        unsigned int pri = 0;

        Val val{};
        Info info{};
        Tag tag{};

        bool rev = false;
    };

    vector<Node> tr;

    FHQ(int n = 0) {
        tr.reserve(n + 1);
        tr.push_back(Node{});
        tr[0].sz = 0;
        tr[0].info = Policy::identity();
        tr[0].tag = Policy::tag_identity();
    }

    int newNode(const Val& v) {
        tr.push_back(Node{});
        int u = int(tr.size()) - 1;

        tr[u].l = tr[u].r = tr[u].fa = 0;
        tr[u].sz = 1;
        tr[u].pri = rng();
        tr[u].val = v;
        tr[u].info = Policy::make(v);
        tr[u].tag = Policy::tag_identity();
        tr[u].rev = false;

        return u;
    }

    int size(int u) const {
        return u ? tr[u].sz : 0;
    }

    Info info(int u) const {
        return u ? tr[u].info : Policy::identity();
    }

    void setFa(int u, int fa) {
        if(u) tr[u].fa = fa;
    }

    void pull(int u) {
        if(!u) return; 
        tr[u].sz = size(tr[u].l) + size(tr[u].r) + 1;
        tr[u].info = Policy::merge(
            Policy::merge(info(tr[u].l), Policy::make(tr[u].val)),
            info(tr[u].r)
        );

        setFa(tr[u].l, u);
        setFa(tr[u].r, u);
    }

    void applyTag(int u, const Tag& tag) {
        if(!u || Policy::tag_empty(tag)) return;
        Policy::apply(tr[u].val, tr[u].info, tr[u].sz, tag);
        Policy::compose(tr[u].tag, tag);
    }

    void applyRev(int u) {
        if(!u) return;

        swap(tr[u].l, tr[u].r);
        tr[u].rev ^= 1;
        Policy::reverse_info(tr[u].info);
    }

    void push(int u) {
        if(!u) return;

        if(tr[u].rev) {
            applyRev(tr[u].l);
            applyRev(tr[u].r);
            tr[u].rev = false;
        }

        if(!Policy::tag_empty(tr[u].tag)) {
            applyTag(tr[u].l, tr[u].tag);
            applyTag(tr[u].r, tr[u].tag);
            tr[u].tag = Policy::tag_identity();
        }
    }

    void pushPath(int u) {
        vector<int> path;
        for(int x = u; x; x = tr[x].fa) {
            path.push_back(x);
        }
        reverse(path.begin(), path.end());
        for(int x : path) push(x);
    }

    void pullPath(int u) {
        for(int x = u; x; x = tr[x].fa) {
            pull(x);
        }
    }

    pair<int,int> split(int u, int k) {
        if(!u) return {0, 0};

        push(u);

        if(size(tr[u].l) >= k) {
            auto [x, y] = split(tr[u].l, k);
            tr[u].l = y;
            pull(u);

            setFa(x, 0);
            setFa(u, 0);
            return {x, u};
        } else {
            auto [x, y] = split(tr[u].r, k - size(tr[u].l) - 1);
            tr[u].r = x;
            pull(u);

            setFa(u, 0);
            setFa(y, 0);
            return {u, y};
        }
    }

    int merge(int u, int v) {
        if(!u || !v) {
            int rt = u | v;
            setFa(rt, 0);
            return rt;
        }

        if(tr[u].pri > tr[v].pri) {
            push(u);
            tr[u].r = merge(tr[u].r, v);
            pull(u);
            setFa(u, 0);
            return u;
        } else {
            push(v);
            tr[v].l = merge(u, tr[v].l);
            pull(v);
            setFa(v, 0);
            return v;
        }
    }

    int getRoot(int u) const {
        while(tr[u].fa) {
            u = tr[u].fa;
        }
        return u;
    }

    int getRank(int u) {
        pushPath(u);

        int res = size(tr[u].l) + 1;

        while(tr[u].fa) {
            int f = tr[u].fa;
            if(tr[f].r == u) {
                res += size(tr[f].l) + 1;
            }
            u = f;
        }

        return res;
    }

    int kth(int u, int k) {
        while(u) {
            push(u);

            int ls = size(tr[u].l);
            if(k <= ls) {
                u = tr[u].l;
            } else if(k == ls + 1) {
                return u;
            } else {
                k -= ls + 1;
                u = tr[u].r;
            }
        }
        return 0;
    }

    pair<int,int> splitBeforeNode(int u) {
        int rt = getRoot(u);
        int rk = getRank(u);
        return split(rt, rk - 1);
    }

    pair<int,int> splitAfterNode(int u) {
        int rt = getRoot(u);
        int rk = getRank(u);
        return split(rt, rk);
    }

    int build(const vector<Val>& a) {
        int rt = 0;
        for(const auto& v : a) {
            rt = merge(rt, newNode(v));
        }
        return rt;
    }

    void setValue(int u, const Val& v) {
        pushPath(u);
        tr[u].val = v;
        pullPath(u);
    }

    tuple<int,int,int> splitRange(int rt, int l, int r) {
        auto [a, bc] = split(rt, l - 1);
        auto [b, c] = split(bc, r - l + 1);
        return {a, b, c};
    }

    Info rangeQuery(int& rt, int l, int r) {
        auto [a, b, c] = splitRange(rt, l, r);
        Info ans = info(b);
        rt = merge(a, merge(b, c));
        return ans;
    }

    void rangeApply(int& rt, int l, int r, const Tag& tag) {
        auto [a, b, c] = splitRange(rt, l, r);
        applyTag(b, tag);
        rt = merge(a, merge(b, c));
    }

    void rangeReverse(int& rt, int l, int r) {
        auto [a, b, c] = splitRange(rt, l, r);
        applyRev(b);
        rt = merge(a, merge(b, c));
    }

    int eraseRange(int& rt, int l, int r) {
        auto [a, b, c] = splitRange(rt, l, r);
        rt = merge(a, c);
        return b;
    }

    void insertAfter(int& rt, int pos, int mid) {
        auto [a, b] = split(rt, pos);
        rt = merge(merge(a, mid), b);
    }
};

struct Policy {
    struct Val {};
    struct Info {};
    struct Tag {};

    static Info identity() {
        return {};
    }

    static Info make(const Val& value) {
        return {};
    }

    static Info merge(const Info& leftInfo, const Info& rightInfo) {
        return {};
    }

    static void reverse_info(Info& info) {
    }

    static Tag tag_identity() {
        return {};
    }

    static bool tag_empty(const Tag& tag) {
        return true;
    }

    static void apply(Val& value, Info& info, int subtreeSize, const Tag& tag) {
    }

    static void compose(Tag& oldTag, const Tag& newTag) {
    }
};