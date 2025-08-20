#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

struct info {
    ll val;
    int pos;
    friend bool operator < (const info &a, const info &b) {
        if(a.val != b.val) return a.val < b.val;
        return a.pos < b.pos;
    }
};
void solve() {
    vector<info> a(1);
    a[0] = info(3, 0);
    sort(a.begin(), a.end());
    auto it = lower_bound(a.begin(), a.end(), info(4, 0)) - a.begin();
    cout << it << "\n";
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
