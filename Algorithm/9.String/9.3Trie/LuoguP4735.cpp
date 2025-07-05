#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct node {
    int son[2];
    vector<int> idx;
};
vector<node> tr;
vector<int> a;
int nxt(int u, int v) {
    if(tr[u].son[v] == 0) tr.push_back(node()), tr[u].son[v] = tr.size() - 1;
    return tr[u].son[v];
}
void add(int x, int id) {
    int u = 0;
    for(int i = 30; i >= 0; i--) {
        int v = (x >> i & 1);
        u = nxt(u, v);
        tr[u].idx.push_back(id);
    }
}
bool ck(vector<int> &idx, int l, int r) {
    auto it = lower_bound(idx.begin(), idx.end(), l);
    if(it != idx.end() && *it <= r) return true;
    return false;
}
int query(int l, int r, int x) {
    int ans = 0, u = 0;
    for(int i = 30; i >= 0; i--) {
        int v = (x >> i & 1);
        if(ck(tr[tr[u].son[v^1]].idx, l, r)) {
            u = tr[u].son[v^1];
            ans += (1 << i);
        } else {
            u = tr[u].son[v];
        }
    }
    return ans;
}
void solve() {
    int n, q;
    cin >> n >> q;
    a.resize(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] ^= a[i - 1];
    }
    tr.push_back(node());
    for(int i = 0; i <= n; i++) add(a[i], i);
    while(q--) {
        char op;
        cin >> op;
        if(op == 'A') {
            int x; cin >> x;
            x ^= a.back();
            a.push_back(x);
            add(x, a.size() - 1);
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            int u = a.back() ^ x;
            cout << query(l - 1, r - 1, u) << "\n";
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
