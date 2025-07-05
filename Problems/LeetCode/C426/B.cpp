#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

//https://leetcode.cn/problems/identify-the-largest-outlier-in-an-array/description/
/*
    数据结构(哈希表)

    设特殊元素1(n - 2个元素和) 为 x, 异常值为y
    则有:   2 * x + y == sum
            2 * x == sum - y
    于是可以先把 2 * x 的结果存在哈希表中
    然后遍历y, 看是否存在sum - y
    ans为最大的合法y
*/

class Solution {
public:
    int getLargestOutlier(vector<int>& nums) {
        unordered_map<int, int> cnt;
        int total = 0;
        for(int x : nums){
            cnt[2 * x]++;
            total += x;
        }
        int ans = INT_MIN;
        for(int x : nums){
            cnt[2 * x]--;
            if(cnt[total - x] > 0){
                ans = max(ans, x);
            }
            cnt[2 * x]++;
        }
        return ans;
    }
};

int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    return 0;
}