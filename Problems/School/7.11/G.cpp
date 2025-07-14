#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc101/tasks/arc099_b
db cal(ll x) {
    ll res = 0, t = x;
    while(t) {
        res += t % 10;
        t /= 10;
    }
    return 1.0 * x / res;
}
void solve() {
    int k;
    cin >> k;
    ll x = 0, base = 1;
    for(int i = 1; i <= k; i++) {
        while(1) {
            if(cal(x + base) > cal(x + base * 10)) {
                base *= 10;
            } else {
                break;
            }
        }
        x += base;
        cout << x << "\n";
    }
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
