#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    i64 OA, OB, OC, OD;
    cin >> OA >> OB >> OC >> OD;
    i64 a = sqrt(OA);
    for(i64 x = max(0LL, a - 2); x <= a + 2; x++) {
        if(x * x == OA) {
            a = x;
            break;
        }
    }

    i64 d = (OC - 2 * OB - OA) / (2 * a);

    i64 delta = 8 * OB - 4 * d * d;
    i64 t = sqrt(delta);
    for(i64 x = max(0LL, t - 2); x <= t + 2; x++) {
        if(x * x == delta) {
            t = x;
            break;
        }
    }

    i64 x1 = (2 * d + t) / 4;
    i64 y1 = x1 - d;
    if(x1 * x1 + y1 * y1 == OB) {
        cout << a << " " << x1 << " " << y1 << " " << a + x1 - y1 << " " << x1 + y1 << " " << a - y1 << " " << a + x1 << "\n";        
        return;
    }
    
    i64 x2 = (2 * d - t) / 4;
    i64 y2 = x2 - d;
    if(x2 * x2 + y2 * y2 == OB) {
        cout << a << " " << x2 << " " << y2 << " " << a + x2 - y2 << " " << x2 + y2 << " " << a - y2 << " " << a + x2 << "\n";        
    }

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}