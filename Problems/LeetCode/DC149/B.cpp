#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


class Solution {
public:
    int maxFreeTime(int eventTime, int k, vector<int>& start, vector<int>& end) {
        int n = start.size();
        vector<int> nums;
        for(int i = 0, pre = 0; i < n; i++){
            int d = start[i] - pre;
            nums.push_back(d);
            pre = end[i];
        }
        nums.push_back(eventTime - end.back());
        int ans = 0;
        int len = nums.size();
        int cur = 0;
        for(int r = 0; r < n; r++){
            cur += nums[r];
            if(r < k - 1) continue;
            ans = max(ans, cur);
            int l = r - k + 1;
            cur -= nums[l];
        }
        return ans;
    }
};