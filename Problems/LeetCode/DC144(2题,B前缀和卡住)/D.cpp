#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://leetcode.cn/problems/find-the-maximum-number-of-fruits-collected/

class Solution {
public:
    int maxCollectedFruits(vector<vector<int>>& fruits) {
        int ans = 0, n =fruits.size();
        vector<vector<int>> memo(n, vector<int>(n, -1));
        auto dfs = [&](auto&& dfs, int i, int j) -> int{
            if(i + j < n - 1 || j >= n){
                return INT_MIN;
            }
            if(i == 0){
                return fruits[i][j];
            }
            int& res = memo[i][j];
            if(res != -1){
                return res;
            }
            return res = max({dfs(dfs, i - 1, j - 1), dfs(dfs, i - 1, j), dfs(dfs, i - 1, j + 1)}) + fruits[i][j];
        };  

        for(int i = 0; i < n; i++){
            ans += fruits[i][i];
        }
        ans += dfs(dfs, n - 2, n - 1);

        ranges::fill(memo, vector<int>(n, -1));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < i; j++){
                fruits[j][i] = fruits[i][j];
            }
        }
        return ans + dfs(dfs, n - 2, n - 1);
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    

    return 0;
}





