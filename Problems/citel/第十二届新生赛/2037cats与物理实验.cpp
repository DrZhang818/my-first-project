#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;



void solve(){
    int n;
    ll k;
    cin >> n >> k;
    vector<int> nums(n);
    for(auto& num : nums){
        cin >> num;
    }
    ll pretest = 0;
    for(int i = 0; i < n - 1; i++){
        pretest += abs(nums[i + 1] - nums[i]);
    }
    if(pretest <= k){
        cout << n << "\n";
        return;
    }
    vector<ll> pre(n), suf(n);
    for(int i = 2; i < n; i++){
        pre[i] = pre[i - 1] + abs(nums[i - 1] - nums[i - 2]);
    }
    for(int i = n - 3; i >= 0; i--){
        suf[i] = suf[i + 1] + abs(nums[i + 1] - nums[i + 2]);
    }
    function<bool(int)> check = [&](int mid) -> bool{
        ll cur = LLONG_MAX;
        for(int l = 0; l + mid - 1 < n; l++){
            int r = l + mid - 1;
            if(r + 1 >= n || l - 1 < 0){
                cur = min(cur, pre[l] + suf[r]);
            }
            else{
                cur = min(cur, pre[l] + suf[r] + abs(nums[r + 1] - nums[l - 1]));
            }
        }
        return cur <= k;
    };
    
    int l = 0, r = n;
    while(l + 1< r){
        int mid = l + (r - l) / 2;
        if(check(mid)){
            r = mid;
        }
        else{
            l = mid;
        }
    }
    cout << n - r << "\n";
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