//https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/
/*
    二叉树 || 递归
    题意:
        给定一棵二叉树的根节点和两个树上节点p和q
        要求找到p和q的最近公共祖先(LCA)
    关键思考:
        本题可以分成两种情况讨论:
        (1)p和q为包含关系, 不妨设q为p的子孙节点
           此时答案就是p本身, 因此可以得出: 当root等于待查节点时, 直接返回
        (2)p和q分属于两颗树
           此时也就对应l和r都不为空(左右都搜到了待查节点), 此时root便是答案
        细节处理:
        当root为空时, 也就是遍历到了空节点, 自然返回空
        当l和r都为空的时候, 也就是左树右树都没有目标节点, 那么在当前root也不是目标节点情况下
            自然就要返回空节点代表没找到
        当l和r只有一个为空的时候, 返回非空的部分
*/
struct TreeNode{
    TreeNode* left;
    TreeNode* right;
    int val;
};
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root || root == p || root == q) return root;
        TreeNode* l = lowestCommonAncestor(root->left, p, q);
        TreeNode* r = lowestCommonAncestor(root->right, p, q);
        if(l && r){
            return root;
        }
        if(!l && !r){
            return nullptr;
        }
        return !l ? r : l;
    }
};