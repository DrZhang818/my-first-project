#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

void add_mod(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;    
}

class FenwickTree {
private:
    vector<int> tree;
    int n;
public:
    FenwickTree(int x) {
        tree.resize(x + 2);
        n = x + 1;
    }
    void add(int i, int x) {
        i++;
        while(i <= n) {
            add_mod(tree[i], x);
            i += i & -i;
        }
    }
    int query(int i) {
        i++;
        int res = 0;
        while(i > 0) {
            add_mod(res, tree[i]);
            i -= i & -i;
        }
        return res;
    }
    int range_query(int l, int r) {
        return ((query(r) - query(l - 1)) % MOD + MOD) % MOD;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int ans = 1;
    vector<FenwickTree> row(n + 1, FenwickTree(n)), col(n + 1, FenwickTree(n));
    for(int i = 1; i <= n; i++) {
        for(int mx = a[i] + 1; mx <= n; mx++) {
            int v = row[mx].range_query(0, a[i]);
            row[mx].add(a[i], v);
            col[a[i]].add(mx, v);
            add_mod(ans, v);
        }
        for(int x = 0; x < a[i]; x++) {
            int v = col[x].range_query(x + 1, a[i]);
            row[a[i]].add(x, v);
            col[x].add(a[i], v);
            add_mod(ans, v);
        }
        row[a[i]].add(0, 1);
        col[0].add(a[i], 1);
        add_mod(ans, 1);
    }
    cout << ans << "\n";
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
