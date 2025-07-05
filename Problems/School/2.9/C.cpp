#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){
    int n, a;
    cin >> n >> a;
    vector<int> nums(n);
    for(int i = 0; i < n; i++) {
        cin >> nums[i];
        nums[i] -= a;
    }
    ll ans = 0;
    unordered_map<int, ll> dp;
    for(int i = 0; i < n; i++) {
        int x = nums[i];
        ans += (x == 0);
        if(dp.find(-x) != dp.end()) ans += dp[-x];
        unordered_map<int,ll> ndp = dp;
        for(auto it = dp.begin(); it != dp.end(); it++){
            int y = it->first;
            ndp[y + x] += dp[y];
        }
        ndp[x]++;
        dp = ndp;
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

