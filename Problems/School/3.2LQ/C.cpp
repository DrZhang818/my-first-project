#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


struct info {
    ll val;
    int id;
};
int find(vector<int> &fa, int x) {
    if(x != fa[x]) {
        fa[x] = find(fa, fa[fa[x]]);
    }
    return fa[x];
}
bool merge(vector<int> &fa, int u, int v) {
    int fu = find(fa, u);
    int fv = find(fa, v);
    if(fu == fv) return false;
    fa[fu] = fv;
    return true;
}

void solve() { 
    int n;
    cin >> n;
    vector<int> fa(n + 1);
    iota(fa.begin(), fa.end(), 0);
    vector<info> a(n + 2);
    a[0].id = -1, a[0].val = -LLONG_MAX / 2;
    a[n + 1].id = -1, a[n + 1].val = LLONG_MAX / 2;
    for(int i = 1; i <= n; i++) {
        cin >> a[i].val;
        a[i].id = i;
    }
    sort(a.begin() + 1, a.end() - 1, [](auto &a, auto &b) -> bool{
        return a.val < b.val;
    });
    vector<ll> res(n + 1);
    for(int i = 1; i <= n; i++) {
        if(a[i].val - a[i - 1].val <= a[i + 1].val - a[i].val) {
            if(!merge(fa, i, i - 1)) {
                res[i] = (a[i - 1].val + a[i].val) / 2;
            }
        } else {
            merge(fa, i, i + 1);
        }
    }
    vector<ll> ans(n + 1);
    for(int i = 1; i <= n; i++) {
        int u = find(fa, i);
        ans[a[i].id] = res[u];
    }
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
