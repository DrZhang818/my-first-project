#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;



class Solution {
public:
    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        int n = edges.size() + 1;
        vector<vector<PII>> adj(n);
        vector<bool> vis(n);
        vector<int> path;
        for(int i = 0; i < edges.size(); i++){
            adj[edges[i][0]].push_back({edges[i][1], edges[i][2]});
        }      
        unordered_map<int,int> mp;
        int maxLen = 0, count = INT_MAX, curLen = 0, curCnt = 0;
        
        auto dfs = [&](auto &&dfs, int i)->void{
            vis[i] = true;
            path.push_back(i);
            curCnt++;
            mp[nums[i]]++;
            for(auto &[cur, v] : adj[i]){
                if(mp[nums[cur]] > 0){
                    continue;
                }
                curLen += v;
                curCnt++;
                dfs(dfs, cur);
                curLen -= v;
                curCnt--;
            }
            if(curLen >= maxLen){
                maxLen = curLen;
                count = min(count, curCnt);
            }
            path.pop_back();
            mp[nums[i]]--;
            curCnt--;
        };
        for(int i = 0; i < n; i++){
            dfs(dfs, i);
        }
        return {maxLen, count};
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);


    solve();
    return 0;
}