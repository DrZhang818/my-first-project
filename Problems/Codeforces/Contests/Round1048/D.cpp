#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class FenwickTree {
private:
    vector<int> tree;
    int n;
public:
    FenwickTree(int x) {
        tree.resize(x + 1);
        n = x;
    }
    void add(int i, int x) {
        while(i <= n) {
            tree[i] = max(tree[i], x);
            i += i & -i;
        }
    }
    int query(int i) {
        int res = 0;
        while(i > 0) {
            res = max(res, tree[i]);
            i -= i & -i;
        }
        return res;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> pre(n + 1);
    vector<int> stk(n + 1);
    int c = 0;
    for(int i = 1; i <= n; i++) {
        while(c && a[stk[c]] < a[i]) {
            c--;
        }
        if(c) {
            pre[i] = stk[c];
        }
        stk[++c] = i;
    }
    FenwickTree tr(n);
    vector<int> L(n + 1);
    for(int i = 1; i <= n; i++) {
        L[i] = max(L[i - 1], tr.query(n - a[i] + 1));
        tr.add(n - a[i] + 1, pre[i]);
    }
    while(q--) {
        int l, r;
        cin >> l >> r;
        if(L[r] >= l) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
