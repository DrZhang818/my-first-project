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
        ll sum = 0;
        unsigned int p = 0;
    };
    
    vector<Node> tr;
    int root = 0;

    FHQ(int n = 0) {
        tr.reserve(n + 1);
        tr.push_back({0, 0, 0, 0, 0});
    }

    int newNode(int v) {
        tr.push_back({0, 0, v, 1, v, (unsigned int)rng()});
        return tr.size() - 1;
    }

    void pull(int u) {
        tr[u].sz = tr[tr[u].l].sz + tr[tr[u].r].sz + 1;
        tr[u].sum = tr[tr[u].l].sum + tr[tr[u].r].sum + tr[u].v;
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

    void split_rank(int u, int k, int &x, int &y) {
        if(!u) {
            x = y = 0;
            return;
        }
        if(tr[tr[u].l].sz + 1 <= k) {
            x = u;
            split_rank(tr[u].r, k - tr[tr[u].l].sz - 1, tr[u].r, y);
        } else {
            y = u;
            split_rank(tr[u].l, k, x, tr[u].l);
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

    ll query(int &u, int k) {
        int n = tr[u].sz;
        if(k >= n) return tr[u].sum;
        if(k <= 0) return 0;
        int x, y;
        split_rank(u, n - k, x, y);
        ll res = tr[y].sum;
        u = merge(x, y);
        return res;
    }

    ll query(int k) {
        return query(root, k);
    }

    void add(int v) {
        int x, y;
        split(root, v, x, y);
        root = merge(merge(x, newNode(v)), y);
    }

    void remove(int v) {
        int x, y, z;
        split(root, v, x, z);
        split(x, v - 1, x, y);
        if(y) {
            y = merge(tr[y].l, tr[y].r);
        }
        root = merge(merge(x, y), z);
    }

    int rank(int v) {
        int x, y;
        split(root, v - 1, x, y);
        int res = tr[x].sz + 1;
        root = merge(x, y);
        return res;
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
    int n, q;
    cin >> n >> q;
    vector<int> A(n + 1), B(n + 1);
    FHQ tr(n + q);
    multiset<int> st;
    int cnt = 0;
    ll sum = 0;
    for(int i = 1; i <= n; i++) {
        cin >> A[i] >> B[i];
        sum += A[i];
        tr.add(A[i]);
        if(B[i] == 1) {
            st.insert(A[i]);
        } else {
            cnt++;
        }
    }

    while(q--) {
        int i, x, y;
        cin >> i >> x >> y;
        if(B[i] == 1) {
            auto it = st.lower_bound(A[i]);
            st.erase(it);
        } else {
            cnt--;
        }
        tr.remove(A[i]);
        sum -= A[i];

        A[i] = x;
        B[i] = y;
        if(B[i] == 1) {
            st.insert(A[i]);
        } else {
            cnt++;
        }
        tr.add(A[i]);
        sum += A[i];

        ll ans = sum;
        
        if(cnt) {
            ans += tr.query(cnt);
            int v = tr.kth(n - cnt + 1);
            if(st.empty()) {
                ans -= v;
            } else if(*st.rbegin() < v) {
                ans -= v;
                ans += *st.rbegin();
            }
        }

        cout << ans << "\n";
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
