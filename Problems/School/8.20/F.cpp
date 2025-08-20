#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    ll b, k, sx, sy, gx, gy;
    cin >> b >> k >> sx >> sy >> gx >> gy;
    if(((sx + b - 1) / b != (gx + b - 1) / b) + ((sy + b - 1) / b != (gy + b - 1) / b) >= 2) {
        ll lenx1, lenx2, leny1, leny2;
        if(sx < gx) {
            lenx1 = (sx + b - 1) / b * b - sx;
            lenx2 = gx - gx / b * b; 
        } else {
            lenx1 = sx - sx / b * b;
            lenx2 = (gx + b - 1) / b * b - gx;
        }
        if(sy < gy) {
            leny1 = (sy + b - 1) / b * b - sy;
            leny2 = gy - gy / b * b; 
        } else {
            leny1 = sy - sy / b * b;
            leny2 = (gy + b - 1) / b * b - gy;
        }
        cerr << lenx1 << " " << leny1 << " " << lenx2 << " " << leny2 << "\n";
        ll sum = min(lenx1, leny1) + min(lenx2, leny2);
        ll res = sum * k;
        ll dis = abs(sx - gx) + abs(sy - gy) - sum;
        res += dis;
        cout << res << "\n";
    } else {
        cerr << "?\n";
    }
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
