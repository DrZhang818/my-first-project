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
    int num;
    vector<u32> basis;
public:
    XorBasis() {
        b.resize(32);
        num = 0;
    }
    bool insert(u32 v) {
        for(int i = b.size() - 1; i >= 0; i--) {
            if(!(v >> i)) {
                continue;
            }
            if(b[i] == 0) {
                b[i] = v;
                num++;
                return true;
            }
            v ^= b[i];
        }
        return false;
    }
    u32 maxXorWithVal(u32 v) {
        u32 res = v;
        for(int i = b.size() - 1; i >= 0; i--) {
            res = max(res, res ^ b[i]);
        }
        return res;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<u32> a(n + 1), b(n + 1);
    u32 sum = 0, suma = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        suma ^= a[i];
        sum ^= a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
        sum ^= b[i];
    }
    u32 tar = (sum == 0 ? 0 : (1ULL << __lg(sum)));
    tar ^= suma;
    tar = (~tar);
    XorBasis B;
    for(int i = 1; i <= n; i++) {
        B.insert(a[i] ^ b[i]);
    }
    u32 ans = B.maxXorWithVal(tar);
    ans ^= tar;
    ans ^= suma;
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
