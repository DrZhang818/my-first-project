#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://www.luogu.com.cn/problem/P2082
/*
    贪心
    题意:
        给定N个区间, 每个区间覆盖[l,r]范围内的整点
        求最终有多少个整点被至少一个区间覆盖
        范围: N∈[1,1e5], l,r∈[1,1e17]
    关键思考:
        本题为数据结构类题目, 需要读请题意, 选用合适的算法和数据结构维护题目信息, 回答询问
        首先观察题目性质, 很容易发现, 如果任意两个区间都没有交集, 那么答案就是
        ∑len[i], 主要的难点就在于"如何处理有交集的区间"
        设两个有交集的区间A和B
            两个区间有交集等价于A.l <= B.r && B.l <= A.r
            我们会发现, 这两个区间计算后的结果等价于它们合并成一个大区间后的计算结果
            即等价于区间[min(A.l,B.l), max(A.r,B.r)]的计算结果
        因此我们会发现问题就转化成了"区间合并"问题, 只要把这N个区间做一次区间合并
        就可以转化成任意两个区间没有交集的情况, 进而累加答案即可
        下面介绍静态下的区间合并算法: 按左端点排序贪心
        现在要解决的问题是: 对于最小的左端点, 找到它的最大右端点
        我们用变量r记录合并后区间的右端点
        用一个变量l记录合并后的区间左端点
        接下来贪心地按照左端点升序来处理这些区间
        这样在遍历到第i条线段时, 我们保证了所有左端点小于当前线段左端点的线段
        均已被更新过
        (1)这样如果a[i].l > r, 那么第i条线段一定无法被合并到前面的区间
        因为后面所有的线段左端点都 >= a[i].l, 而前面的区间的r < a[i].l
        这意味着不存在任何一条线段可以将当前线段与前面的连接起来, 那这两个就是独立的
        (2)如果a[i].l <= r, 那么第i条线段一定会被合并到前面的区间
        此时l不变, 更新r = max(r, a[i].r)
        下面思考: 为什么要按左端点排序呢?
        这主要是因为我们的问题是对于最小的左端点, 找到最大右端点
        因此千万不可错写成按右端点升序排序, 否则会出现[1,2], [4,5], [1,10]这样的hack数据            
*/
struct info {
    ll l, r;
    friend bool operator < (const info &a, const info &b) {
        if(a.l != b.l) return a.l < b.l;
        return a.r < b.r;
    }
};
void solve() { 
    int n;
    cin >> n;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].l >> a[i].r;
    } 
    sort(a.begin() + 1, a.end());
    if(n == 0) { cout << 0 << "\n"; return; }
    ll l = a[1].l, r = a[1].r;
    vector<info> res;
    for(int i = 1; i <= n; i++) {
        if(a[i].l > r) {
            res.push_back({l, r});
            l = a[i].l, r = a[i].r;
        } else {
            r = max(r, a[i].r);
        }
    }
    res.push_back({l, r});
    ll ans = 0;
    for(int i = 0; i < res.size(); i++) {
        ans += res[i].r - res[i].l + 1;
    }
    cout << ans << "\n";
}
//进阶: 动态插入 + 查询
/*
    如果需要动态插入区间, 就需要使用进阶的方法
    利用set来维护
    具体原理为:
        对于新插入的区间A, 我们需要在set中查找最后一个满足左端点≤r的区间
        如果这个区间右端点 >= A.l, 则可以合并 
*/
set<info> st;
void add(info o) {
    info res = o;
    auto it = st.lower_bound({res.l, -inf});
    if(it != st.begin()) {
        auto pre = prev(it);
        if(pre->r >= res.l) it = pre;
    }
    while(it != st.end() && it->l <= res.r) {
        res.l = min(res.l, it->l);
        res.r = max(res.r, it->r);
        it = st.erase(it);
    }
    st.insert(res);
}
void solve1() {
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        ll L, R;
        cin >> L >> R;
        add({L, R});
    }
    ll ans = 0;
    for(auto [L,R] : st) {
        ans += R - L + 1;
    }
    cout << ans << "\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve1();
    return 0;
}
    
