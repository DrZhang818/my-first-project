#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

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
    vector<int> ca(n + 1);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        ca[x]++;
    }
    int mx = 0;
    FenwickTree fen1(n + 1), fen2(n + 1);
    for(int i = 1; i <= n; i++) {
        if(ca[i] == 0) {
            continue;
        }
        int c = ca[i];
        mx = max(mx, c + fen1.query(c - 1) + (c - 1) * fen2.range_query(c, n));
        fen1.add(c, c);
        fen2.add(c, 1);
    }
    cout << n - mx << "\n";
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
