#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


class Solution {
public:
    int maxFreeTime(int eventTime, vector<int>& start, vector<int>& end) {
        int n = start.size();
        vector<int> nums, pre;
        for(int i = 0, t = 0; i < n; i++){
            int d = start[i] - t;
            nums.push_back(d);
            if(i == 0) {
                pre.push_back(0);
            }
            else pre.push_back(end[i - 1] - start[i - 1]);
            t = end[i];
        }
        nums.push_back(eventTime - end.back());
        pre.push_back(end.back() - start.back());

        int ans = 0;
        int len = nums.size();
        map<int,int> mp;
        for(int i = 0; i < len; i++){
            mp[nums[i]]++;
        }
        int cur = 0;
        int k = 1;
        for(int r = 0; r < len; r++){
            cur += nums[r];
            mp[nums[r]]--;
            if(mp[nums[r]] == 0) mp.erase(nums[r]);
            if(r < k) continue;
            int p = pre[r];
            auto it = mp.rbegin();
            if(it->first >= p){
                ans = max(ans, cur + p);
            }
            ans = max(ans, cur);
            int l = r - k;
            cur -= nums[l];
            mp[nums[l]]++;
        }
        return ans;
    }
};