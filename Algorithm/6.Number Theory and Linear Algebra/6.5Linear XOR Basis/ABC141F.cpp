#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class XorBasis {
    vector<ull> b;
public:
    XorBasis(int n) : b(n) {}
    void insert(ull x) {
        while(x) {
            int i = bit_width(x) - 1;
            if(b[i] == 0) {
                b[i] = x;
                return;
            }
            x ^= b[i];
        }
    }
    ull query() {
        ull res = 0;
        for(int i = b.size() - 1; i >= 0; i--) {
            res = max(res, res ^ b[i]);
        }
        return res;
    }
};
void solve() {
    int n;
    cin >> n;
    vector<ull> a(n + 1);
    ull sum = 0, mx = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        sum ^= a[i];
        mx = max(mx, a[i]);
    }
    int sz = bit_width(mx);
    XorBasis b(sz);
    for(int i = 1; i <= n; i++) {
        b.insert(a[i] & ~sum);
    }
    cout << sum + 2 * b.query() << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
