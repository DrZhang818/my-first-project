#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://icpc.bjtu.edu.cn/contest/1386/status
/*
    贪心 || 位运算枚举子集
    

*/
struct info{
    ll x, y, z;
};
void solve(){
    int n, m;
    cin >> n >> m;
    vector<info> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i].x >> a[i].y >> a[i].z;
    }
    vector<ll> dp(1 << 3, 0);
    for(int msk = 0; msk < 1 << 3; msk++){
        int sx = (msk & 1) ? 1 : -1;
        int sy = (msk & 2) ? 1 : -1;
        int sz = (msk & 4) ? 1 : -1;
        vector<ll> nums;
        for(auto v : a) {
            ll val = v.x * sx + v.y * sy + v.z * sz;
            nums.push_back(val);
        }
        sort(nums.begin(), nums.end(), greater<ll>());
        for(int i = 0; i < m; i++){
            dp[msk] += nums[i];
        }
    }
    ll ans = *max_element(dp.begin(), dp.end());
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

