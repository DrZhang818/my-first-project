#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    ll n, ans = 0;;
    cin >> n;
    for(int x = 1; x * x <= n; x++){
        if(n % (x * x) == 0){
            ans += n / (x * x);
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}