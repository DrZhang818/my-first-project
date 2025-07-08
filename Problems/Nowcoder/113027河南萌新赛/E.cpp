#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

const int MOD = 1000000007;
void solve() {
    int t;
    cin >> t;
    ll a = 1, b = 0;
    for(int i = 1; i <= t; i++) {
        ll na = a * a % MOD + 2 * a * b % MOD;
        ll nb = a * a % MOD + b * b % MOD;
        a = na % MOD;
        b = nb % MOD;
    }
    cout << a << " " << b << "\n";
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
