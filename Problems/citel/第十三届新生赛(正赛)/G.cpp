#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

/*
    贪心思维
    题意: 给定一个长度为n的数组, 你有m次op1以及k次op2
        op1为选择数组中的一个数(不能重复选择), 获得a[i]的价值
        op2为选择一个进行过op1的数, 获得1e5-a[i]的价值
        目标是找到一个合法方案, 使得获得的价值最大
    简化问题:
        问题可以简化为选择k个数贡献1e5, 剩下(m-k)个数贡献a[i]
        那么只需要最大化(m - k)个数的和即可, 排序后选最大值即可
*/
//优化做法
void solve1(){
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> nums(n);
    for(auto& num : nums) cin >> num;
    sort(nums.begin(), nums.end(), greater<int>());
    int ans = k * 100000;
    for(int i = 0; i < m - k; i++){
        ans += nums[i];
    }
    cout << ans << "\n";
}
//比赛时做法
void solve(){
    int n, m, k;
    cin >> n >> m >> k;
    ll ans = 0;
    vector<ll> nums(n);
    for(auto& num : nums){
        cin >> num;
    }
    sort(nums.begin(), nums.end());
    int l = 0;
    if(k > 0){
        for(; l < k && l < m; l++){
            ans += 100000;
        }
    }
    int re = m - l;
    for(int r = nums.size() - 1; re > 0 && r >= l; r--){
        ans += nums[r];
        re--;
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