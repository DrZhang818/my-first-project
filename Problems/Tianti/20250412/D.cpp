#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    ll ans = 0;
    int flag;
    while(cin >> flag) {
        if(flag == 1) ans++;
        else if(flag == 0) cout << ans << "\n";
        else break;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
