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
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        ans += x >= k;
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
    
