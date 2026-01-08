#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct FHQ {
    struct Node {
        int l = 0, r = 0, v = 0, sz = 0;
        unsigned int p = 0;
    };
    
    vector<Node> tr;
    int root = 0;

    FHQ(int n = 0) {
        tr.reserve(n + 1);
        tr.push_back({0, 0, 0, 0, 0});
    }

    int newNode(int v) {
        tr.push_back({0, 0, v, 1, (unsigned int)rng()});
        return tr.size() - 1;
    }

    void pull(int u) {
        tr[u].sz = tr[tr[u].l].sz + tr[tr[u].r].sz + 1;
    }

    void split(int u, int v, int &x, int &y) {
        if(!u) {
            x = y = 0;
            return;
        }
        if(tr[u].v <= v) {
            x = u;
            split(tr[u].r, v, tr[u].r, y);
        } else {
            y = u;
            split(tr[u].l, v, x, tr[u].l);
        }
        pull(u);
    }

    int merge(int u, int v) {
        if(!u || !v) return u | v;
        if(tr[u].p > tr[v].p) {
            tr[u].r = merge(tr[u].r, v);
            pull(u);
            return u;
        } else {
            tr[v].l = merge(u, tr[v].l);
            pull(v);
            return v;
        }
    }

    void add(int v) {
        int x, y;
        split(root, v, x, y);
        root = merge(merge(x, newNode(v)), y);
    }

    int kth(int k) {
        int u = root;
        while(u) {
            if(tr[tr[u].l].sz + 1 == k) return tr[u].v;
            if(tr[tr[u].l].sz >= k) {
                u = tr[u].l;
            } else {
                k -= tr[tr[u].l].sz + 1;
                u = tr[u].r;
            }
        }
        return -1;
    }

};

void solve() {  
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> cnt(m + 1);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    vector adj(n + 1, vector<int>{});
    vector<int> ccnt(n + 1);
    vector<ll> S(n + 1);
    for(int i = 1; i <= m; i++) {
        adj[cnt[i]].push_back(i);
        ccnt[cnt[i]]++;
        S[cnt[i]] += cnt[i];
    }
    
    vector<ll> Q(q + 1);
    vector<int> ans(q + 1);
    for(int i = 1; i <= q; i++) {
        cin >> Q[i];
    }

    vector<int> p(q);
    iota(p.begin(), p.end(), 1);
    sort(p.begin(), p.end(), 
        [&](auto x, auto y) {
            return Q[x] < Q[y];
        });

    int v = 0;
    ll sum = 0, c = 0;
    FHQ tr(m);
    for(int i : p) {
        ll need = Q[i] - n;
        while(v <= n) {
            ll nsum = sum + S[v];
            ll nc = c + ccnt[v];
            if(nc * v - nsum >= need) {
                break;
            }
            sum = nsum;
            c = nc;

            for(int u : adj[v]) {
                tr.add(u);
            }
            v++;
        }
        need -= c * (v - 1) - sum;
        if(v == n + 1) {
            ans[i] = 1 + (need - 1) % m;
        } else {
            ans[i] = tr.kth(need);
        }
    }
    for(int i = 1; i <= q; i++) {
        cout << ans[i] << "\n";
    }
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
