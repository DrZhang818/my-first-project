#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://www.luogu.com.cn/problem/P4913
/*
    二叉树 || BFS || DFS
    题意:
        给定一颗有n个节点的二叉树, 以及按顺序给出第i个节点的子节点, 要求计算出
        二叉树的深度
    关键思考:
        按题意建出二叉树即可, 构建方法为:
        (1)定义一个树节点结构体, 使用l, r存储编号
        (2)使用数组存储节点
        遍历时候由于要计算深度, 因此使用BFS层序遍历更为适应
*/
struct TreeNode{
    int l, r;
};
void solve(){
    int n;
    cin >> n;
    vector<TreeNode> Tree(n + 1);
    for(int i = 1; i <= n; i++){
        cin >> Tree[i].l >> Tree[i].r;
    }
    queue<TreeNode> q;
    q.push(Tree[1]);
    int depth = 0;
    while(!q.empty()){
        int size = q.size();
        depth++;
        for(int i = 0; i < size; i++){
            auto cur = q.front();
            q.pop();
            if(cur.l){
                q.push(Tree[cur.l]);
            }
            if(cur.r){
                q.push(Tree[cur.r]);
            }
        }
    }
    cout << depth << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}