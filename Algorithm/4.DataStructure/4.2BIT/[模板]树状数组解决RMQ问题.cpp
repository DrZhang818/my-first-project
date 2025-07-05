#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


inline int lowbit(int x) {
    return x & -x;
}
vector<int> tree;
vector<int> a;
int n;
void update(int o, int x) {
    tree[o] = x;
    for(; o <= n; o += lowbit(o)) {
        for(int i = 1; i < lowbit(o); i <<= 1) {
            tree[o] = max(tree[o], tree[o - i]);
        }
    }
}
int query(int l, int r) {
    int res = 0;
    while(l <= r) {
        res = max(res, a[r]);
        r--;
        while(r - l >= lowbit(r)) {
            res = max(res, tree[r]);
            r -= lowbit(r);
        }
    }
    return res;
}
void solve() { 
    int q;
    cin >> n >> q;
    a.resize(n + 1);
    tree.resize(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        update(i, a[i]);
    }
    while(q--) {
        int x, y;
        cin >> x >> y;
        cout << query(x, y) << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
