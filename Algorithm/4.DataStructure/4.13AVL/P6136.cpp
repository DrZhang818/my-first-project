#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

struct AVL {
    struct Node {
        int l = 0, r = 0;
        int v, h = 1, cnt = 1;
        int sz = 1;
    };

    vector<Node> tr;
    int root = 0;

    AVL(int n = 0) {
        tr.reserve(n + 1);
        tr.push_back({0, 0, 0, 0, 0, 0});
    }

    int newNode(int v) {
        tr.push_back({0, 0, v, 1, 1, 1});
        return tr.size() - 1;
    }

    int height(int u) {
        return tr[u].h;
    }

    int size(int u) {
        return tr[u].sz;
    }

    void pull(int u) {
        tr[u].h = max(height(tr[u].l), height(tr[u].r)) + 1;
        tr[u].sz = size(tr[u].l) + size(tr[u].r) + tr[u].cnt;
    }

    int rotateRight(int u) {
        int q = tr[u].l;
        tr[u].l = tr[q].r;
        tr[q].r = u;
        pull(u);
        pull(q);
        return q;
    }

    int rotateLeft(int u) {
        int q = tr[u].r;
        tr[u].r = tr[q].l;
        tr[q].l = u;
        pull(u);
        pull(q);
        return q;
    }

    int balance(int u) {
        if(!u) return 0;
        if(height(tr[u].l) - height(tr[u].r) > 1) {
            if(height(tr[tr[u].l].l) >= height(tr[tr[u].l].r)) {
                return rotateRight(u);
            } else {
                tr[u].l = rotateLeft(tr[u].l);
                return rotateRight(u);
            }
        } else if(height(tr[u].r) - height(tr[u].l) > 1) {
            if(height(tr[tr[u].r].r) >= height(tr[tr[u].r].l)) {
                return rotateLeft(u);
            } else {
                tr[u].r = rotateRight(tr[u].r);
                return rotateLeft(u);
            }
        }
        pull(u);
        return u;
    }

    int add(int u, int v) {
        if(!u) {
            return newNode(v);
        }
        if(v == tr[u].v) {
            tr[u].cnt++;
        } else if(v < tr[u].v) {
            tr[u].l = add(tr[u].l, v);
        } else {
            tr[u].r = add(tr[u].r, v);
        }
        pull(u);
        return balance(u);
    }

    int remove(int u, int v) {
        if(!u) return 0;
        if(v < tr[u].v) {
            tr[u].l = remove(tr[u].l, v);
        } else if(v > tr[u].v) {
            tr[u].r = remove(tr[u].r, v);
        } else {
            if(tr[u].cnt > 1) {
                tr[u].cnt--;
            } else {
                if(!tr[u].l || !tr[u].r) {
                    u = tr[u].l ? tr[u].l : tr[u].r;
                    return u;
                } else {
                    int q = tr[u].r;
                    while(tr[q].l) q = tr[q].l;
                    tr[u].v = tr[q].v;
                    tr[u].cnt = tr[q].cnt;
                    tr[q].cnt = 1;
                    tr[u].r = remove(tr[u].r, tr[u].v);
                }
            }
        }
        pull(u);
        return balance(u);
    }

    int getRank(int u, int v) {
        if(!u) return 1;
        if(v == tr[u].v) return size(tr[u].l) + 1;
        if(v < tr[u].v) return getRank(tr[u].l, v);
        return size(tr[u].l) + tr[u].cnt + getRank(tr[u].r, v);
    }

    int getKth(int u, int k) {
        if(!u) return -1;
        if(k <= size(tr[u].l)) return getKth(tr[u].l, k);
        if(k <= size(tr[u].l) + tr[u].cnt) return tr[u].v;
        return getKth(tr[u].r, k - size(tr[u].l) - tr[u].cnt);
    }

    int getPrev(int v) {
        int u = root;
        int res = INT_MIN;
        while(u) {
            if(tr[u].v < v) {
                res = tr[u].v;
                u = tr[u].r;
            } else {
                u = tr[u].l;
            }
        }
        return res;
    }

    int getNext(int v) {
        int u = root;
        int res = INT_MAX;
        while(u) {
            if(tr[u].v > v) {
                res = tr[u].v;
                u = tr[u].l;
            } else {
                u = tr[u].r;
            }
        }
        return res;
    }

    void add(int v) { root = add(root, v); }
    void remove(int v) { root = remove(root, v); }
    int rank(int v) { return getRank(root, v); }
    int kth(int k) { return getKth(root, k); }
};

void solve() {
    int n, q;
    cin >> n >> q;
    AVL tr(n + q);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        tr.add(x);
    }
    int last = 0;
    int ans = 0;
    while(q--) {
        int op, x;
        cin >> op >> x;
        x ^= last;
        if(op == 1) {
            tr.add(x);
        } else if(op == 2) {
            tr.remove(x);
        } else if(op == 3) {
            ans ^= (last = tr.rank(x)); 
        } else if(op == 4) {
            ans ^= (last = tr.kth(x));
        } else if(op == 5) {
            ans ^= (last = tr.getPrev(x));
        } else {
            ans ^= (last = tr.getNext(x));
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