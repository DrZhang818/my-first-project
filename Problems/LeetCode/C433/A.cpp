#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


class Solution {
public:
    int subarraySum(vector<int>& nums) {
        int n = nums.size();
        vector<int> prefix(n + 1);      
        int ans = 0;
        for(int i = 0; i < n; i++){
            prefix[i + 1] = prefix[i] + nums[i];
            int s = max(0, i - nums[i]);
            ans += prefix[i] - prefix[s];
        }
        return ans;
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    return 0;
}