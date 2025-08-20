#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const db PI = acos(-1.0);
void solve() {
    int a, b, d;
    cin >> a >> b >> d;
    if(a == 0 && b == 0) {
        cout << 0 << " " << 0 << "\n";
        return;
    }
    db r = sqrt(a * a + b * b);
    db theta = acos((db)a / r);
    if(b < 0) {
        theta = 2 * PI - theta;
    }
    theta += (db)d / 180 * PI;
    db x = r * cos(theta);
    db y = r * sin(theta);
    cout << fixed << setprecision(12) << x << " " << y << "\n";
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
