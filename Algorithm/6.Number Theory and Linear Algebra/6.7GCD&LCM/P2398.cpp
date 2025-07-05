#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int n;
    cin >> n;
    ll ans = 0;
    vector<int> phi(n + 1);
    vector<bool> vis(n + 1, false);
    iota(phi.begin(), phi.end(), 0);
    for(int i = 2; i <= n; i++) {
        if(!vis[i]) {
            phi[i] = i - 1;
            for(int j = 2; j <= n / i; j++) {
                vis[i * j] = true;
                phi[i * j] *= 1.0 - 1.0 / i;
            }
        }
    }
    vector<ll> sum(n + 1);
    sum[1] = 1;
    for(int i = 2; i <= n; i++) {
        sum[i] = sum[i - 1] + (ll)phi[i] * 2;
    }
    for(ll i = 1; i <= n; i++) {
        ans += i * sum[n / i];
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
    
