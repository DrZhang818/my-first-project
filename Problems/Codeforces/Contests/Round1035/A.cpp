#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    if(b < a) {
        if((a ^ 1) == b) {
            cout << y << "\n";
        } else {
            cout << -1 << "\n";
        }
        return;
    }
    if(a == b) {
        cout << 0 << "\n";
        return;
    }
    int ans = 0;
    if(y >= x) {
        ans = (b - a) * x;
    } else {
        while(a != b) {
            if(a & 1) {
                ans += x;
                a++;
            } else {
                ans += y;
                a++;
            }
        }
    }   
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
