#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
class Solution {
public:
    int maxSum(vector<int>& nums) {
        int ans = 0;
        map<int,int> mp;
        for(int i = 0; i < nums.size(); i++) {
            if(nums[i] >= 0 && mp[nums[i]] == 0) {
                ans += nums[i];
                mp[nums[i]]++;
            }
        }      
        if(ans == 0) {
            ans = *max_element(nums.begin(), nums.end());
        }
        return ans;
    }
};