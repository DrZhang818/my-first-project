#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    ll n, l, r, k;
    cin >> n >> l >> r >> k;
    if(n & 1) {
        cout << l << "\n";
        return;
    }    
    if(l == r || n == 2) {
        cout << -1 << "\n";
        return;
    }
    ll lo = 1;
    while(lo <= l) {
        lo <<= 1;
    }
    if(lo > r) {
        cout << -1 << "\n";
        return;
    }
    if(k >= n - 1) {
        cout << lo << "\n";
    } else {
        cout << l << "\n";
    }
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
