#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;



class Solution {
public:
    int countPartitions(vector<int>& nums) {
        int sum = 0;
        int n = nums.size();
        int a = 0;
        int cnt = 0;
        for(auto c : nums) sum += c;
        for(int i = 0; i < n; i++){
            a += nums[i];
            sum -= nums[i];
            if(abs(a - sum) % 2 == 0){
                cnt++;
            }
        }      
        return cnt;
    }
};