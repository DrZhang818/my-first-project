#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    ll n, m, k;
    cin >> n >> m >> k;

    ll l = 0, r = m + 1;
    auto check = [&](ll x) -> bool {
        ll tot = n * x * (m / (x + 1)) + n * (m - (x + 1) * (m / (x + 1)));
        return tot >= k; 
    };
    while(l + 1 < r) {
        ll mid = l + r >> 1;
        if(check(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << r << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
