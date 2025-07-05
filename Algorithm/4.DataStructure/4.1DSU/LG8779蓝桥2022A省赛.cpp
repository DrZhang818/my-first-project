#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://www.luogu.com.cn/problem/P8779
/*
    题意:
        给定一个长度为n的数组, 现给定m条信息和q次询问
        每条信息为: 给定l,r,S, 表示a[l] + ... + a[r] = S
        每条询问为: 给定l,r, 回答a[l] + ... + a[r]的值
        范围: 1 <= n,m,q <= 1e5, S[i]∈[-1e12, 1e12], l,r∈[1,n]
        如果询问的答案无法确定, 输出UNKNOWN, 保证没有矛盾数据
    关键思考:
        本题为数据结构类题目, 需要选择高效的数据结构维护信息
        可以把a[l] + ... + a[r]看作点l到点r+1的距离(即a[l]表示连接l和l+1的边权)
        这样就相当于建立m条边构建起k棵树, 每棵树内部两点间的距离是可以计算的
        两颗不同的树之间的节点距离无法计算, 如果节点不存在于任何一颗树上也无法计算
        建边 + 合并 + 查询树上两点间的距离
        这些操作可以通过"带权并查集"来高效实现
        合并 + 查询的操作均为O(α(n))
        因此最终时间复杂度为O((m + q) * α(n)), 可以通过本题
        需要注意的点是, find方法里面需要先用temp存储fa[x], 在fa[x]修改正确后再修改d[x]
        merge和query的方法可以按照"盖斯定律"来理解
        merge的核心是把两个根节点的距离计算出来
            d(r1,r2) = d(r1,x) + d(x,y) + d(y,r2) = d(y,r2) - d(x,r1) + d(x,y)
        query的核心是利用x,y到根节点的距离来计算出x,y之间的距离
            即d(x,y) = d(x,root) + d(root,y) = d(x,root) - d(y,root)
*/
class DSU {
    vector<int> fa;
    vector<ll> d;
public:
    DSU(int n) {
        fa.resize(n);
        iota(fa.begin(), fa.end(), 0);
        d.assign(n, 0LL);
    }
    int find(int x) {
        if(x != fa[x]) {
            int temp = fa[x];
            fa[x] = find(fa[x]);
            d[x] += d[temp];
        }
        return fa[x];
    }
    void merge(int x, int y, ll v) {
        y += 1;
        int fx = find(x);
        int fy = find(y);
        if(fx == fy) return;
        fa[fx] = fy;
        d[fx] = d[y] - d[x] + v;
    }
    ll query(int x, int y) {
        y += 1;
        int fx = find(x);
        int fy = find(y);
        if(fx != fy) {
            return LLONG_MAX;
        }
        return d[x] - d[y];
    }
};
void solve(){ 
    int n, m, q;
    cin >> n >> m >> q;
    DSU g(n + 1);
    for(int i = 0; i < m; i++) {
        int x, y;
        ll v;
        cin >> x >> y >> v;
        x--, y--;
        g.merge(x, y, v);
    }
    while(q--) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        ll ans = g.query(x, y);
        if(ans == LLONG_MAX) {
            cout << "UNKNOWN\n";
        } else {
            cout << ans << "\n";
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
    
