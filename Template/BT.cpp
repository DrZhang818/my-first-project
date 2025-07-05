#include <iostream>
#include <queue>
using namespace std;

typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

template<typename T>
struct TreeNode{
    T val;
    TreeNode* L;
    TreeNode* R;
    TreeNode(const T& x) : val(x), L(nullptr), R(nullptr) {}
};

template<typename T>
class BT{   
public:
    TreeNode<T>* root;
    BT() : root(nullptr) {}
    
    void add(const T& val){
        if(root == nullptr){
            root = new TreeNode<T>(val);
            return;
        }
        queue<TreeNode<T>*> q;
        q.push(root);
        while(!q.empty()){
            TreeNode<T>* cur = q.front();
            q.pop();
            if(cur->L == nullptr){
                cur->L = new TreeNode<T>(val);
                break;
            } else {
                q.push(cur->L);
            }
            if(cur->R == nullptr){
                cur->R = new TreeNode<T>(val);
                break;
            } else {
                q.push(cur->R);
            }
        }
    }
    
    void addSon(const T& faVal, const T& sonVal, int flag){
        TreeNode<T>* fa_node = search(faVal);
        if(fa_node == nullptr){
            cerr << "Parent node with value " << faVal << " not found.\n";
            return;
        }
        if(flag == 0){
            if(fa_node->L != nullptr){
                cerr << "Left child already exists for node " << faVal << ".\n";
                return;
            }
            fa_node->L = new TreeNode<T>(sonVal);
        }
        else if(flag == 1){
            if(fa_node->R != nullptr){
                cerr << "Right child already exists for node " << faVal << ".\n";
                return;
            }
            fa_node->R = new TreeNode<T>(sonVal);
        }
        else{
            cerr << "Invalid flag value. Use 0 for left child or 1 for right child.\n";
        }
    }
    
    void remove(const T& val){
        if(root == nullptr) return;
        if(root->val == val){
            destroyRec(root);
            root = nullptr;
            return;
        }
        queue<TreeNode<T>*> q;
        q.push(root);
        while(!q.empty()){
            TreeNode<T>* current = q.front(); q.pop();
            if(current->L){
                if(current->L->val == val){
                    destroyRec(current->L);
                    current->L = nullptr;
                    return;
                }
                else{
                    q.push(current->L);
                }
            }
            if(current->R){
                if(current->R->val == val){
                    destroyRec(current->R);
                    current->R = nullptr;
                    return;
                }
                else{
                    q.push(current->R);
                }
            }
        }
        cerr << "Node with value " << val << " not found.\n";
    }
    
    void modify(const T& old_val, const T& new_val){
        TreeNode<T>* node = search(old_val);
        if(node != nullptr){
            node->val = new_val;
        }
        else{
            cerr << "Node with value " << old_val << " not found.\n";
        }
    }
    void pre_order_print(){
        preOrderRec(root);
        cout << "\n";
    }
    void in_order_print(){
        inOrderRec(root);
        cout << "\n";
    }
    
    ~BT(){
        destroyRec(root);
    }
    
private:
    TreeNode<T>* search(const T& val) const{
        if(root == nullptr) return nullptr;
        queue<TreeNode<T>*> q;
        q.push(root);
        while(!q.empty()){
            TreeNode<T>* cur = q.front();
            q.pop();
            if(cur->val == val) return cur;
            if(cur->L != nullptr) q.push(cur->L);
            if(cur->R != nullptr) q.push(cur->R);
        }
        return nullptr;
    }
    
    void destroyRec(TreeNode<T>* node){
        if(node == nullptr) return;
        destroyRec(node->L);
        destroyRec(node->R);
        delete node;
    }
    
    void preOrderRec(TreeNode<T>* node){
        if(node == nullptr) return;
        cout << node->val << " ";
        preOrderRec(node->L);
        preOrderRec(node->R);
    }
    
    void inOrderRec(TreeNode<T>* node){
        if(node == nullptr) return;
        inOrderRec(node->L);
        cout << node->val << " ";
        inOrderRec(node->R);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    BT<int> bt;
    bt.add(1);
    bt.addSon(1, 2, 1);
    bt.addSon(2, 3, 0);
    bt.pre_order_print();
    return 0;
}
