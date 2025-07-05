#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){
    int n;
    cin >> n; 
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<vector<ll>> dp(n + 1, vector<ll>(2)); //0 - 前缀
    for(int i = 1; i <= n; i++) {
        if(a[i] < 0) {
            dp[i][0] = max(dp[i - 1][1], dp[i - 1][0]) + (-a[i]);
            dp[i][1] = dp[i - 1][1];
        }
        else {
            dp[i][1] = dp[i - 1][1] + (a[i]);
            dp[i][0] = dp[i - 1][0];
        }
    }
    cout << max(dp[n][0], dp[n][1]) << "\n";
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
