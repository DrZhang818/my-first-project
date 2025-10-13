#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    ll B, t1, a1, t2, a2;
    cin >> B >> t1 >> a1 >> t2 >> a2;
    ll dis = t2 - t1;
    ll can = B * dis;
    db ans1 = 0, ans2 = 0;
    if(a1 <= can) {
        ans1 = (db)a1 / B;
        ans2 = (db)a2 / B;
    } else {
        ans1 += dis;
        a1 -= can;
        db V = (db)B / 2;
        if(a1 == a2) {
            ans1 += a1 / V;
            ans2 += a2 / V;
        } else if(a1 < a2) {
            ans1 += a1 / V;
            ans2 += a1 / V;
            a2 -= a1;
            ans2 += (db)a2 / B;
        } else {
            ans1 += a2 / V;
            ans2 += a2 / V;
            a1 -= a2;
            ans1 += (db)a1 / B;
        }
    }
    cout << fixed << setprecision(12) << ans1 << " " << ans2 << "\n";
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
