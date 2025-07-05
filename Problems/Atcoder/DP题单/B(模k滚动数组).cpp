#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://atcoder.jp/contests/dp/tasks/dp_b
/*
    DP || 模K滚动数组
*/
void solve(){
    int n, k;
    cin >> n >> k;
    std::vector<int> nums(n);
    for(auto& num : nums){
        cin >> num;
    }
    vector<int> dp(k + 1);
    dp[0] = 0, dp[1] = abs(nums[0] - nums[1]);
    for(int i = 2; i < n; i++){
        dp[i % (k + 1)] = dp[(i - 1) % (k + 1)] + abs(nums[i] - nums[i - 1]);
        for(int j = 2; j <= k && j <= i; j++){
            dp[i % (k + 1)] = min(dp[i % (k + 1)], dp[(i - j) % (k + 1)] + abs(nums[i] - nums[i - j]));
        }
    }
    cout << dp[(n - 1) % (k + 1)] << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}