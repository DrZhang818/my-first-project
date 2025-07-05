#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/problemset/problem/484/A
void solve() {
    ll l, r;
    cin >> l >> r;
    ll ans = 0;
    bool ok = false;
    for(int i = 60; i >= 0; i--) {
        if(ok) {
            ans |= 1LL << i;
        } else {
            if((l >> i & 1) && (r >> i & 1)) {
                ans |= 1LL << i;
            } else if(r >> i & 1) {
                ok = true;
            }
        }
    }
    if((r & ans) == ans) {
        ans = r;
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
