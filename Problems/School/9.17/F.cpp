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
    vector<PII> a(n + 1);
    vector<int> val;
    for(int i = 1; i <= n; i++) {
        cin >> a[i].first;
    }
    for(int i = 1; i <= n; i++) {
        cin >> a[i].second;
        val.push_back(a[i].second);
    }
    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());
    int sz = val.size();
    sort(a.begin() + 1, a.end(), 
        [&](auto x, auto y) {
            return x.first < y.first; 
        });
    FenwickTree tr(sz + 5);
    ll ans = 1LL * n * n;
    for(int i = 1, j = 1; i <= n; i++) {
        while(j <= n && a[j].first == a[i].first) {
            auto it = lower_bound(val.begin(), val.end(), a[j].second) - val.begin() + 1;
            tr.add(it, 1);
            j++;
        }
        ans -= n - j + 1;
        auto it = lower_bound(val.begin(), val.end(), a[i].second) - val.begin() + 1;
        ans -= tr.query(it - 1);
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
