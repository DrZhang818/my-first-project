class Solution {
public:
    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        int n = edges.size() + 1;
        vector<vector<int>> adj(n);
        vector<bool> vis(n);
        vector<vector<int>> valid;
        vector<int> path;
        for(int i = 0; i < edges.size(); i++){
            adj[edges[i][0]].push_back(edges[i][1]);
        }      
        unordered_map<int,int> mp;
        auto dfs = [&](auto &&dfs, int i) -> void{
            vis[i] = true;
            path.push_back(i);
            mp[nums[i]]++;
            for(auto &cur : adj[i]){
                if(mp[nums[cur]] > 0){
                    valid.push_back(path);
                    break;
                }
                dfs(dfs, cur);
            }
            path.pop_back();
            mp[nums[i]]--;
        };
        for(int i = 0; i < n; i++){
            if(!vis[i]){
                dfs(dfs, i);
            }
        }
        for(auto &p : valid){
            for(auto c : p){
                cout << c << " ";
            }
            cout << "\n";
        }
        return {};
    }
};