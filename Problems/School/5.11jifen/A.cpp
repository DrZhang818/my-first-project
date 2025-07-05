#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    ll n;
    cin >> n;
    if(n & 1) {
        cout << 0 << "\n";
    } else {
        ll lo = 10, c5 = 0;
        while(lo <= n) {
            c5 += n / lo;
            lo *= 5;
        }
        cout << c5 << "\n";
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
