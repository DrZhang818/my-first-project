#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

struct TreeNode{
    TreeNode *left;
    TreeNode *right;
    int val;
};
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> ans;
        vector<int> path;
        function<void(TreeNode*, int)> dfs = [&](TreeNode *node, int cur) -> void{
            if(!node) return ;
            path.push_back(node->val);
            if(!node->left && !node->right){
                if(cur == targetSum){
                    ans.emplace_back(path);
                }
                return;
            }
            dfs(root->left, cur + node->val);
            dfs(root->right, cur + node->val);
            path.pop_back();            
        };
        dfs(root, targetSum);
        return ans;
    }
};