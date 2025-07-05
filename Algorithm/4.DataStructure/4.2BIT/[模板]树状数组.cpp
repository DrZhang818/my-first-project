#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


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
    FenwickTree tree(n);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        tree.add(i, x);
    }
    cout << tree.query(n) << "\n";
    cout << tree.range_query(3, 3) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
