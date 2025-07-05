#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    ll n;
    cin >> n;
    int ans = 0;
    for(ll i = sqrt(n); i >= 1; i--){
        if(n % i == 0){
            n = n / i;
            break;
        }
    }
    ans = to_string(n).size();
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}