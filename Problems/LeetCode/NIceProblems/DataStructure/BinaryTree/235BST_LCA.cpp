#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-search-tree/solutions/
/*
    BST || LCA
    题意:
        给定一颗二叉搜索树的根节点和两个待查节点p和q
        要求返回p和q的最近公共祖先
    关键思考:
        bst的性质:
        左子树 < 根节点 < 右子树 (用val比较)
        因此LCA一定满足: min(p,q) <= LCA <= max(p,q)
            6
           3 7
          2 4  
        对于这种情况, 假如我们要查2和7的LCA, 如何知道是6而不是3的
        证明:
            由于6是(3,2,4)和(7)两个子树的根节点
            如果6满足min(p,q) <= 6 <= max(p,q)
            此时有且仅有两种情况
            (1)p和q分别属于6的左子树和右子树
            (2)p,q之一的值就是6
            显然不存在3能成为p,q的LCA的情况
            并且由上述讨论可以保证此时返回6就是答案
*/
struct TreeNode{
    TreeNode *left;
    TreeNode *right;
    int val;
};
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode *ans = root;
        int mn = min(p->val, q->val), mx = max(p->val, q->val);
        while(ans->val < mn || ans->val > mx){
            if(ans->val < mn){
                ans = ans->right;
            }
            else if(ans->val > mx){
                ans = ans->left;
            }
        }
        return ans;
    }
};