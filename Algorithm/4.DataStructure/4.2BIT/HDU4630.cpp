#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://acm.hdu.edu.cn/showproblem.php?pid=4630
/*
    离线处理 || 树状数组 || 数论
    题意: 
        给定一个长度为1~N的排列, 有Q组询问, 每组询问给出一个区间[L,R]
        你需要回答区间内任意两个数的最大公约数的最大值是多少
        范围: n∈[1,5e4], Q∈[1,5e4], L,R∈[1,n]
    关键思考:


*/
inline int lowbit(int x) { return x & -x; }
struct info {
    int l, r, id;
};
int n;
vector<int> tree;
void update(int i, int x) {
    for(; i <= n; i += lowbit(i)) {
        tree[i] = max(tree[i], x);
    }
}
int query(int i) {
    int res = 0;
    for(; i >= 1; i -= lowbit(i)) {
        res = max(res, tree[i]);
    }
    return res;
}
void solve() { 
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int q;
    cin >> q;
    vector<info> Q(q);
    for(int i = 0; i < q; i++) {
        cin >> Q[i].l >> Q[i].r;
        Q[i].id = i + 1;
    }
    vector<int> ans(q + 1);
    sort(Q.begin(), Q.end(), [&](auto x, auto y) -> bool {
        return x.l > y.l;
    });
    tree.assign(n + 1, 0);
    vector<int> pre(n + 1);
    int idx = n;
    for(auto [l, r, id] : Q) {
        while(idx >= l) {
            int x = a[idx];
            for(int i = 1; i <= sqrt(x); i++) {
                if(x % i == 0) {
                    if(pre[i]) update(pre[i], i);
                    if(pre[x / i]) update(pre[x / i], x / i);
                    pre[i] = idx;
                    pre[x / i] = idx;
                }
            }
            idx--;
        }
        ans[id] = query(r);
    }
    for(int i = 1; i <= q; i++) {
        cout << ans[i] << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
