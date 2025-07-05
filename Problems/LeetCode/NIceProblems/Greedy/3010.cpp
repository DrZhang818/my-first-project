#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://leetcode.cn/problems/divide-an-array-into-subarrays-with-minimum-cost-i/
/*
    贪心思维
    维护最小值和次小值即可
*/
class Solution {
public:
    int minimumCost(vector<int>& nums) {
        int sum = nums[0];
        int min1 = INT_MAX, min2 = INT_MAX;
        for(int i = 1; i < nums.size(); i++){
            if(nums[i] < min1){
                min2 = min1;
                min1 = nums[i];
            }
            else if(nums[i] < min2){
                min2 = nums[i];
            }
        }
        sum += min1 + min2;
        return sum;
    }
};

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