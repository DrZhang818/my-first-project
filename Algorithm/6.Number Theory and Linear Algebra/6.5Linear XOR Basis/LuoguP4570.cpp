#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
struct info {
    ull id;
    int v;
    friend bool operator < (const info &a, const info &b) {
        return a.v > b.v;
    };  
};
class XorBasis {
    vector<ull> b;
public:
    XorBasis(int n) : b(n) {}
    bool insert(ull x) {
        while(x) {
            int i = bit_width(x) - 1;
            if(!b[i]) {
                b[i] = x;
                return true;
            }
            x ^= b[i];
        }
        return false;
    }
};
void solve() {
    int n;
    cin >> n;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].id >> a[i].v;
    }
    sort(a.begin() + 1, a.end());
    XorBasis b(64);
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        if(b.insert(a[i].id)) {
            ans += a[i].v;
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
