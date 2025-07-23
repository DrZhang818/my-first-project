#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1E9;

//https://ac.nowcoder.com/acm/contest/111679/D
/*
    数据结构 || 贪心排序 || 枚举
    题意:
        给定N个区间[l,r]和一个整数k, 你可以放置两个长度为k的区间, 如果给定第i个区间与你放置的区间
        有交集, 则认为该区间被收集
        请你求出最多能收集多少个区间
        范围: N∈[1,3e5], k∈[0,1e9], l,r∈[1,1e9]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        我们考虑使用区间选点trick, 把给定的区间[l,r]转化成[l,r+k], 这样我们就不是放置区间, 而变成
        放置两个点, 使得覆盖这两个点的区间最多
        首先考虑一个点的时候如何做, 如果l,r比较小, 我们可以用差分, 但对于l,r较大的情况, 我们可以用
        优先队列来维护:
        (1)首先把区间按照左端点升序排列
        (2)从小到大枚举区间, 把当前区间加入优先队列, 优先队列按照区间右端点从大到小排序, 这样如果
            堆顶区间的右端点小于当前区间左端点, 那么就弹出该区间
        (3)重复完步骤(2)后, 优先队列的大小就是当前有交集的区间个数
        换句话说, 我们用这种方法求出了: 排序后, 考虑前i个区间, 包含第i个区间的最大交集个数
        在枚举过程中不断取max, 即可得到一个点情况的最大值
        回到原问题, 如果还可以再选一个点, 我们又该如何做呢?
        在上面的枚举中, 我们还要计算: 考虑前i个区间, 不在堆中的区间的最大交集个数
        此时能否再开一个优先队列维护呢? 这是不行的, 因为此时加入堆的区间不是按照从小到大顺序加入的
        但我们发现, 此时用第一种方法就很合适了, 可以离散化后用线段树维护区间加与区间最值查询
        我们发现, 经过这样枚举, 我们成功避开了"如何处理重复区间"的问题
        但如果枚举的时候都使用第一种方法, 就很难处理这种问题了, 这正是优先队列方法的优势
        它可以强制选择第i个区间, 这样我们就完全知道哪些区间被选择哪些没被选择
        但是用线段树的方式是不能获得这些信息的, 他只能给出答案
        因此我们在枚举时使用优先队列, 在统计第二个点的时候用线段树
*/
struct info {
    int l, r;
    friend bool operator < (const info &a, const info &b) {
        return a.l < b.l;
    }
};
inline int ls(int o) { return o << 1; }
inline int rs(int o) { return o << 1 | 1; } 
class SegmentTree {
private:
    vector<int> mx, tag;
public:
    SegmentTree(int x) : mx(x << 2), tag(x << 2) {}
    void push_up(int o) {
        mx[o] = max(mx[ls(o)], mx[rs(o)]);
    }
    void addtag(int o, int l, int r, int d) {
        tag[o] += d;
        mx[o] += d;
    }
    void push_down(int o, int l, int r) {
        if(tag[o]) {
            int mid = l + r >> 1;
            addtag(ls(o), l, mid, tag[o]);
            addtag(rs(o), mid + 1, r, tag[o]);
            tag[o] = 0;
        }
    }
    void add(int L, int R, int o, int l, int r, int d) {
        if(L <= l && r <= R) {
            addtag(o, l, r, d);
            return;
        }
        push_down(o, l, r);
        int mid = l + (r - l) / 2;
        if(L <= mid) add(L, R, ls(o), l, mid, d);
        if(R > mid) add(L, R, rs(o), mid + 1, r, d);
        push_up(o);
    }
    int query_max(int L, int R, int o, int l, int r) {
        if(L <= l && r <= R) return mx[o];
        push_down(o, l, r);
        int res = -inf;
        int mid = l + r >> 1;
        if(L <= mid) res = max(res, query_max(L, R, ls(o), l, mid));
        if(R > mid) res = max(res, query_max(L, R, rs(o), mid + 1, r));
        return res;
    }
};

void solve() {
    int n, k;
    cin >> n >> k;
    vector<info> a(n);
    vector<int> val{0};
    for(int i = 0; i < n; i++) {
        cin >> a[i].l >> a[i].r;
        a[i].r += k;
        val.push_back(a[i].l);
        val.push_back(a[i].r);
    }
    sort(a.begin(), a.end());
    sort(val.begin() + 1, val.end());
    val.erase(unique(val.begin() + 1, val.end()), val.end());
    int sz = val.size();
    SegmentTree tr(sz);
    priority_queue<PII, vector<PII>, greater<PII>> q;
    int ans = 0;
    for(auto [l, r] : a) {
        while(!q.empty() && q.top().first < l) {
            auto [R, L] = q.top(); q.pop();
            L = lower_bound(val.begin() + 1, val.end(), L) - val.begin();
            R = lower_bound(val.begin() + 1, val.end(), R) - val.begin();
            tr.add(L, R, 1, 1, sz, 1);
        }
        q.push({r, l});
        int cur = q.size();
        ans = max(ans, cur + tr.query_max(1, sz, 1, 1, sz));
    }
    cout << ans << "\n";
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
