#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int n;
    cin >> n;
    vector<ll> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    ll cur = 1, ans = 1;
    sort(nums.begin(), nums.end());
    for(int i = 0; i < n; i++){
        if(nums[i] < cur){
            ans += nums[i];
            continue;
        }
        else if(nums[i] > cur){
            ans += nums[i] - cur;
        }
        cur++;
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