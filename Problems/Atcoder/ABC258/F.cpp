#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

void chmin(ll &x, ll y) {
    if(x > y) {
        x = y;
    }
}
void solve() {
    ll b, k, sx, sy, gx, gy;
    cin >> b >> k >> sx >> sy >> gx >> gy;
    auto cal = [&](ll x1, ll y1, ll x2, ll y2) -> ll {
        if(x1 % b == 0 && x1 == x2) {
            return abs(y1 - y2);
        }
        if(y1 % b == 0 && y1 == y2) {
            return abs(x1 - x2);
        }
        ll bid_x1 = (x1 + b - 1) / b;
        ll bid_x2 = (x2 + b - 1) / b;
        ll bid_y1 = (y1 + b - 1) / b;
        ll bid_y2 = (y2 + b - 1) / b;
        if(y1 % b == 0) {
            if(bid_x1 != bid_x2) {
                return abs(x1 - x2) + abs(y1 - y2);
            } else {
                ll res = k * abs(y1 - y2) + abs(x1 - x2);
                chmin(res, abs(y1 - y2) + x1 - (bid_x1 - 1) * b + x2 - (bid_x2 - 1) * b);
                chmin(res, abs(y1 - y2) + bid_x1 * b - x1 + bid_x2 * b - x2);
                return res;
            }
        } else {
            if(bid_y1 != bid_y2) {
                return abs(x1 - x2) + abs(y1 - y2);
            } else {
                ll res = k * abs(x1 - x2) + abs(y1 - y2);
                chmin(res, abs(x1 - x2) + y1 - (bid_y1 - 1) * b + y2 - (bid_y2 - 1) * b);
                chmin(res, abs(x1 - x2) + bid_y1 * b - y1 + bid_y2 * b - y2);
                return res;
            }
        }
    };
    ll ans = inf;
    ll bid_x1 = (sx + b - 1) / b;
    ll bid_x2 = (gx + b - 1) / b;
    ll bid_y1 = (sy + b - 1) / b;
    ll bid_y2 = (gy + b - 1) / b;
    for(int i = 0; i < 4; i++) {
        ll x1 = sx, y1 = sy, cur = 0;
        if(i == 0) x1 = bid_x1 * b, cur += (x1 - sx) * k;
        if(i == 1) y1 = bid_y1 * b, cur += (y1 - sy) * k;
        if(i == 2) x1 = (bid_x1 - 1) * b, cur += (sx - x1) * k;
        if(i == 3) y1 = (bid_y1 - 1) * b, cur += (sy - y1) * k;
        for(int j = 0; j < 4; j++) {
            ll x2 = gx, y2 = gy;
            ll res = cur;
            if(j == 0) x2 = bid_x2 * b, res += (x2 - gx) * k;
            if(j == 1) y2 = bid_y2 * b, res += (y2 - gy) * k;
            if(j == 2) x2 = (bid_x2 - 1) * b, res += (gx - x2) * k;
            if(j == 3) y2 = (bid_y2 - 1) * b, res += (gy - y2) * k;
            res += cal(x1, y1, x2, y2);
            chmin(ans, res);
        }   
    }
    if(bid_y1 == bid_y2 && bid_x1 == bid_x2) {
        chmin(ans, k * (abs(sx - gx) + abs(sy - gy)));
    }
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
