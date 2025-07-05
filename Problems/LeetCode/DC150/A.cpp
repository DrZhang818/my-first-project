#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



class Solution {
public:
    int sumOfGoodNumbers(vector<int>& nums, int k) {
        int sum = 0;
        int n = nums.size();
        for(int i = 0; i < n; i++) {
            bool ok = true;
            if(i - k >= 0) {
                if(nums[i] <= nums[i - k]) {
                    ok = false;
                }
            }
            if(i + k < n) {
                if(nums[i] <= nums[i + k]) {
                    ok = false;
                }
            }
            if(ok) sum += nums[i];
        }   
        return sum;
    }
};