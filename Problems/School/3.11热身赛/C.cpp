#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


constexpr ll inf = 1e18;
void solve() { 
    ll a, b, c;
    cin >> a >> b >> c;
    ll ans = -inf;
    ans = max(ans, a + b + c);
    ans = max(ans, a * b * c);
    ans = max(ans, a * b + c);
    ans = max(ans, a + b * c);
    ans = max(ans, a * (b + c));
    ans = max(ans, (a + b) * c);
    cout << ans << "\n";
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
    
