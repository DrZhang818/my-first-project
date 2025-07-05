#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;



class Solution {
public:
    int maxAdjacentDistance(vector<int>& nums) {
        int ans = 0;
        int n = nums.size();
        for(int i = 0; i < 2 * nums.size() - 1; i++){
            ans = max(ans, abs(nums[i % n] - nums[(i + 1) % n]));
        }      
        return ans;
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);


    solve();
    return 0;
}