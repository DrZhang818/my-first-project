#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://www.luogu.com.cn/problem/P3740
/*
    线段树
    题意:
        有一堵墙由N个单位的格子组成, 现在要在墙上按照顺序贴海报
        一共贴M张海报, 每张海报以A B表示, 代表覆盖第A个格子到第B个格子(可能>N)
        后贴的海报会覆盖原来格子上的海报
        回答贴完所有海报后, 在这堵墙上能看见多少个海报 
        范围: N∈[10, 1e7], M∈[1,1000], A,B∈[1,1e7]
    关键思考:
        本题为数据结构类题目, 需要读请题意, 选用合适的算法和数据结构维护题目信息, 回答询问
        首先要理解好格子是什么意思, 第一个格子对应的区间是[1,2], 第二个是[2,3]...
        题目输入数据给的是第A~第B个格子, 对于覆盖的区间是[A,B+1]
        因此如果我们使用点线段树(每个节点代表坐标轴上的一个点), 需要处理好区间实际范围
        而相比而言, 区间线段树更适合本题(每个节点代表一个长度为1的格子)
        不难发现, 本题可以转化为线段树染色问题, 只涉及到简单的区间修改和单次区间查询
        本题的难点在于离散化的trick, 试想一下情景
        [1,300], [1,100], [200,300]
        处理完之后能看见几张呢? 显然是3张
        但如果我们离散化为[1,4], [1,2], [3,4]
        我们会发现, 竟然神奇地消失了一个海报
        这是因为我们把原本不连续的海报100,200, 离散化成了离散的2,3
        解决办法就是插点, 在非连续的区间直接插入一个区间, 连续的区间之间无需插点
        具体实现见下文代码实现
        另外注意A,B是会大于N的, 因此我们需要把N也加入pos中进行离散化, 查询时只查1~N
*/
struct info {
    int l, r;
};
vector<info> a;
vector<int> tag;
set<int> st;
inline int ls(int o) { return o << 1; }
inline int rs(int o) { return o << 1 | 1; }
void addtag(int o, int l, int r, int d) {
    tag[o] = d;
}
void push_down(int o, int l, int r) {
    if(tag[o]) {
        int mid = l + r >> 1;
        addtag(ls(o), l, mid, tag[o]);
        addtag(rs(o), mid + 1, r, tag[o]);
        tag[o] = 0;
    }
}
void update(int L, int R, int o, int l, int r, int d) {
    if(L <= l && r <= R) {
        addtag(o, l, r, d);
        return;
    }
    push_down(o, l, r);
    int mid = l + r >> 1;
    if(L <= mid) update(L, R, ls(o), l, mid, d);
    if(R > mid) update(L, R, rs(o), mid + 1, r, d);
}
void push_downAll(int L, int R, int o, int l, int r) {
    if(r < L || l > R) return;
    if(l == r || tag[o]) {
        if(tag[o]) {
            st.insert(tag[o]);
        }
        return;
    }
    int mid = l + r >> 1;
    push_downAll(L, R, ls(o), l, mid);
    push_downAll(L, R, rs(o), mid + 1, r);
}
int query(int L, int R, int o, int l, int r) {
    push_downAll(L, R, o, l, r);
    return (int)st.size();
}
void solve() {  
    int n, q;
    cin >> n >> q;
    a.resize(q + 1);
    vector<int> pos;
    pos.push_back(n);
    pos.reserve(2 * q);
    for(int i = 1; i <= q; i++) {
        cin >> a[i].l >> a[i].r;
        pos.push_back(a[i].l);
        pos.push_back(a[i].r);
    }
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
    unordered_map<int,int> mp;
    int cnt = 1;
    for(int i = 0; i < pos.size(); i++) {
        if(i && pos[i] != pos[i - 1] + 1) cnt++;
        mp[pos[i]] = cnt++; 
    }
    tag.assign(cnt << 2, 0);
    for(int i = 1; i <= q; i++) {
        auto [l, r] = a[i];
        l = mp[l];
        r = mp[r];
        update(l, r, 1, 1, cnt, i);
    }
    int R = mp[n];
    cout << query(1, R, 1, 1, cnt) << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    solve();
    return 0;
}
    
