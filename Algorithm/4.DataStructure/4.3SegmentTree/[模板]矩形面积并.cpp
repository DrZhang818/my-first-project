#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://www.luogu.com.cn/problem/P5490
/*
    扫描线 || 线段树
    题意:
        求n个平行于坐标轴的矩形的面积并
        矩形信息由4个整数x1,y1,x2,y2描述, 代表左下和右上端点坐标
        范围: n∈[1,1e5], x,y∈[0,1e9]
    关键思考:
        本题为数据结构类题目, 需要读请题意, 选用合适的算法和数据结构维护题目信息, 回答询问
        本题的难点在于如何处理好重叠面积, 可以利用扫描线算法结合线段树来处理
        扫描线算法是一根平行于x轴的直线从下向上进行扫描, 线段树在这里的作用是
        对扫到的区间添加tag来标记是否处于矩形中
        由于添加tag只会发生在矩形的入边/出边时刻, 因此我们可以把矩阵的入/出整理成一个个事件
        并把事件按照y轴位置(扫描的时间先后)从小到大排序
        每次扫完一个事件后, 查询当前处于矩形中的长度, 而宽度就是当前事件与下一事件间的Δy
        比较复杂的是这里的离散化技巧
        由于x的范围很大, 我们必须对x的坐标进行离散化, 思考这里应该如何离散化
        考虑以下情景:
        X : 10 20 30 50 80 90
        i : 1  2  3  4  5  6
        如果我们把坐标一一映射, 那么[10,30]对应[1,3], [50,80]对应[4,5]
        我们会发现[30,50]中间的空挡消失了, 于是我们可以用一个非常实用的离散化技巧
        ————右端点偏移法
        我们在传参的时候将右端点左移, 在计算的时候将右端点右移
        也就是把[1,30]离散化成[1,2], 把[50,80]离散化成[4,4]
        这样我们就会发现, 30和50中间出现了空挡————3这个数字就是二者中间的空挡
        从而正确地把稀疏的坐标离散化成了稠密的坐标
        接下来介绍下线段树的核心部分
        update函数
        与以往的Lazy-Tag不同的是, 这里并不需要下发懒标记
        在与查询的[L,R]完全重合的区间标记cnt
        对于部分重合的情况, 分别递归左右子节点, 最后通过push_up更新结果
        push_up函数
        根据当前节点的cnt值判断是否整个区间被覆盖
        如果完全覆盖, 则长度为该区间的真实长度, 否则长度为左右子节点覆盖长度的和
        总结来说, 矩形面积并的信息维护只需要做好两件事:
        (1)打标记
            只给完全覆盖的区间打上对应事件的标记
        (2)更新区间在矩形内的长度
            分完全覆盖和不完全覆盖进行更新
        查询时候, 每两根扫描线直接进行一次查询, 只需要查询tr[1]的长度就是全部有效长度
        更新答案, 即长×宽即可, 长是tr[1], 宽是两根扫描线间的Δy
        思考: 为什么这样不会算重复面积
        答: Δy = 0的时候更新的答案也为0, 相当于没有更新
            只有Δy不为0, 也就是扫描处理完了所有y = y0的事件之后才会进行更新答案
            而此时由于全部处理完, 做到了不漏, 只更新一次, 做到了不重
            不重不漏, 得到的答案自然是正确的
*/
struct line {
    int x1, x2, y, tag;
    friend bool operator < (const line &a, const line &b) {
        return a.y < b.y;
    }
};
struct node {
    int cnt, len;
};
vector<line> L;
vector<node> tr;
vector<int> X;

inline int ls(int o) { return o << 1; }
inline int rs(int o) { return o << 1 | 1; }
void push_up(int o, int l, int r) {
    if(tr[o].cnt) tr[o].len = X[r + 1] - X[l];
    else tr[o].len = tr[ls(o)].len + tr[rs(o)].len;
    cerr << "l : " << X[l] << " r : " << X[r + 1] << " len : " << tr[o].len << " cnt : " << tr[o].cnt << "\n";
}
void update(int L, int R, int o, int l, int r, int tag) {
    if(L <= l && r <= R) {
        tr[o].cnt += tag;
    } else {
        int mid = l + r >> 1;
        if(L <= mid) update(L, R, ls(o), l, mid, tag);
        if(R > mid) update(L, R, rs(o), mid + 1, r, tag);
    }
    push_up(o, l, r);
}
void solve() { 
    int n;
    cin >> n;
    int eventCnt = n * 2;
    L.assign(eventCnt + 1, line());
    tr.assign(eventCnt * 8, node());
    X.assign(eventCnt + 1, 0);
    for(int i = 1; i <= n; i++) {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        L[i] = {x1, x2, y1, 1};
        L[n + i] = {x1, x2, y2, -1};
        X[i] = x1;
        X[n + i] = x2;
    }
    sort(L.begin() + 1, L.end());
    sort(X.begin() + 1, X.end());
    X.erase(unique(X.begin() + 1, X.end()), X.end());
    int m = X.size() - 1;
    
    ll ans = 0;
    for(int i = 1; i < eventCnt; i++) {
        int l = lower_bound(X.begin() + 1, X.end(), L[i].x1) - X.begin();
        int r = lower_bound(X.begin() + 1, X.end(), L[i].x2) - X.begin();
        cerr << "l : " << L[i].x1 << " r : " << L[i].x2 << "\n";
        update(l, r - 1, 1, 1, m - 1, L[i].tag);
        ans += (ll)tr[1].len * (L[i + 1].y - L[i].y);
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
