#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int n;
    cin >> n;
    std::vector<int> nums(n);
    for(auto& num : nums){
        cin >> num;
    }
    vector<int> dp(3);
    dp[0] = 0, dp[1] = abs(nums[0] - nums[1]);
    for(int i = 2; i < n; i++){
        dp[i % 3] = min(dp[(i - 1) % 3] + abs(nums[i] - nums[i - 1]),
                    dp[(i - 2) % 3] + abs(nums[i] - nums[i - 2]));
    }
    cout << dp[(n - 1) % 3] << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}