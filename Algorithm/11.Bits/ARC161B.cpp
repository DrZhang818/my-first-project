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
    ll ans = 0, cnt = 0;
    if(n < 7) {
        cout << -1 << "\n";
        return;
    }
    while(cnt < 3) {
        int cur = 0;
        ans = 0;
        for(int i = 60; i >= 0 && cur < 3; i--) {
            if(n >> i & 1) {
                ans |= 1LL << i;
                cur++;
            }
        }
        cnt = cur;
        ll lowbit = n & -n;
        n ^= lowbit;
        n |= lowbit - 1;
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
