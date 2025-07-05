#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://atcoder.jp/contests/dp/tasks/dp_e
/*
    01背包变形
    本题比较有意思, 当背包容量大, 总价值较小时, 考虑进行值域DP
    也就是dp[j]:=价值为j需要的最小背包容量
*/
void solve(){
    ll n, w;
    cin >> n >> w;
    vector<vector<ll>> infos(n, vector<ll>(2));
    for(auto& r : infos) for(auto& c : r) cin >> c;
    ll sum = 0;
    for(int i = 0; i < infos.size(); i++){
        sum += infos[i][1];
    }
    vector<ll> dp(sum + 1, LLONG_MAX / 2);
    dp[0] = 0;
    for(int i = 0; i < n; i++){
        ll w = infos[i][0];
        ll v = infos[i][1];
        for(int j = sum; j >= v; j--){
            dp[j] = min(dp[j], dp[j - v] + w);
        }
    }
    ll ans = 0;
    for(int j = 0; j <= sum; j++){
        if(dp[j] <= w){
            ans = max(ans, (ll)j);
        }
    }
    cout << ans << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}