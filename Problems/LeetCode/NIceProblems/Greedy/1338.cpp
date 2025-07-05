#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://leetcode.cn/problems/reduce-array-size-to-the-half/
/*
    贪心思维 || 哈希表
    统计次数即可
*/
class Solution {
public:
    int minSetSize(vector<int>& nums) {
        int k = (nums.size() + 1) / 2;
        unordered_map<int, int> hash;
        for(int i = 0; i < nums.size(); i++){
            hash[nums[i]]++;
        }
        vector<int> count;
        for(auto& [_, c] : hash){
            count.push_back(c);
        }
        sort(count.begin(), count.end(), greater<int>());
        int ans = 0;
        for(int i = 0; i < count.size(); i++){
            k -= count[i];
            ans++;
            if(k <= 0) break;
        }
        return ans;
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