#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n, k;
    cin >> n >> k;
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        ans += 2 * min(x, k - x);
    }    
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
