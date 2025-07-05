#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://leetcode.cn/problems/minimum-array-sum/
/*
    多维DP || 贪心(从最小/最大开始贪心)
    根据数据量猜算法, 本题n op1 op2都 <= 100, 应该首先想比较暴力的解法(DP)
    灵神语录 ———— 做题先从DP开始想, 贪心是DP过不了时优化用的
*/

//记忆化搜索 -> 动态规划 O(n * op1 * op2)
/*
    寻找最优子结构
    对于每个nums[i], 有四种操作:
        不操作 || 操作op1 || 操作op2 || 操作op1和op2
    dp[i][op1][op2] := 前i个数, 经过最多op1个操作1, op2个操作2后的最小和
    初始状态 dp[0][op1][op2] = 0
    状态转移 dp[i][op1][op2] = min(dp[i - 1][op1][op2] + x, dp[i - 1][op1 - 1][op2] + (x + 1) / 2, 
                              dp[i - 1][op1][op2 - 1] + x - k, dp[i - 1][op1 - 1][op2 - 1] + y)
    空间优化:
            类似0-1背包, 可以把状态i优化掉
*/
class Solution {
public:
    int minArraySum(vector<int>& nums, int k, int op1, int op2) {
        int n = nums.size();
        vector<vector<vector<int>>> memo(n, vector(op1 + 1, vector<int>(op2 + 1, -1)));
        auto dfs = [&](auto&& dfs, int i, int op1, int op2) -> int{
            if(i < 0){
                return 0;
            }
            int& res = memo[i][op1][op2];
            if(res != -1){
                return res;
            }
            int x = nums[i];
            res = dfs(dfs, i - 1, op1, op2) + x;
            if(op1){
                res = min(res, dfs(dfs, i - 1, op1 - 1, op2) + (x + 1) / 2);
            }
            if(op2 && x >= k){
                res = min(res, dfs(dfs, i - 1, op1, op2 - 1) + x - k);
                if(op1){
                    int y = (x + 1) / 2 >= k ? (x + 1) / 2 - k : (x - k + 1) / 2;
                    res = min(res, dfs(dfs, i - 1, op1 - 1, op2 - 1) + y);
                }
            }
            return res;
        };
        return dfs(dfs, n - 1, op1, op2);
    }
};
//动态规划
class Solution {
public:
    int minArraySum(vector<int>& nums, int k, int op1, int op2) {
        int n = nums.size();
        vector<vector<int>> dp(op1 + 1, vector<int>(op2 + 1));
        for(int i = 0; i < n; i++){
            int x = nums[i];
            for(int p = op1; p >= 0; p--){
                for(int q = op2; q >= 0; q--){
                    int res = dp[p][q] + x;
                    if(p){
                        res = min(res, dp[p - 1][q] + (x + 1) / 2);
                    }
                    if(q && x >= k){
                        res = min(res, dp[p][q - 1] + x - k);
                        if(p){
                            int y = (x + 1) / 2 >= k ? (x + 1) / 2 - k : (x - k + 1) / 2;
                            res = min(res, dp[p - 1][q - 1] + y);
                        }                    
                    }
                    dp[p][q] = res;
                }
            }
        }   
        return dp[op1][op2];
    }
};

//贪心
/*
    核心思路:
            操作 1（除 2 上取整）应用到大的数上，越大越好。
            操作 2（减 k）应用到 ≥k 的数上。对于较小的数，需要细致地讨论
*/
class Solution {
public:
    int minArraySum(vector<int>& nums, int k, int op1, int op2) {
        sort(nums.begin(), nums.end());
        int high = ranges::lower_bound(nums, k * 2 - 1) - nums.begin();
        int low = ranges::lower_bound(nums, k) - nums.begin();
        for(int i = nums.size() - 1; i >= high; i--){
            if(op1){
                nums[i] = (nums[i] + 1) / 2;
                op1--;
            }
            if(op2){
                nums[i] -= k;
                op2--;
            }
        }
        unordered_multiset<int> st;
        int odd = 0;
        for(int i = low; i < high; i++){
            if(op2){
                nums[i] -= k;
                if(k % 2 && nums[i] % 2){
                    st.insert(nums[i]);
                } 
                op2--;
            }
            else{
                odd += nums[i] % 2;
            }
        }
        sort(nums.begin(), nums.begin() + high);
        int ans = 0;
        if(k % 2){
            for(int i = high - op1; i < high && odd; i++){
                int x = nums[i];
                auto it = st.find(x);
                if(it != st.end()){
                    st.erase(it);
                    odd--;
                    ans--;
                }
            }
        }
        for(int i = high - 1; i >= 0 && op1; i--){
            nums[i] = (nums[i] + 1) / 2;
            op1--;
        }
        return ans + reduce(nums.begin(), nums.end(), 0);
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    solve();
    return 0;
}
