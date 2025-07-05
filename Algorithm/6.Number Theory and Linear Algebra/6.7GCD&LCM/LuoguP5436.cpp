#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    ll n;
    cin >> n;
    cout << max(1LL, n * (n - 1)) << "\n";
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
    
