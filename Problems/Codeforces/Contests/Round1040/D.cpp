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
            tree[i] += x;
            i += i & -i;
        }
    }
    int query(int i) {
        int res = 0;
        while(i > 0) {
            res += tree[i];
            i -= i & -i;
        }
        return res;
    }
    int range_query(int l, int r) {
        return query(r) - query(l - 1);
    }
};
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    FenwickTree tr(n);
    vector<int> suf(n + 1);
    int ans = 0;
    for(int i = n; i >= 1; i--) {
        suf[i] = tr.range_query(a[i], n);
        ans += tr.range_query(1, a[i]);
        tr.add(a[i], 1);
    }
    for(int i = n; i >= 1; i--) {
        tr.add(a[i], -1);
        int x = tr.range_query(a[i], n);
        if(x - suf[i] > 0) {
            ans -= x - suf[i];
        }
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
