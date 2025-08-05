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
            if(!b[i]) {
                b[i] = x;
                break;
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
    XorBasis b(64);
    for(int i = 1; i <= n; i++) {
        ull x;
        cin >> x;
        b.insert(x);
    }
    cout << b.query() << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> it;
    while(t--) {
        solve();
    }
    return 0;
}
