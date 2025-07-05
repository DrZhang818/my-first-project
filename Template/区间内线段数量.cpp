#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;



/*
    树状数组
    题意:
        给定N条线段[L,R], 有Q次询问
        每次询问给定l,r, 分别回答区间[l,r]内两种覆盖的线段数量
        (1)允许不完全覆盖数量  
        (2)完全覆盖数量
        N∈[1,1e5], L,R∈[1,1e5], Q∈[1,1e5]


*/ 
int n;
vector<int> t1(100005), t2(100005);
void add(vector<int> &a, int i) {
    for(; i <= 100000; i += i & -i) a[i]++;
}
int query(vector<int> &a, int i) {
    int res = 0;
    for(; i > 0; i -= i & -i) res += a[i];
    return res;
}
struct info {
    int l, r;
};
struct Q {
    int l, r, id;
};
void solve() { 
    int q;
    cin >> n >> q;
    vector<info> seg(n + 1);
    for(int i = 1; i <= n; i++) {
        int l, r;
        cin >> l >> r;
        seg[i] = {l, r};
    }   
    vector<Q> que(q + 1);
    for(int i = 1; i <= q; i++) {
        int l, r;
        cin >> l >> r;
        que[i] = {l, r, i};
    }
    sort(que.begin() + 1, que.end(), [](auto &a, auto &b) -> bool {
        return a.r < b.r;
    });
    sort(seg.begin() + 1, seg.end(), [](auto &a, auto &b) -> bool {   
        return a.r < b.r;
    });
    vector<int> ans2(q + 1);
    int idx = 1;
    for(int i = 1; i <= q; i++) {
        auto [l, r, id] = que[i];
        while(idx <= n && seg[idx].r <= r) {
            add(t1, seg[idx].l);
            add(t2, seg[idx].r);
            idx++;
        }
        int ans = query(t2, r) - query(t1, l - 1);
        ans2[id] = ans;
    }
    for(int i = 1; i <= q; i++) {
        cout << ans2[i] << " \n"[i == q];
    }
    for(; idx <= n; idx++) {
        add(t1, seg[idx].l);
        add(t2, seg[idx].r);
    }
    vector<int> ans1(q + 1);
    for(int i = 1; i <= q; i++) {
        auto [l, r, id] = que[i];
        int ans = query(t1, r) - query(t2, l - 1);
        ans1[id] = ans;
    }
    for(int i = 1; i <= q; i++) {
        cout << ans1[i] << " \n"[i == q];
    }
}   

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
