#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://atcoder.jp/contests/dp/tasks/dp_d
/*
    01背包
    至多型求最大
*/
void solve(){
    ll n, w;
    cin >> n >> w;
    vector<vector<ll>> infos(n, vector<ll>(2));
    for(auto& r : infos) for(auto& c : r) cin >> c;
    
    vector<ll> dp(w + 1);
    for(auto& x : infos){
        for(int j = w; j >= x[0]; j--){
            dp[j] = max(dp[j], dp[j - x[0]] + x[1]);
        }
    }
    cout << dp[w];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}