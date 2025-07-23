#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

ll cal(ll R, ll x) {
    return R / x;
}
ll work(ll R) {
    ll res = R;
    res -= cal(R, 2);
    res -= cal(R, 3);
    res -= cal(R, 5);
    res -= cal(R, 7);
    res += cal(R, 6);
    res += cal(R, 10);
    res += cal(R, 14);
    res += cal(R, 15);
    res += cal(R, 21);
    res += cal(R, 35);
    res -= cal(R, 30);
    res -= cal(R, 42);
    res -= cal(R, 70);
    res -= cal(R, 105);
    res += cal(R, 210);
    return res;
}
void solve() {
    ll l, r;
    cin >> l >> r;
    cout << work(r) - work(l - 1) << "\n";
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
