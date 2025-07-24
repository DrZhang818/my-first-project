#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc415/tasks/abc415_f
/*
    线段树区间合并
    题意:
        给定一个长度为N的字符串, 你需要回答Q次查询
        q1: 给定i,x, 将第i个字符修改为x
        q2: 给定l,r, 求出s[l:r]中最长连续相同字符的长度
        范围: N∈[1,5e5], Q∈[1,5e5]
    关键思考:
        本题为数据结构类题目, 需要读请题意, 选用合适的算法与数据结构维护题目信息, 回答询问
        首先考虑不带修时的做法
        如果暴力查询s[l:r], 时间复杂度是O(n)的, 那么总时间复杂度是O(nq), 超时
        考虑分治, 我们可以取l,r的中的mid, 那么问题就变成求解[l,mid][mid+1,r],以及二者合并后的中间部分的
        最大值
        线段树的结构天然适合维护分治信息, 我们只要能够写出push_up函数(merge)就能统计二者合并后的中间部分
        的长度, 而对于左儿子和右儿子的最大值是很好维护的
        那么如何进行merge呢?
        我们把区间左侧最大值和右侧最大值记录下来, 以及左侧和右侧的字符
        这样在合并时, 如果左儿子的右侧字符和右儿子的左侧字符相同, 我们就可以进行合并了
        合并后的长度为左儿子的右侧最大值 + 右儿子的左侧最大值
        合并后的区间左侧最大值继承左儿子的, 右侧最大值继承右儿子的
        如果左侧最大值等于左侧区间的长度, 说明有可能和右儿子的左侧拼起来
        此时需要判断左儿子的左侧字符和右儿子的左侧字符是否相同
        右儿子同理操作                
*/
inline int ls(int o) { return o << 1; }
inline int rs(int o) { return o << 1 | 1; }
class SegmentTree {
private:
    struct node {
        char ch_L, ch_R;
        int len_L, len_R;
        int mx;
        int len;
    };
    vector<node> tr;
    string s;
public:
    SegmentTree(int n, string t) : tr(n << 2), s(t) {}
    node merge(node l, node r) {
        node res;
        res.ch_L = l.ch_L;
        res.ch_R = r.ch_R;
        res.len_L = l.len_L;
        res.len_R = r.len_R;
        res.len = l.len + r.len;
        res.mx = max(l.mx, r.mx);
        if(l.ch_R == r.ch_L) res.mx = max(res.mx, l.len_R + r.len_L);
        if(l.len_L == l.len && l.ch_L == r.ch_L) res.len_L += r.len_L;
        if(r.len_R == r.len && r.ch_R == l.ch_R) res.len_R += l.len_R;
        return res;
    }
    void build(int o, int l, int r) {
        if(l == r) {
            tr[o] = node(s[l], s[l], 1, 1, 1, 1);
            return;
        }
        int mid = l + r >> 1;
        build(ls(o), l, mid);
        build(rs(o), mid + 1, r);
        tr[o] = merge(tr[ls(o)], tr[rs(o)]);
    }
    void modify(int i, int o, int l, int r, char x) {
        if(l == r) {
            tr[o].ch_L = tr[o].ch_R = x;
            return;
        }
        int mid = l + r >> 1;
        if(i <= mid) modify(i, ls(o), l, mid, x);
        else modify(i, rs(o), mid + 1, r, x);
        tr[o] = merge(tr[ls(o)], tr[rs(o)]);
    }
    node query(int L, int R, int o, int l, int r) {
        if(L <= l && r <= R) {
            return tr[o];
        }
        int mid = l + r >> 1;
        if(R <= mid) return query(L, R, ls(o), l, mid);
        if(L > mid) return query(L, R, rs(o), mid + 1, r);
        return merge(query(L, mid, ls(o), l, mid), query(mid + 1, R, rs(o), mid + 1, r));
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    s = "#" + s;
    SegmentTree tr(n, s);
    tr.build(1, 1, n);
    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            int i;
            char x;
            cin >> i >> x;
            tr.modify(i, 1, 1, n, x);
        } else {
            int l, r;
            cin >> l >> r;
            cout << tr.query(l, r, 1, 1, n).mx << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
