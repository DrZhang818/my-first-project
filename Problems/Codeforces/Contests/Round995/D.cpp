#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    ll n, x, y;
    cin >> n >> x >> y;
    vector<ll> nums(n);
    ll sum = 0;
    for(auto &num : nums) {
        cin >> num;
        sum += num;
    }
    sort(nums.begin(), nums.end());
    ll ans = 0;
    for(int i = 0; i < n; i++){
        ll cur = nums[i];
        ll low = sum - cur - y;
        ll high = sum - cur - x;
        ll L = lower_bound(nums.begin() + i + 1, nums.end(), low) - nums.begin();
        ll R = lower_bound(nums.begin() + i + 1, nums.end(), high + 1) - nums.begin();
        ans += R - L;
    }
    cout << ans << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
