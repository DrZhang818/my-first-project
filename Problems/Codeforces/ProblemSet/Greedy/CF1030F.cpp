#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

//https://codeforces.com/contest/1030/problem/F
/*
    数据结构 || 贪心 || 二分
    题意:
        给定两个长度为N的数组a和w, 保证a是严格递增数组
        数轴上有N个物品, 第i个物品的位置是a[i], 权重为w[i]
        定义f(L,R) := 把下标[L,R]中的物品排在一起且位置连续的最小带权距离和
        例如三个物品的位置分别为1,3,7, 若把物品分别移动到4,5,6, 则带权距离和为:
            |4-1|*w[1] + |5-3|*w[2] + |6-7|*w[3]
        你需要回答Q次询问, 每个询问包含两个数, 格式如下:
        "i nw": 把w[i]修改为nw
        "L R" : 输出f(L,R) % 1000000007
        用输入的第一个数区分这两种询问:
        如果第一个数是负数, 表示第一种询问, 把第一个数取相反数就是正确的i
        如果第一个数是正数, 表示第二种询问
        范围: N∈[1,2e5], Q∈[1,2e5], a[i]∈[1,1e9], w[i]∈[1,1e9]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先思考暴力做法, 对于每个第二种询问, 枚举[L,R]的每个位置, 时间复杂度为O(QNM), 超时
        瓶颈在于不能枚举位置并计算
        观察式子: ∑ |a[i] - (x + (i - L)) | * w[i], i∈[L,R]
                = ∑ |a[i] - i - (x - L) | * w[i]
        我们可以简化式子, 令a[i] = a[i] - i, x = x - L
        则变为 ∑ |a[i] - x| * w[i]
        我们知道, 对于最小化 ∑ |a[i] - x|这个问题有个简单贪心做法: 取 x 为数组a的中位数
        那么如何解决带权版本呢? 这就要求我们对中位数贪心有更本质的理解
        我们用一个数轴来辅助理解, 用.表示物品位置, Δ表示聚集的位置
        ____.___.____.____.____.___
                        Δ
        我们思考, 当Δ向左移动一格, 会带来什么变化?
        向左移动一格, 我们的总权值会减小∑w[i], 其中i满足a[i] < x
                     我们的总权值也会增加∑w[i], 其中i满足a[i] >= x
        因此权值变化为 ∑右w[i] - ∑左w[i]
        我们从左向右看, 就是要找到最后一个 ∑右w[i] - ∑左w[i] > 0的点
        这是简单的, 我们可以用树状数组维护单点修改和区间查询
        由于最后一个∑右w[i] - ∑左w[i] > 0的点x必然落在某个a[i]上, 因此我们可以二分查找i∈[L,R]
        求解∑ |a[i] - x| * w[i], 我们可以拆绝对值
        ∑右a[i]*w[i] - x∑右w[i] + x∑左w[i] - ∑左a[i]*w[i]
        开两棵树状数组即可, 注意∑w[i]这棵不能取模, 因为在二分查找时必须拿原数进行比大小
        这样的时间复杂度是O(Qlogn * logn)的, 可以通过题目
        
        我们还可以进一步优化到O(Qlogn), 方法是树状数组二分
        树状数组二分, 也称为树状数组倍增, 本质是利用树状数组的倍增结构查找 < X的最后一个位置
        我们要找最后一个 ∑右w[i] - ∑左w[i] > 0, 那么这个点满足什么性质呢?
        即 S(l,i) >= S(i + 1, r)
        作如下变形:
            S(l,i) >= S(r) - S(l - 1) - S(l,i)
            S(l,i) >= ceil((S(r) - S(l - 1)) / 2)
            S(l,i) >= (S(r) - S(l - 1) + 1) / 2
            S(l - 1) + S(l,i) >= S(l - 1) + (S(r) - S(l - 1) + 1) / 2
            S(i) >= (S(r) + S(l - 1) + 1) / 2
        因此我们可以利用倍增查到第一个 >= (S(r) + S(l - 1) + 1) / 2的位置
        这就是我们要选取的点
        时间复杂度为O(Qlogn)
*/
ll mod(ll x) {
    return (x % MOD + MOD) % MOD;
}
inline int lowbit(int o) { return o & -o; }
class BIT {
    vector<ll> tr;
    int n;
public:
    BIT(int n) : tr(n + 1), n(n) {}
    void add(int o, ll d) {
        for(int i = o; i <= n; i += lowbit(i)) {
            tr[i] += d;
        }
    }
    void add_mod(int o, ll d) {
        for(int i = o; i <= n; i += lowbit(i)) {
            tr[i] = (tr[i] + d) % MOD;
        }
    }
    ll query(int o) {
        ll res = 0;
        for(int i = o; i > 0; i -= lowbit(i)) {
            res += tr[i];
        }
        return res;
    }
    ll range_query(int l, int r) {
        return query(r) - query(l - 1);
    }
    int kth(ll k) {
        int cur = 0;
        for(int s = 17; s >= 0; s--) {
            int nxt = cur | 1 << s;
            if(nxt <= n && tr[nxt] < k) {
                cur = nxt;
                k -= tr[nxt];
            }
        }
        return cur + 1;
    }
    ll query_mod(int o) {
        ll res = 0;
        for(int i = o; i > 0; i -= lowbit(i)) {
            res = (res + tr[i]) % MOD;
        }
        return res;
    }
    ll range_query_mod(int l, int r) {
        return mod(query_mod(r) - query_mod(l - 1));
    }
};
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1), w(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] -= i;
    }
    for(int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    BIT tr1(n + 1), tr2(n + 1);
    for(int i = 1; i <= n; i++) {
        tr1.add(i, w[i]);
        tr2.add_mod(i, 1LL * w[i] * a[i] % MOD);
    }
    while(q--) {
        int x, y;
        cin >> x >> y;
        if(x < 0) {
            int o = -x;
            tr1.add(o, -w[o]);
            tr2.add_mod(o, mod(1LL * -w[o] * a[o]));
            w[o] = y;
            tr1.add(o, w[o]);
            tr2.add_mod(o, mod(1LL * w[o] * a[o]));
        } else {
            int l = tr1.kth((tr1.query(y) + tr1.query(x - 1) + 1) / 2);
            ll ans = 0;
            ans -= mod(tr2.range_query_mod(x, l - 1));
            ans += mod(tr2.range_query_mod(l, y));
            ans += mod(a[l] * mod(tr1.range_query(x, l - 1)));
            ans -= mod(a[l] * mod(tr1.range_query(l, y)));
            cout << mod(ans) << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
