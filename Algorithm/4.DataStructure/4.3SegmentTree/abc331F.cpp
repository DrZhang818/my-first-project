#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://atcoder.jp/contests/abc331/tasks/abc331_f
/*
    线段树 || 字符串哈希
    题意:
        给定一个长度为N的字符串S, 现在有Q次询问, 询问包含两种
        (1)给定一个位置x和一个字符c, 把S[x]修改为字符c
        (2)给定区间[L,R], 判断S[L:R]是否为回文串
        范围: N∈[1,1e6], Q∈[1,1e5]
    关键思考:
        本题为数据结构类题目, 需要读请题意, 选取合适的算法和数据结构高效维护题目信息, 回答询问
        带修的区间回文串询问, 可以使用线段树维护正反哈希来实现, 实质上是单点修改 + 区间查询
        (1)对于修改操作很容易实现, 只需要把那个点的Hash函数换成对应的字符c即可
        (2)对于查询操作是本题的难点, 因为push_up的操作不是简单的两个子节点相加
        而是等比数列相加, 这样一个子节点就要乘上相应的系数, 系数就是另一个子节点的区间长度
        为了代码逻辑简洁, 我们可以使用友元函数重载运算符 + 具体细节见代码实现
        另一个细节是query函数, 重载运算符之后的 + 不再具有交换律, 因此采用三段写法
        第三段return 的时候注意加法的顺序         
*/
constexpr ull P = 131;
int n, q;
vector<ull> pw;
struct node {
    int l, r;
    ull h1, h2;
    friend node operator + (const node &a, const node &b) {
        return {
            a.l,
            b.r,
            a.h1 * pw[b.r - b.l + 1] + b.h1,
            b.h2 * pw[a.r - a.l + 1] + a.h2
        };
    }
};
vector<node> tr;
string s;
inline int ls(int o) { return o << 1; }
inline int rs(int o) { return o << 1 | 1; }
void push_up(int o) {
    tr[o] = tr[ls(o)] + tr[rs(o)];
}
void build(int o, int l, int r) {
    tr[o].l = l, tr[o].r = r;
    if(l == r) {
        tr[o].h1 = tr[o].h2 = s[l];
        return;
    }
    int mid = l + r >> 1;
    build(ls(o), l, mid);
    build(rs(o), mid + 1, r);
    push_up(o);
}
void update(int pos, int o, int c) {
    if(tr[o].l == tr[o].r) {
        tr[o].h1 = tr[o].h2 = c;
        return;
    }
    int mid = tr[o].l + tr[o].r >> 1;
    if(pos <= mid) update(pos, ls(o), c);
    else update(pos, rs(o), c);
    push_up(o);
}
node query(int L, int R, int o) {
    if(L <= tr[o].l && tr[o].r <= R) return tr[o];
    int mid = tr[o].l + tr[o].r >> 1;
    if(R <= mid) return query(L, R, ls(o));
    if(L > mid) return query(L, R, rs(o));
    return query(L, R, ls(o)) + query(L, R, rs(o));
}
void solve() { 
    cin >> n >> q >> s;
    s = "#" + s;
    tr.resize(n << 2);
    pw.resize(n + 1, 0);
    pw[0] = 1;
    for(int i = 1; i <= n; i++) {
        pw[i] = pw[i - 1] * P;
    }
    build(1, 1, n);
    while(q--) {
        int flag;
        cin >> flag;
        if(flag == 1) {
            int x;
            char c;
            cin >> x >> c;
            update(x, 1, c);
        } else {
            int l, r;
            cin >> l >> r;
            node t = query(l, r, 1);
            if(t.h1 == t.h2) {
                cout << "Yes\n"; 
            } else {
                cout << "No\n";
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
