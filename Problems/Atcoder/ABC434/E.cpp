#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

vector<int> fa, cntx, cnt;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if(u == v) {
        return;
    }
    fa[v] = u;
    cnt[u] += cnt[v];
}
void init(int n) {
    fa.assign(3 * n + 1, {});
    cntx.assign(n + 1, {});
    cnt.assign(3 * n + 1, 1);
    iota(fa.begin(), fa.end(), 0);
}
void solve() {
    int n;
    cin >> n;
    init(n);
    map<int,int> mp;
    int sz = n;
    for(int i = 1; i <= n; i++) {
        int x, r;
        cin >> x >> r;
        if(!mp.contains(x - r)) {
            mp[x - r] = ++sz;
        }
        if(!mp.contains(x + r)) {
            mp[x + r] = ++sz;
        }
        merge(i, mp[x - r]);
        merge(i, mp[x + r]);
    }

    int ans = 0;
    for(int i = 1; i <= n; i++) {
        cntx[find(i)] += 1;
    }
    for(int i = 1; i <= n; i++) {
        if(i == find(i)) {
            ans += min(cntx[i], cnt[i] - cntx[i]);
        }
    }
    cout << ans << "\n";
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
