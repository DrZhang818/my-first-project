#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
typedef unsigned int u32;
const int inf = 1000000000;

class XorBasis {
    vector<u32> b;
public:
    XorBasis(int n) : b(n) {}
    bool insert(u32 x) {
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
    vector<int> a(n + 1);
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        ans += a[i];
    }    
    sort(a.begin() + 1, a.end(), greater<int>());
    XorBasis b(32);
    for(int i = 1; i <= n; i++) {
        if(b.insert(a[i])) {
            ans -= a[i];
        }
    }
    cout << ans << "\n";
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
