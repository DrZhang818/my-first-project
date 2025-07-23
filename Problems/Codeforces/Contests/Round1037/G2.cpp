#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2126/problem/G2
/*
    枚举 || 中位数Trick || 线段树 || 双指针
    题意:
        给定一个长度为N的数组, 你需要从中选取一段子数组a[l:r], 
        使得med(a[l:r]) - min(a[l:r])最大
        med(a[l:r])表示a[l:r]的中位数, 即第(k+1)/2大元素(上取整)
        输出能得到的最大值
        范围: N∈[1,2e5], a[i]∈[1,n]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        由G1的分析, 我们已经有了初步的思路, 就是枚举med后枚举数组
        但现在a[i]范围增大, 上述思路的时间复杂度变为O(n^2), 无法通过
        我们思考如何节省枚举数组这一步
        由于med越大, 对数组a的要求越严格, 因为数组b的-1个数只会更多, 1的个数只会更少
        那么med和min就有了单调性关系, 当med增大后, 能取到的min单调不降
        这样我们就可以用双指针来寻找min, 而无需遍历整个数组寻找min
        另一个问题是如何维护S以及前缀max后缀min
        显然可以用线段树来维护, 每次相当于一系列单点修改
        把遍历到med + 1时, 把所有a[i] = med的位置i对应的b数组-2 (从1变成-1)
*/
inline int ls(int o) { return o << 1; }
inline int rs(int o) { return o << 1 | 1; } 
class SegmentTree {
private:
    int n;
    vector<int> mx, mn;
    vector<int> tag;
public:
    SegmentTree(int x) : n(x), mx(x << 2), mn(x << 2), tag(x << 2) {}
    void push_up(int o) {
        mx[o] = max(mx[ls(o)], mx[rs(o)]);
        mn[o] = min(mn[ls(o)], mn[rs(o)]);
    }
    void addtag(int o, int l, int r, int d) {
        tag[o] += d;
        mx[o] += d;
        mn[o] += d;
    }
    void push_down(int o, int l, int r) {
        if(tag[o]) {
            int mid = l + (r - l) / 2;
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
        int mid = l + (r - l) / 2;
        if(L <= mid) res = max(res, query_max(L, R, ls(o), l, mid));
        if(R > mid) res = max(res, query_max(L, R, rs(o), mid + 1, r));
        return res;
    }
    int query_min(int L, int R, int o, int l, int r) {
        if(L <= l && r <= R) return mn[o];
        push_down(o, l, r);
        int res = inf;
        int mid = l + (r - l) / 2;
        if(L <= mid) res = min(res, query_min(L, R, ls(o), l, mid));
        if(R > mid) res = min(res, query_min(L, R, rs(o), mid + 1, r));
        return res;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<vector<int>> pos(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]].push_back(i);
    }
    int ans = -inf, c = 0;
    vector<int> b(n + 1);
    for(int i = 1; i <= n; i++) {
        for(int j : pos[i]) {
            b[++c] = j;
        }
    }
    SegmentTree tr(n + 2);
    for(int i = 2; i <= n + 1; i++) tr.add(i, i, 1, 1, n + 1, i - 1);
    auto ck = [&](int j) -> bool {
        return tr.query_max(j + 1, n + 1, 1, 1, n + 1) >= tr.query_min(1, j, 1, 1, n + 1);
    };
    for(int i = 1, j = 1; i <= n; i++) {
        while(j <= n && !ck(b[j])) j++;
        if(j > n) break;
        ans = max(ans, i - a[b[j]]);
        for(int p : pos[i]) {
            tr.add(p + 1, n + 1, 1, 1, n + 1, -2);
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
