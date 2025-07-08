#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    ll k, x, y;
    cin >> k >> x >> y;
    ll dis = abs(x) + abs(y);
    if(k % 2 == 0 && dis % 2 == 1) {
        cout << -1 << "\n";
        return;
    }
    ll sx = (x >= 0 ? 1 : -1), sy = (y >= 0 ? 1 : -1);
    x = abs(x), y = abs(y);
    auto work = [&](ll x, ll y, ll sx, ll sy) -> void {
        ll cx = x / k, cy = y / k;
        ll cur_x = 0, cur_y = 0;
        for(ll i = 0; i < cx; i++) {
            cur_x += k * sx;
            cout << cur_x << " " << cur_y << "\n";
        }
        for(ll i = 0; i < cy; i++) {
            cur_y += k * sy;
            cout << cur_x << " " << cur_y << "\n";
        }
        if(abs(cur_x) != x || abs(cur_y) != y) {
            cout << x * sx << " " << y * sy << "\n";
        }
    };  
    if(dis % k == 0) {
        cout << dis / k << "\n";
        work(x, y, sx, sy);
    } else if(k % 2 == 0 || dis % 2 != max(1LL, dis / k) * k % 2) {
        cout << dis / k + 1 + (dis < k) << "\n";
        ll t = ((1 + max(1LL, dis / k)) * k - dis) >> 1;
        ll nx = x + t, ny = y - k + t;
        if(nx < 0 || ny < 0) {
            nx = x - k + t, ny = y + t;
        }
        work(nx, ny, sx, sy);
        cout << x * sx << " " << y * sy << "\n";
    } else {
        cout << dis / k + 2 + (dis < k) << "\n";
        ll t = max(1LL, dis / k) * k - dis;
        ll nx = x, ny = y + t;
        if(nx < 0 || ny < 0) {
            nx = x + t, ny = y;
        }
        work(nx, ny, sx, sy);
        if(nx == x) {
            ll delta_x = k - abs(t / 2);
            cout << (x + delta_x) * sx << " " << (y + t / 2) * sy << "\n";
            cout << x * sx << " " << y * sy << "\n";
        } else {
            ll delta_y = k - abs(t / 2);
            cout << (x + t / 2) * sx << " " << (y + delta_y) * sy << "\n";
            cout << x * sx << " " << y * sy << "\n";
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
