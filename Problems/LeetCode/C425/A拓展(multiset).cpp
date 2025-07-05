#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://leetcode.cn/problems/minimum-positive-sum-subarray/

/*
    前缀和 + 定长滑窗 + 有序多重集合
    枚举右, 维护左
    遍历 j in range[1, n] (1 - based)
    维护左端点 i 使得窗口长度介于[l, r], 且使得s[j] - s[i - 1]为 >= 0的最小值
    关键在于左端点 i 的查找的时间复杂度如何降下来
    就需要使用有序集multiset高效维护[j - l, j - 1]范围内的前缀和
    根据前缀和1-based左闭右开的性质, 即维护sum数组下标 j - l -> j 的前缀和
    这样就可以利用单调性二分查找小于等于s[j]的最大值, 且满足窗口介于[l, r]
    最后, 当 j >= r的时候，窗口达到最大, 每次都有移除sum[j - r]
*/
class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {
        int ans = INT_MAX;
        int n = nums.size();
        vector<int> s(n + 1);
        multiset<int> s_set;
        for(int j = 1; j <= n; j++){
            //这里的前缀和是1-based
            s[j] = s[j - 1] + nums[j - 1];
            if(j < l){
                continue;
            }
            s_set.insert(s[j - l]);
            auto it = s_set.lower_bound(s[j]);
            if(it != s_set.begin()){
                ans = min(ans, s[j] - *--it);
            }
            if(j >= r){
                s_set.erase(s_set.find(s[j - r]));
            }
        }
        return ans == INT_MAX ? -1 : ans;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    solve();
    return 0;
}
