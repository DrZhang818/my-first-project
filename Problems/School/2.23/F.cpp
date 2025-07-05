#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


struct node {
    int l, r, val, li, ri;
    node() : l(0), r(0), val(0), li(0), ri(0) {}
};
void solve() { 
    int n;
    cin >> n;
    vector<node> a(2 * n + 1);
    vector<int> leaf(n + 1);
    vector<int> help(n + 1);
    int idx = 1, id = 1;;
    auto dfs = [&](auto &&dfs, int i) -> void {
        int x;
        cin >> x;
        if(x == 0) {
            a[i].l = ++idx;
            dfs(dfs, idx);
            a[i].r = ++idx;
            dfs(dfs, idx);
            a[i].li = a[a[i].l].li;
            a[i].ri = a[a[i].r].ri;
        } else {
            a[i].val = x;
            a[i].li = a[i].ri = id;
            leaf[id] = x;
            id++;
        }
    };
    dfs(dfs, 1);
    auto work = [&](auto &&work, int i) -> ll {
        if(!a[i].l && !a[i].r) {
            return 0;
        }
        ll ans = 0, tmp = 0;
        ans += work(work, a[i].l);
        ans += work(work, a[i].r);
        int l1 = a[a[i].l].li, r1 = a[a[i].l].ri, l2 = a[a[i].r].li, r2 = a[a[i].r].ri;
        ll n = r1 - l1 + 1, m = r2 - l2 + 1;
        int t = l2;
        for(; l1 <= r1; l1++) {
            while(l2 <= r2 && leaf[l2] < leaf[l1]) {
                l2++;
            }
            tmp += l2 - t;
        }
        ll tot = n * m;
        tmp = min(tmp, tot - tmp);
        ans += tmp;
        l1 = a[a[i].l].li, r1 = a[a[i].l].ri, l2 = a[a[i].r].li, r2 = a[a[i].r].ri;
        int idx = 0;
        while(l1 <= r1 && l2 <= r2) {
            if(leaf[l1] < leaf[l2]) help[idx++] = leaf[l1++];
            else help[idx++] = leaf[l2++];
        }
        while(l1 <= r1) help[idx++] = leaf[l1++];
        while(l2 <= r2) help[idx++] = leaf[l2++];
        l1 = a[a[i].l].li, r1 = a[a[i].l].ri, l2 = a[a[i].r].li, r2 = a[a[i].r].ri;
        for(int i = l1; i <= r2; i++) leaf[i] = help[i - l1];
        return ans;
    };
    ll ans = work(work, 1);
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    