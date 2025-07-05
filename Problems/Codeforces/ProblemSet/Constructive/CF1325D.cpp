#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/problemset/problem/1325/D
void solve() {
    ll u, v;
    cin >> u >> v;
    ll k = v - u;
    if(k < 0 || k % 2 == 1) {
        cout << -1 << "\n";
        return;
    } 
    if(u == 0 && v == 0) {
        cout << 0 << "\n";
        return;
    }
    k >>= 1;
    ll x = u;
    int ans = 3;
    if(!(x & k)) x |= k, ans--;
    if(!(x & k)) x |= k, ans--;
    cout << ans << "\n";
    cout << x << " ";
    for(int i = 0; i < ans - 1; i++) {
        cout << k << " ";
    }
    cout << "\n";
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
