#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


template <typename T>
struct TreeNode{
    T val;
    TreeNode* l;
    TreeNode* r;
    TreeNode(const T& x) : val(x), l(nullptr), r(nullptr) {}
};

template <typename T>
class BST{
public:
    TreeNode<T>* root;
    BST() : root(nullptr) {}
    void add(const T& val){
        root = insertRec(root, val);
    }
    void preOrder() const{
        preOrderRec(root);
        cout << "\n";
    }
    void inOrder() const {
        inOrderRec(root);
        cout << "\n";
    }
    void postOrder() const{
        postOrderRec(root);
        cout << "\n";
    }
    ~BST(){
        destoryRec(root);
    }
private:
    TreeNode<T>* insertRec(TreeNode<T>* node, const T& val) {
        if(node == nullptr){
            return new TreeNode<T>(val);
        }
        if(val < node->val){
            node->l = insertRec(node->l, val);
        }else{
            node->r = insertRec(node->r, val);
        }
        return node;
    }
    void preOrderRec(TreeNode<T>* node) const {
        if(node == nullptr) return ;
        cout << node->val << " ";
        preOrderRec(node->l);
        preOrderRec(node->r);
    }
    void inOrderRec(TreeNode<T>* node) const {
        if(node == nullptr) return ;
        inOrderRec(node->l);
        cout << node->val << " ";
        inOrderRec(node->r);
    }
    void postOrderRec(TreeNode<T>* node) const {
        if(node == nullptr) return ;
        postOrderRec(node->l);
        postOrderRec(node->r);
        cout << node->val << " ";
    }
    void destoryRec(TreeNode<T>* node) {
        if(node == nullptr) return ;
        destoryRec(node->l);
        destoryRec(node->r);
        delete node;
    }
};

template <typename T>
class BT{
public:
    TreeNode<T>* root;
    BT() : root(nullptr) {}
    void add(const T& val){
        if(root == nullptr){
            root = new TreeNode<T>(val);
            return ;
        }
        queue<TreeNode<T>*> q;
        q.push(root);
        while(!q.empty()){
            TreeNode<T>* cur = q.front();
            q.pop();
            if(cur->l == nullptr){
                cur->l = new TreeNode<T>(val);
                break;
            } else {
                q.push(cur->l);
            }
            if(cur->r == nullptr){
                cur->r = new TreeNode<T>(val);
                break;
            } else {
                q.push(cur->r);
            }
        }
    }
    void preOrder() const {
        preOrderRec(root);
        cout << "\n";
    }
    void inOrder() const {
        inOrderRec(root);
        cout << "\n";
    }
    void postOrder() const {
        postOrderRec(root);
        cout << "\n";
    }
    ~BT(){
        destoryRec(root);
    }
private:
    void preOrderRec(TreeNode<T>* node) const {
        if(node == nullptr) return ;
        cout << node->val << " ";
        preOrderRec(node->l);
        preOrderRec(node->r);
    }
    void inOrderRec(TreeNode<T>* node) const {
        if(node == nullptr) return ;
        inOrderRec(node->l);
        cout << node->val << " ";
        inOrderRec(node->r);
    }
    void postOrderRec(TreeNode<T>* node) const {
        if(node == nullptr) return ;
        postOrderRec(node->l);
        postOrderRec(node->r);
        cout << node->val << " ";
    }
    void destoryRec(TreeNode<T>* node){
        if(node == nullptr) return ;
        destoryRec(node->l);
        destoryRec(node->r);
        delete node;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    BT<int> bt;
    for(int i = 1; i <= 10; i++){
        bt.add(i);
    }
    bt.inOrder();
    return 0;
}
